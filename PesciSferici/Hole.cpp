
#include "Hole.h"
#include <cmath>


//la seguente costruzione è valida solo se v[2]=0!!!

Hole::Hole(float* p, float* v, int type) {
    //4 tipi di buche laterali: 1 e 2 dietro, 3 e 4 davanti (destra e sinistra)
    if (type == 1) MagicAngle = 126 * 3.14159 / 180;
    else if (type == 2) MagicAngle = -126 * 3.14159 / 180;
    else if (type == 3) MagicAngle = 54 * 3.14159 / 180;
    else if (type == 4)  MagicAngle = -54 * 3.14159 / 180;
    //ruoto il vettore velocità dell'angolazione giusta
    pos[0] = (cos(MagicAngle) * v[0] + sin(MagicAngle) * v[1]);
    pos[1] = (-sin(MagicAngle) * v[0] + cos(MagicAngle) * v[1]);
    pos[2] = 0;
    //normalizzo il vettore alla distanza e lo sommo al vettore posizione del pesce->vado in buca
    for (int i = 0; i < 3; i++) pos[i] = (Distance / Module(v)) * pos[i] + p[i];
}

float getModule(float* X) {
    return X[0] * X[0] + X[1] * X[1] + X[2] * X[2];
}

float askPhi(float* X) {
    return atan2(X[1], X[0]);
}

float askTheta(float* X) {
    double t = atan(sqrt(X[0] * X[0] + X[1] * X[1]) / X[2]);
    if (X[2] >= 0) return t;
    else return t + 2 * acos(0.0); //se z<0 
}

void Hole::TraslaBuca(float* v) {
    for (int i = 0; i < 3; i++) pos[i] += v[i] * 0.1;
}

void Hole::RuotaBuca(float* p, float* angle) {
    //trovo il vettore che va dal pesce alla buca
    for (int i = 0; i < 3; i++) pos[i] = p[i]-pos[i];
    //angle[0]=delta phi->nuovo phi, angle[1]=delta theta->nuovo theta
    angle[0] += askPhi(pos);
    angle[1] = askTheta(pos)-angle[1];
    //trovo il nuovo vettore che va dal pesce alla buca
    pos[0] = Distance * sin(angle[1]) * cos(angle[0]);
    pos[1] = Distance * sin(angle[1]) * sin(angle[0]);
    pos[2] = Distance * cos(angle[1]);
    //vado in buca
    for (int i = 0; i < 3; i++) pos[i] = p[i] + pos[i];
}







