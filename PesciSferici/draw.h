#pragma once
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include "Pesce.h"
#include "School.h"

bool init = false;
void normale9f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
void draw_scene(void);
void draw_pesce2(void);

//prova per le buche. Per avere moto circolare su piano xy: vy=10, su piano xz vz=10
/*float posizione[3] = { 10,10,0 };
float velocità[3] = {0, 0, 10 };
float accelerazione[3] = { 0, 0, 0};
Pesce cerchio (posizione, velocità, accelerazione);
float t = 0;*/

//prova per potenziale repulsivo.
/*loat posizione[3] = { 0,-20,0 };
float velocità[3] = { 0, 10, 0 };
float posizione1[3] = { -20, 0,0 };
float velocità1[3] = { 10, 0, 0 };
Pesce fermo (posizione1, velocità1); 
Pesce collidente(posizione, velocità);
Pesce pesciolini[2] = { fermo, collidente };*/

//prova per potenziale repulsivo+attrattivo.
float posizione1[3] = { 0  ,10, 1.0 };
float velocità1[3] = { 0, -6, 0.2 };

float posizione2[3] = {0, 0, 0 };
float velocità2[3] = { 0.3, 0.7, 0.1 };

float posizione3[3] = { 3, -3, -0.2 };
float velocità3[3] = { -0.3, 0.2, 0.3 };

float posizione4[3] = { 2., -0.3, 0.5 };
float velocità4[3] = { 1, 0.8, -0.3 };

Pesce uno (posizione1, velocità1);
Pesce due(posizione2, velocità2);
Pesce tre(posizione3, velocità3);
Pesce quattro(posizione4, velocità4);
School un(&uno);
School du(&due);
School tr(&tre);
School qu(&quattro);
vector<School> pozza = { un, du, tr, qu};

/*void draw_palla(void);
void draw_tetra(void);*/
void draw_cube(void);

