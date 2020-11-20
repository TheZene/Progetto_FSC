#include "Pesce.h"
#include <iostream>
Pesce::Pesce() {
    float arr[3] = { 0.0, 0.0, 0.0 };
    setPos(arr);
    setVel(arr);
    setAcc(arr);
    setTheta(0.0);
    if (vel[2]==0)
        for (int i = 1; i < 5; i++) holes[i] = Hole(pos, vel, i);
}

Pesce::Pesce(float* p, float* v, float* a) {
    //assuming everything has the same size, as it should be
    setPos(p);
    setVel(v);
    setAcc(a);
    if (vel[2] == 0)
        for (int i = 1; i < 5; i++) holes[i] = Hole(pos, vel, i);
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
        pos[k] += vel[k]*0.1;
    }
    for (int i = 1; i < 5; i++) holes[i].TraslaBuca(vel);
}

void Pesce::NuotainCerchio(float &t) {
    float oldPos[3];
    float angle[2];
    for (int i = 1; i < 3; i++) oldPos[i] = pos[i];
    acc[0] = -10 * cos(t);
    acc[1] = -10*sin(t);
    acc[2] = 0;
    Nuota();
    angle[0] = askPhi(vel);
    angle[1] = askPhi(vel);
    for (int k = 0; k < DIMARR; ++k) vel[k] += acc[k] * 0.1;
    angle[0] = askPhi(vel) - angle[0];
    angle[1] = askTheta(vel) - angle[1];
    for (int i = 1; i < 5; i++) holes[i].RuotaBuca(pos, angle);
    t += 0.1;

}

float Pesce::computeTheta() {
    return atan2f(vel[1], vel[0])*(180/M_PI);
}