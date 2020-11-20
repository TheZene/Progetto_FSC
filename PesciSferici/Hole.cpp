
#include "Hole.h"
#include <cmath>

double pi() { return 4.0 * atan(1.0); }
double angle54() { return 54 * pi() / 180; }
double angle30() { return 30 * pi() / 180; }



Hole::Hole(float* p, float* v, int n) {
    type = n;
    if (type < 5) Distance = LateralDistance;
    else if (type > 4)  Distance = VerticalDistance;
    AggiornaBuca(p, v);
    if (type == 1||type==2) color[0] = 0.80078125, color[1] = 0.640625, color[2] = 0.203125; //gold
    else if (type==3||type==4) color[0] =0.6, color[1] = 0.0666, color[2] =0.6; //violet
    else if (type == 5 || type == 6) color[0] = 1., color[1] = 1., color[2] = 1.; //white
    else if (type == 7 || type == 8) color[0] = 0., color[1] = 0., color[2] = 0.; //black
    //color[0]=0.99609375, color[1] = 0.7109375, color[2] = 0.75390625; pink
}

void Hole::AggiornaBuca(float* p, float* v) {
    angle[0] = askPhi(v);
    angle[1] = askTheta(v);
    //4 tipi di buche laterali: 1 e 2 dietro, 3 e 4 davanti (destra e sinistra)
    if (type == 1) angle[0] += pi() + angle54(), angle[1] = pi() - angle[1];
    else if (type == 2) angle[0] += pi() - angle54(), angle[1] = pi() - angle[1];
    else if (type == 3) angle[0] -= angle54();
    else if (type == 4) angle[0] += angle54();
    //4 tipi di buche verticali: 1 e 2 dietro, 3 e 4 davanti (sopra e sotto)
    else if (type == 5) angle[0] = pi() + angle[0], angle[1] = pi() - angle[1] - angle30();
    else if (type == 6) angle[0] = pi() + angle[0], angle[1] = pi() - angle[1] + angle30();
    else if (type == 7) angle[1] = pi() - angle[1] - angle30();
    else if (type == 8) angle[1] = pi() - angle[1] + angle30();
    //Trovo il vettore che va dal pesce alla buca
    pos[0] = Distance * sin(angle[1]) * cos(angle[0]);
    pos[1] = Distance * sin(angle[1]) * sin(angle[0]);
    pos[2] = cos(angle[1]);
    //vado in buca
    for (int i = 0; i < 3; i++) pos[i] += p[i];
}




float askModule(float* X) {
    return pow(X[0] * X[0] + X[1] * X[1] + X[2] * X[2],0.5);
}

float askPhi(float* X) {
    return atan2(X[1], X[0]);
}

float askTheta(float* X) {
    double t = atan(sqrt(X[0] * X[0] + X[1] * X[1]) / X[2]);
    if (X[2] >= 0) return t;
    else return t + 2 * acos(0.0); //se z<0 
}




//Vecchi dinosauri che aspettano il vostro consenso per essere eliminati
/*
void Hole::TraslaBuca(float* v) {
    for (int i = 0; i < 3; i++) pos[i] += v[i] * dt;
}

void Hole::RuotaBuca(float* p, float* angle) {
    float memory[2] = { angle[0], angle[1] };
    //trovo il vettore che va dal pesce alla buca
    for (int i = 0; i < 3; i++) pos[i] -= p[i];
    //angle[0]=delta phi->nuovo phi, angle[1]=delta theta->nuovo theta
    angle[0] += askPhi(pos);
    angle[1] = pi() - angle[1];
    //trovo il nuovo vettore che va dal pesce alla buca
    pos[0] = Distance * sin(angle[1]) * cos(angle[0]);
    pos[1] = Distance * sin(angle[1]) * sin(angle[0]);
    pos[2] = Distance * cos(angle[1]);
    //vado in buca
    for (int i = 0; i < 3; i++) pos[i] = p[i] + pos[i];
    angle[0] = memory[0];
    angle[1] = memory[1];

}
*/






