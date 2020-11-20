#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define LIGHT 1
#define SFERA 44

class Frame : public Fl_Gl_Window {
private:
	void draw();
	void init();
	int handle_mouse(int event, int button, int x, int y);
	int handle_key(int event, int key);
public:
	double ruotaX, ruotaY, ruotaZ, zoom;
	int  handle(int);
	Frame(int x, int y, int w, int h, const char* l = 0) : Fl_Gl_Window(x, y, w, h, l) {}
};


