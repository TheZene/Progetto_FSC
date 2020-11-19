#include "Pesce.h"
#include <iostream>
Pesce::Pesce() {
    float arr[3] = { 0.0, 0.0, 0.0 };
    setPos(arr);
    setVel(arr);
    setAcc(arr);
    setTheta(0.0);
}

Pesce::Pesce(float* p, float* v, float* a) {
    //assuming everything has the same size, as it should be
    setPos(p);
    setVel(v);
    setAcc(a);
}
void Pesce::setPos(float* p) {
	for (int i = 0; i < DIMARR; i++)
		pos[i] = p[i];
}

void Pesce::setVel(float* v) {
	for (int i = 0; i < DIMARR; i++)
		vel[i] = v[i];
}

void Pesce::setAcc(float* a) {
	for (int i = 0; i < DIMARR; i++)
		acc[i] = a[i];
}


void Pesce::setTheta(float t) {
    theta = t;
}

void Pesce::Nuota() {
    for (int k = 0; k < DIMARR; ++k){
        pos[k] += vel[k]*0.002;
    }
}


float Pesce::computeTheta() {
    return atan2f(vel[1], vel[0])*(180/M_PI);
}