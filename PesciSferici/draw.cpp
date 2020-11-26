#pragma once

#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include <thread>

#include "draw.h"
#include "Frame.h"

extern float* RepulsiveForcesFish(Pesce PesceGen, Pesce PesceSub); //il primo pesce genera il potenziale il secondo lo subisce
extern float* AttractiveForcesSchool(School Banco, Pesce Fish); //calcola la media della posizone dei pesci del banco(centro) e la velocit� media poi fa il conto delle dimensioni massime del banco
extern void SetAccelerazioni(vector<School>& Oceano); //setta tutte le acc di tutti i pesci
extern void DrawOcean(vector<School>& Oceano);
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
void draw_palla(void) {
    glColor3f(1.0, 0, 0);
    GLUquadricObj* palla;
    palla = gluNewQuadric();
    glDisable(GL_TEXTURE_2D);
    GLfloat cubeMater[] = { 0.2, 0.2, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubeMater);
    gluQuadricDrawStyle(palla, GLU_FILL);
    gluQuadricNormals(palla, GLU_FLAT);
    gluSphere(palla, 0.5, 50, 100);
    glEnable(GL_TEXTURE_2D);
}
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
void draw_linea() {
    glColor3f(1, 0, 0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex3f(-15, -15, 0); glVertex3f(15, 15, 0);
    glEnd();
}
//------------------------------------------------------
void draw_pesce() {

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
    //s->computeAVGDir();

    //qua disegno
    for (int i = 0; i < s->getSchool().size(); i++) {
        //calcolo lo spostamento dei pesci
        s->getSchool()[i]->Nuota();
        glColor3f(1.0f, .0f, 1.0f);
        glPushMatrix();
        //traslo
        glTranslatef(s->getSchool()[i]->getPos()[0], s->getSchool()[i]->getPos()[1], s->getSchool()[i]->getPos()[2]);
        glRotatef(-s->getTheta() * 180 / 3.1415927, 0, 0, 1);
        draw_cube();
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(s->getCentro()[0], s->getCentro()[1], s->getCentro()[2]);
    glRotatef(-s->getTheta() * 180 / 3.1415927, 0, 0, 1);
    draw_palla();
    draw_linea();
    glPopMatrix();
    glLoadIdentity();
    gluLookAt(s->getCentro()[0], s->getCentro()[1], 60, s->getCentro()[0], s->getCentro()[1], s->getCentro()[2], 0, 1, 0);
}



//pesce con moto circolare
/*void draw_pesce2(void) {
    int i = 0;
    //i=0->ruta su piano xz i=1->ruota su piano xy, altri valori->bohhh
    cerchio.NuotainCerchio(t, i);
    //grafica del pesce
    glPushMatrix();
    glTranslated(cerchio.getPos()[0], cerchio.getPos()[1], cerchio.getPos()[2]);
    glCallList(SFERA);
    glPopMatrix();
}*/
//pesce con repulsione
/*void draw_pesce3(void) {
    //per vedere esplodere velocit� attivare e mettere posizione e velocit� del pesciolini[0] a 0 e silenziare pesciolino[0].setAcc
    /*if (pesciolini[1].getPos()[1] < -25)
    {
        float k[] = { 0, -pesciolini[1].getVel()[1], 0 };
        float kk[] = { 0, -25, 0 };
        pesciolini[1].setVel(k);
        pesciolini[1].setPos(kk);
    }*//*
    pesciolini[1].setAcc(RepulsiveForcesFish(pesciolini[0], pesciolini[1]));
    pesciolini[0].setAcc(RepulsiveForcesFish(pesciolini[1], pesciolini[0]));
    //grafica dei pesci
    for (int i = 0; i < 2; i++)
    {
        pesciolini[i].Nuota();
        glPushMatrix();
        glTranslated(pesciolini[i].getPos()[0], pesciolini[i].getPos()[1], pesciolini[i].getPos()[2]);
        glCallList(SFERA);
        glPopMatrix();
    }}*/

    //pesce con SetAccelerazione
    /*void draw_pesce4(void) {

        SetAccelerazioni(pozza);
        //grafica dei pesci
        for (int i = 0; i < pozza.size(); i++)
        {
            pozza[i].getSchool()[0]->Nuota();
            glPushMatrix();
            glTranslated(pozza[i].getSchool()[0]->getPos()[0], pozza[i].getSchool()[0]->getPos()[1], pozza[i].getSchool()[0]->getPos()[2]);
            glCallList(SFERA);
            glPopMatrix();
        }}*/


        //pesce con drawOcean
void draw_pesce5(void) {

    DrawOcean(pozza);
}
// ********************************************************************************************************
void draw_scene(void) {

    draw_pesce5();

    // ********************************************************************************************************
    /*void draw_scene(void) {

        draw_pesce();
    */
    glColor3f(0.1, 1.0, 0.1);		// redish
    //glFrontFace(GL_CW); 
    //glutSolidTeapot(0.5);			// draw the teapot
   //glutSolidTorus(1,2,30,30);			            // draw the torus
    //glutSolidCylinder(1,2,30,20);			            // draw the cylinder

}
