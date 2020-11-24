#define _CRT_SECURE_NO_WARNINGS
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Enumerations.H>

#include "Frame.h"
#include "Fish.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


#define LIGHT

extern void draw_scene();
extern void stampa(const char* messaggio);
char* foo;
int flag = 0;

void Frame::init(void) {
   
    gl_font(FL_HELVETICA_BOLD, 16);
    GLUquadricObj* palla;
    palla = gluNewQuadric();
    gluQuadricDrawStyle(palla, GLU_FILL);
    gluQuadricNormals(palla, GLU_FLAT);
    glNewList(SFERA, GL_COMPILE);
    glColor3f(1.0f, .0f, .0f);
    gluSphere(palla, 0.8, 30, 30);
    glEndList();

    glNewList(CENTRO, GL_COMPILE);
    glColor3f(.5f, .5f, .5f);
    gluSphere(palla, 0.1, 30, 30);
    glEndList();

    //per disegnare le buche (giusto per vedere se sono nelle posizioni giuste)
    GLUquadricObj* buca;
    buca = gluNewQuadric();
    gluQuadricDrawStyle(buca, GLU_FILL);
    gluQuadricNormals(buca, GLU_FLAT);

    glNewList(BUCA, GL_COMPILE);
    gluSphere(buca, 0.1, 30, 30);
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
        glClearColor(0.0, 0.0, .5, .6);                        // Turn the background color blue
        glViewport(0, 0, w(), h());                            // Make our viewport the whole window
        glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
        glLoadIdentity();                                      // Reset The Projection Matrix
        gluPerspective(45.0f, w() / h(), 1, 200.0f);
        glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
        glLoadIdentity();                                      // Reset The Modelview Matrix
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
       // glLoadIdentity();                                      // Reset The View
       // gluLookAt(0.0, 0.0, 120, 0, 0, 0, 0, 1, 0);        // Position - View  - Up Vector
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        init();
        valid(1);
    }

    //glClear(GL_DEPTH_BUFFER_BIT); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_scene();
}

//-----------------------------------------------------------------------------------------------
int Frame::handle(int event) {

    switch (event) {
    case FL_PUSH:
        //return handle_mouse(event, Fl::event_button(), Fl::event_x(), Fl::event_y());
    case FL_RELEASE:
    case FL_DRAG:
        return handle_mouse(event, Fl::event_button(), Fl::event_x(), Fl::event_y());
    case FL_MOVE:
        return handle_mouse(event, Fl::event_button(), Fl::event_x(), Fl::event_y());
    case FL_FOCUS:
        label("Gained focus");
        damage(1);
        return 1;
    case FL_UNFOCUS:
        label("Lost focus");
        damage(1);
        return 1;
    default:
        return Fl_Window::handle(event);
    case FL_KEYBOARD:  return handle_key(event, Fl::event_key());
    };
}

int Frame::handle_mouse(int event, int button, int x, int y) {
    foo = new char[100];
    int ret = 0;
    int spostamentox;
    int spostamentoy;
    switch (button) {
    case 1: // LMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        //TODO: fix rotations to camera 
        if (event == FL_PUSH) {
            //inizializzo le posizioni in cui clicko
            prevx = x;
            prevy = y;
        }
        else if (event == FL_DRAG) {
            //
            spostamentox = prevx - x;
            spostamentoy = prevy - y;
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
            glRotatef(-spostamentox, 0, 1, 0);
            glRotatef(-spostamentoy, 1, 0, 0);

            prevx = x;
            prevy = y;
            
            /**/
        }
        else if (event == FL_RELEASE) {
            spostamentox = prevx - x;
            spostamentoy = prevy - y;
            glRotatef(-spostamentox, 0, 1, 0);
            glRotatef(-spostamentoy, 1, 0, 0);
        }
        break;
    case 2: // MMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        if (event == FL_PUSH) {
            
        }
        else if (event == FL_DRAG) {
            
        }
        else if (event == FL_RELEASE) {
            
        }
        break;
    case 3: // RMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        if (event == FL_PUSH) {
            
        }
        else if (event == FL_DRAG) {
            
        }
        else if (event == FL_RELEASE) {
           
        }
        break;
    }
    return ret;
}

int Frame::handle_key(int event, int key) {
    switch (key) {
    case 's':  //label("letter c was depressed");
        glRotatef(-4, 1, 0, 0);
        damage(1);
        return 1;
    case 'q':  //label("letter c was depressed");
        glRotatef(-4, 0, 1, 0);
        damage(1);
        return 1;
    case 'w':  //label("letter c was depressed");
        glRotatef(4, 2, 0, 0);
        damage(1);
        return 1;
    case 'e':  //label("letter c was depressed");
        glRotatef(4, 0, 1, 0);
        damage(1);
        return 1;
    case 'd':  //label("letter c was depressed");
        glRotatef(4, 0, 0, 1);
        damage(1);
        return 1;
    case 'a':  //label("letter c was depressed");
        glRotatef(-4, 0, 0, 1);
        damage(1);
        return 1;
    default:  //label("Nothing to do!");
        damage(1);
        printf("nothing to do\n");
        return 1;
    }
}