#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include <thread>

#include "draw.h"
#include "Frame.h"

double phi(double x, double y) {
    return atan2(y, x);
}

double theta(double x, double y, double z) {
    double t = atan(sqrt(x * x + y * y) / z);
    if (z >= 0) return t;
    else return t + 2 * acos(0.0);
}

double distance(double x, double y, double z)
{
    double dist = 0;
    double xs[] = { x, y, z };
    /*for (int i = 0; i < 3; ++i)
        dist += pow((xs[i] - Xp[i]), 2);*/
    return sqrt(dist);
}

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

void draw_pesce() {
    //se non ho inizializzato la struttura dati la inizializzo
    if (!init) {
        float arr0[3][3] = { { 4.0, -4.0, 0.0 },
                             { 0.0, 0.0, 0.0 }, 
                             { -4.0, -4.0, 0.0 } };
        float arr1[3] = { 0.0, 1.0, 0.0 };
        float arr2[3] = { 0.0, 0.0, 0.0 };
        Pesce* p1 = new Pesce(arr0[0], arr1, arr2);
        Pesce* p2 = new Pesce(arr0[1], arr1, arr2);
        Pesce* p3 = new Pesce(arr0[2], arr1, arr2);
        s->addPesce(p1);
        s->addPesce(p2);
        s->addPesce(p3);
        init = true;
    }
    //ottengo il banco di pesci
    s->getShoal();
    //qua calcolo la direzione del banco media (in teoria pesata perche' chi sta avanti comanda)
    s->computeAVGDir();

    //qua disegno
    for (int i = 0; i < s->getShoal().size(); i++) {
        //calcolo lo spostamento dei pesci
        s->getShoal()[i]->Nuota();
        glColor3f(1.0f, .0f, 1.0f);     
        glPushMatrix();
        //traslo
        glTranslated(s->getShoal()[i]->getPos()[0], s->getShoal()[i]->getPos()[1], s->getShoal()[i]->getPos()[2]);
        glCallList(SFERA);
        glPopMatrix();
    }

}
// ********************************************************************************************************
void draw_scene(void) {

    draw_pesce();

    glColor3f(0.1, 1.0, 0.1);		// redish
    //glFrontFace(GL_CW); 
    //glutSolidTeapot(0.5);			// draw the teapot
   //glutSolidTorus(1,2,30,30);			            // draw the torus
    //glutSolidCylinder(1,2,30,20);			            // draw the cylinder

}
