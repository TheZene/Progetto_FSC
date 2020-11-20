
#pragma once

#include<vector>
#include <iostream>

float askTheta(float* X);
float askPhi(float* X);
float askModule(float* X);


struct Hole {
private:
	float pos[3];
	//float theta;	//angolo azimut
	//float phi;	//angolo nel piano xy
	float MagicAngle;
	float Distance=3;
public:
	float* getPos() { return pos; }
	void TraslaBuca(float* v);
	void RuotaBuca(float* p, float *angle);
	Hole(float* p, float* v, int type);
	Hole() {}
};






