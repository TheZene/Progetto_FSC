
#pragma once

#include<vector>
#include <iostream>
#include "define.h"


float askTheta(float* X);
float askPhi(float* X);
float askModule(float* X);


struct Hole {
private:
	float pos[3];
	float angle[2];
	float color[3];
	float Distance;
	int type;
	float force;
	
public:
	float* getPos() { return pos; }
	float* getCol() { return color; }
	float getForce() { return force; }
	void AggiornaBuca(float* p, float* v);
	Hole(float* p, float* v, int n);
	Hole() {}

	//Vecchi dinosauri che aspettano il vostro consenso per essere eliminati
	/*void TraslaBuca(float* v);
	void RuotaBuca(float* p, float *angle);*/
};






