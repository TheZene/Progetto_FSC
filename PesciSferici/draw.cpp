#pragma once

#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include <thread>

#include "draw.h"
#include "Frame.h"

//-------------------------------------------------------------------------------------------------
void normale9f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    float xx1, yy1, zz1, xx2, yy2, zz2, nx, ny, nz, nn;
    xx1 = x2 - x1; yy1 = y2 - y1; zz1 = z2 - z1;
    xx2 = x3 - x1; yy2 = y3 - y1; zz2 = z3 - z1;
    nx = yy1 * zz2 - yy2 * zz1; ny = zz1 * xx2 - zz2 * xx1; nz = xx1 * yy2 - xx2 * yy1;
    nn = sqrt(nx * nx + ny * ny + nz * nz);
    nx /= nn; ny /= nn; nz /= nn;
    glNormal3f(nx, ny, nz);
}
//-------------------------------------------------------------------------------------------------
/*void draw_palla(void) {
    GLUquadricObj* palla;
    palla = gluNewQuadric();
    glDisable(GL_TEXTURE_2D);
    GLfloat cubeMater[] = { 0.2, 0.2, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubeMater);
    gluQuadricDrawStyle(palla, GLU_FILL);
    gluQuadricNormals(palla, GLU_FLAT);
    gluSphere(palla, 1.0, 50, 100);
    glEnable(GL_TEXTURE_2D);
}*/
//------------------------------------------------------------------------------------------------
void draw_cube(void) {
    glColor3f(0.2, 1.0, 0.2);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(-1.0f, 1.0f, -1.0f); glVertex3f(1.0f, 1.0f, -1.0f); glVertex3f(1.0f, -1.0f, -1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(0, 0, 1);
    glVertex3f(-1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0, -1, 0);
    glVertex3f(1.0f, -1.0f, -1.0f); glVertex3f(1.0f, -1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(0, 1, 0);
    glVertex3f(-1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glNormal3f(-1, 0, 0);
    glVertex3f(-1.0f, -1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(1, 0, 0);
    glVertex3f(1.0f, -1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); glVertex3f(1.0f, 1.0f, -1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
}
//------------------------------------------------------
/*void draw_pesce() {
    
    //se non ho inizializzato la struttura dati la inizializzo
    if (!init) {
        float arr0[4][3] = { { 0.0, 0.0, 0.0 },
                             { 4.0, 0.0, 0.0 }, 
                             { -4.0, -4.0, 0.0 },
                             { -4.0, 0.0, 0.0 } };
        float arr1[3] = { 2.0, 1.0, 0.0 };
        float arr2[3] = { 0.0, 0.0, 0.0 };
        Pesce* p1 = new Pesce(arr0[0], arr1, arr2);
        Pesce* p2 = new Pesce(arr0[1], arr1, arr2);
        Pesce* p3 = new Pesce(arr0[2], arr1, arr2);
        Pesce* p4 = new Pesce(arr0[3], arr1, arr2);
        s->addPesce(p1);
        s->addPesce(p2);
        s->addPesce(p3);
        s->addPesce(p4);
        init = true;
    }
    //ottengo il banco di pesci
    s->getSchool();
    //qua calcolo la direzione del banco media (in teoria pesata perche' chi sta avanti comanda)
    s->computeAVGDir();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer

    //qua disegno
    for (int i = 0; i < s->getSchool().size(); i++) {
        //calcolo lo spostamento dei pesci
        s->getSchool()[i]->Nuota();
        glColor3f(1.0f, .0f, 1.0f);     
        glPushMatrix();
        //traslo
        glTranslatef(s->getSchool()[i]->getPos()[0], s->getSchool()[i]->getPos()[1], s->getSchool()[i]->getPos()[2]);
        glRotatef(-(atan(0.5)*180/3.14), 0, 0, 1);
        draw_cube();
        glPopMatrix();
    }
    glLoadIdentity();
    gluLookAt(s->getSchool()[0]->getPos()[0]-30, s->getSchool()[0]->getPos()[1], 60, s->getSchool()[0]->getPos()[0], s->getSchool()[0]->getPos()[1], s->getSchool()[0]->getPos()[2], 0, 1, 0);
    /*if (lastTheta != s->getSchool()[0]->computeTheta()) {
        glRotatef(s->getSchool()[0]->computeTheta(), 0, 0, 1);
        glPushMatrix();
        lastTheta = s->getSchool()[0]->computeTheta();
    }*/
    /*glLoadIdentity();
    gluLookAt(s->getSchool()[0]->getPos()[0] - 4.0, 9.0, s->getSchool()[0]->getPos()[2] + 24.0,
        s->getSchool()[0]->getPos()[0] - 4.0, 2.0, s->getSchool()[0]->getPos()[2],
        0, 1, 0);
    glRotatef(s->getSchool()[0]->computeTheta(), 1, 1, 1);
    glPopMatrix();*/
}*/


//pesce con moto circolare
void draw_pesce2(void) {
    int i = 0;
    //i=0->ruta su piano xz i=1->ruota su piano xy, altri valori->bohhh
    cerchio.NuotainCerchio(t, i);
    //grafica del pesce
    glPushMatrix();
    glTranslated(cerchio.getPos()[0], cerchio.getPos()[1], cerchio.getPos()[2]);
    glCallList(SFERA);
    glPopMatrix();
}
// ********************************************************************************************************
void draw_scene(void) {

    draw_pesce2();

    glColor3f(0.1, 1.0, 0.1);		// redish
    //glFrontFace(GL_CW); 
    //glutSolidTeapot(0.5);			// draw the teapot
   //glutSolidTorus(1,2,30,30);			            // draw the torus
    //glutSolidCylinder(1,2,30,20);			            // draw the cylinder

}
