#include "Pesce.h"
#include <iostream>

Pesce::Pesce() {
    float arr[3] = { 0.0, 0.0, 0.0 };
    setPos(arr);
    setVel(arr);
    setAcc(arr);
    setTheta(0.0);
    for (int i = 0; i < 2; i++) holes[i] = Hole(pos, vel, i+1);
}

Pesce::Pesce(float* p, float* v, float* a) {
    //assuming everything has the same size, as it should be
    setPos(p);
    setVel(v);
    setAcc(a);
    for (int i = 0; i < 2; i++) holes[i] = Hole(pos, vel, i+1);
    
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
    //registra phi e theta iniziali
    float angle[2];
    angle[0] = askPhi(vel);
    angle[1] = askTheta(vel);
    //incremento della posizione e della velocità del pesce
    for (int k = 0; k < DIMARR; ++k)
    {
        pos[k] += vel[k] * dt;
        vel[k] += acc[k] * dt;
    }
    
    //calcola variazione phi e theta
    angle[0] = askPhi(vel) - angle[0];
    //movimenti e grafica delle buche
    for (int i = 0; i < 2; i++)
    {
        holes[i].TraslaBuca(vel);
        //moto grafico delle buche:
        glColor3f(.0f, 1.0f, 0.0f);
        glPushMatrix();
        glTranslated(holes[i].getPos()[0], holes[i].getPos()[1], holes[i].getPos()[2]);
        glCallList(BUCA);
        glPopMatrix();
    
        holes[i].RuotaBuca(pos, angle);
    }
}

void Pesce::NuotainCerchio(float &t) {
    float oldPos[3];
    for (int i = 1; i < 3; i++) oldPos[i] = pos[i];
    acc[0] = -15 * cos(t);
    acc[1] = -15*sin(t);
    acc[2] = 0;
    Nuota();  
    t +=dt;
}

float Pesce::computeTheta() {
    return atan2f(vel[1], vel[0])*(180/M_PI);
}