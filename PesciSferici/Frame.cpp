
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>

#include "Frame.h"
#include "Pesce.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


#define LIGHT

extern void draw_scene();
extern void stampa(const char* messaggio);

//-----------------------------------------------------------------------------------------------
void Frame::init(void) {
    gl_font(FL_HELVETICA_BOLD, 16);
    GLUquadricObj* palla;
    palla = gluNewQuadric();
    gluQuadricDrawStyle(palla, GLU_FILL);
    gluQuadricNormals(palla, GLU_FLAT);

    glNewList(SFERA, GL_COMPILE);
    glColor3f(1.0f, .0f, .0f);
    gluSphere(palla, 0.5, 30, 30);
    glEndList();

}
//-----------------------------------------------------------------------------------------------


void Frame::draw() {
    if (!valid()) {
#if defined(LIGHT)

        GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
        GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
        GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glShadeModel(GL_SMOOTH);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glClearColor(0.0, 0.0, 0.0, 1.0);

#endif // LIGHT            
        glClearColor(0.0, 0.0, .5, .6);                        // Turn the background color white
        glViewport(0, 0, w(), h());                               // Make our viewport the whole window
        glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
        glLoadIdentity();                                      // Reset The Projection Matrix
        gluPerspective(45.0f, w() / h(), 1, 200.0f);
        glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
        glLoadIdentity();                                      // Reset The Modelview Matrix
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
        glLoadIdentity();                                      // Reset The View
        gluLookAt(0, 0, 60, 0, 0, 0, 0, 1, 0);        // Position - View  - Up Vector
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        init();
        valid(1);
    }

    //glClear(GL_DEPTH_BUFFER_BIT); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotated(ruotaZ, 0, 0, 1); 
    glRotated(ruotaX, 1, 0, 0); 
    glRotated(ruotaY, 0, 1, 0);
    glScalef(zoom, zoom, zoom);
   
    draw_scene();
    glPopMatrix();
}
//-----------------------------------------------------------------------------------------------
int Frame::handle(int evento)
{
    int ix, iy;
    static char  messaggio[50] = { 0 };
    switch (evento)
    {
    case FL_MOVE:
        ix = Fl::event_x();
        iy = Fl::event_y();
        sprintf_s(messaggio, "  ix=%d iy=%d\n", ix, iy); stampa(messaggio);
    default:
        break;
    }
    redraw();
    return 1;
}
//-----------------------------------------------------------------------------------------------
