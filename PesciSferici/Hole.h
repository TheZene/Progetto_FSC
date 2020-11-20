
#pragma once

#include<vector>
#include <iostream>

#define dt 0.001
#define LateralDistance 4
#define VerticalDistance 2

float askTheta(float* X);
float askPhi(float* X);
float askModule(float* X);


struct Hole {
private:
	float pos[3];
	//float theta;	//angolo azimut
	//float phi;	//angolo nel piano xy
	float MagicAngle;
	float Distance;
public:
	float* getPos() { return pos; }
	void TraslaBuca(float* v);
	void RuotaBuca(float* p, float *angle);
	Hole(float* p, float* v, int type);
	Hole() {}
};






