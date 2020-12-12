#pragma once
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include "Fish.h"
#include "School.h"

void draw_scene(void);

//prova per potenziale repulsivo+attrattivo.
float posizione1[3] = { 1  ,10, .0 };
float velocità1[3] = { 0, -1.80, 0. };

float posizione2[3] = { -1, -10, 0 };
float velocità2[3] = { 0, 6, 0. };

float posizione3[3] = { 3, -3, -0.2 };
float velocità3[3] = { -0.3, 0.2, 0.3 };

float posizione4[3] = { 2., -0.3, 0.5 };
float velocità4[3] = { 1, 0.8, -0.3 };

float posizione5[3] = { 5., -0.3, 0. };
float velocità5[3] = { 5, 2, -0. };

float posizione6[3] = { 12., -6, 2 };
float velocità6[3] = { -8, -3, -0.0 };

float posizione7[3] = { -20., -0.3, 0.5 };
float velocità7[3] = { 4, 0.8, -0.3 };

float posizione8[3] = { 5., -6.3, 0. };
float velocità8[3] = { 2, -1, -0. };

float posizione9[3] = { 8., -6, 0 };
float velocità9[3] = { -1, -1.3, -0.0 };

float posizione10[3] = { -2., -3.3, 0.5 };
float velocità10[3] = { 1.9, 0.8, -0.3 };

Fish uno(posizione1, velocità1);
Fish due(posizione2, velocità2);
Fish tre(posizione3, velocità3);
Fish quattro(posizione4, velocità4);
Fish cinque(posizione5, velocità5);
Fish sei(posizione6, velocità6);
Fish sette(posizione7, velocità7);
Fish otto(posizione8, velocità8);
Fish nove(posizione9, velocità9);
Fish dieci(posizione10, velocità10);
School un(&uno);
School du(&due);
School tr(&tre);
School qu(&quattro);
School ci(&cinque);
School se(&sei);
School set(&sette);
School ot(&otto);
School nov(&nove);
School die(&dieci);
vector<School> pozza = { un, du, tr, qu, ci, se, set, ot, nov, die };