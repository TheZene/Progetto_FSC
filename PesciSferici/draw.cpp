#pragma once

#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include <thread>
#include "draw.h"
#include "Frame.h"

extern void DrawOcean(vector<School>& Oceano);

//pesce con drawOcean
void draw_scene(void) {
    DrawOcean(pozza);
    glColor3f(0.1, 1.0, 0.1);		// redish
}
