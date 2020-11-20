#define _CRT_SECURE_NO_WARNINGS
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Enumerations.H>

#include "Frame.h"
#include "Pesce.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


#define LIGHT

extern void draw_scene();
extern void stampa(const char* messaggio);
char* foo;

void rotate(int deg, int x, int y, int z) {
    glMatrixMode(GL_MODELVIEW);
    glRotatef(deg, x, y, z);
}
//-----------------------------------------------------------------------------------------------
void Frame::init(void) {
    label("Demo Window for CS 559");
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
        glClearColor(0.0, 0.0, .5, .6);                        // Turn the background color blue
        glViewport(0, 0, w(), h());                            // Make our viewport the whole window
        glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
        glLoadIdentity();                                      // Reset The Projection Matrix
        gluPerspective(45.0f, w() / h(), 1, 200.0f);
        glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
        glLoadIdentity();                                      // Reset The Modelview Matrix
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
        glLoadIdentity();                                      // Reset The View
        gluLookAt(0.0, 0.0, 60, 0, 0, 0, 0, 1, 0);        // Position - View  - Up Vector
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        init();
        valid(1);
    }

    //glClear(GL_DEPTH_BUFFER_BIT); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_scene();

    /*glPushMatrix();
    glRotated(ruotaZ, 0, 0, 1); 
    glRotated(ruotaX, 1, 0, 0); 
    glRotated(ruotaY, 0, 1, 0);
    glScalef(zoom, zoom, zoom);
   
    glPopMatrix();*/
}
//-----------------------------------------------------------------------------------------------
/*int Frame::handle(int evento)
{
    int ix, iy;
    static char  messaggio[50] = { 0 };
    switch (evento){
    case FL_MOVE: {
        ix = Fl::event_x();
        iy = Fl::event_y();
        //sprintf_s(messaggio, "  ix=%d iy=%d\n", ix, iy); stampa(messaggio);
    };
    /*case FL_SHORTCUT: {
        if (Fl::event_key() == FL_Up) {
            camRotateUpX;
            Fl::unfocus();
        }
        return 0;
    };
    default: {
        break;
    };
    return 1;
    
    }
    return 0;
}*/
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
    switch (button) {
    case 1: // LMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        if (event == FL_PUSH) {
            //sprintf(foo, "LMB PUSH ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        else if (event == FL_DRAG) {
            //mi sposto lungo le y, ruoto in base a se y < prevy o y > prevy
            if (prevx == x) 
            //viceversa 
            /*else if (prevy == y)
            else prevx = x;*/


            //sprintf(foo, "LMB Drag ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        else if (event == FL_RELEASE) {
            //sprintf(foo, "LMB Release ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        break;
    case 2: // MMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        if (event == FL_PUSH) {
            //sprintf(foo, "MMB Push ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        else if (event == FL_DRAG) {
            //sprintf(foo, "MMB Drag ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        else if (event == FL_RELEASE) {
            //sprintf(foo, "MMB Release ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        break;
    case 3: // RMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        if (event == FL_PUSH) {
            //sprintf(foo, "RMB Push ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        else if (event == FL_DRAG) {
            //sprintf(foo, "RMB Drag ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        else if (event == FL_RELEASE) {
            //sprintf(foo, "RMB Release ( %d , %d )", x, y);
            //label(foo);
            damage(1);
        }
        break;
    }
    return ret;
}

int Frame::handle_key(int event, int key) {
    switch (key) {
    case 's':  //label("letter c was depressed");
        rotate(-2, 1, 0, 0);
        damage(1);
        return 1;
    case 'q':  //label("letter c was depressed");
        rotate(-2, 0, 1, 0);
        damage(1);
        return 1;
    case 'w':  //label("letter c was depressed");
        rotate(2, 2, 0, 0);
        damage(1);
        return 1;
    case 'e':  //label("letter c was depressed");
        rotate(2, 0, 1, 0);
        damage(1);
        return 1;
    case 'd':  //label("letter c was depressed");
        rotate(2, 0, 0, 1);
        damage(1);
        return 1;
    case 'a':  //label("letter c was depressed");
        rotate(-2, 0, 0, 1);
        damage(1);
        return 1;
    default:  //label("Nothing to do!");
        damage(1);
        printf("nothing to do\n");
        return 1;
    }
}