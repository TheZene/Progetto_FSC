#pragma once
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include "Fish.h"
#include "School.h"

void draw_scene(void);

//prova per potenziale repulsivo+attrattivo.
float pos1[3] = { 0  ,10, 1.0 };
float vel1[3] = { 0, -6, 0.2 };
float pos2[3] = {0, 0, 0 };
float vel2[3] = { 0.3, 0.7, 0.1 };/*

float pos3[3] = { 3, -3, -0.2 };
float vel3[3] = { -0.3, 0.2, 0.3 };

float pos4[3] = { 2., -0.3, 0.5 };
float vel4[3] = { 1, 0.8, -0.3 };*/

Fish uno (pos1, vel1);
Fish due(pos2, vel2);/*
Fish tre(pos3, vel3);
Fish quattro(pos4, vel4);*/
School un(&uno);
School du(&due);/*
School tr(&tre);
School qu(&quattro);*/
vector<School> pozza = { un, du/*, tr, qu*/};