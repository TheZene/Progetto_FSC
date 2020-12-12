#define _USE_MATH_DEFINES
#include "Frame.h"
#include "Hole.h"
#include <stdlib.h>     
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "define.h"

#pragma once
//#define L 5
//#define SFERETTA 7


using namespace std;
class Fish {
private:
	float pos[DIMARR];
	float vel[DIMARR];
	float acc[DIMARR];
	Hole holes[8];
	float theta;
public:
	Fish();
	Fish(float* p, float* v, float* a);
	Fish(float* p, float* v);
	void setPos(float* p);
	void setVel(float* v);
	void setAcc(float* a);
	void setTheta(float t);
	float* getPos() { return pos; }
	float* getVel() { return vel; }
	float* getAcc() { return acc; }
	Hole* getHoles() { return holes; }
	float getTheta() { return theta; }
	void Nuota();
	void NuotainCerchio(float &t, int i);
	float computeTheta();
};
