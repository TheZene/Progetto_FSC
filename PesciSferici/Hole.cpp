
#include "Hole.h"
#include <cmath>

double pi = 4.0 * atan(1.0);

//la seguente costruzione è valida solo se v[2]=0!!!

Hole::Hole(float* p, float* v, int type) {
    //Per evitare errori
    if (abs(v[2]) < 0.0000001)
    {
        v[2] = 0;
        //buche laterali
        if (type < 5)
        {
            Distance = LateralDistance;
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
            for (int i = 0; i < 3; i++) pos[i] = (Distance / askModule(v)) * pos[i] + p[i];
        }
        //buche verticali
        else if (type > 4)
        {
            float phi;
            Distance = VerticalDistance;
            //4 tipi di buche verticali: 1 e 2 dietro, 3 e 4 davanti (sopra e sotto)
            if (type == 1) MagicAngle = 30 * 3.14159 / 180, phi=-askPhi(v);
            else if (type == 2) MagicAngle = -30 * 3.14159 / 180, phi = -askPhi(v);
            else if (type == 3) MagicAngle = 30 * 3.14159 / 180, phi = askPhi(v);
            else if (type == 4)  MagicAngle = -30 * 3.14159 / 180, phi = askPhi(v);
            //Trovo il vettore che va dal pesce alla buca
            pos[0] = Distance * sin(MagicAngle) * cos(phi);
            pos[1] = Distance * sin(MagicAngle) * sin(phi);
            pos[2] = Distance * cos(MagicAngle);
            //vado in buca
            for (int i = 0; i < 3; i++) pos[i]+=p[i];
        }
    }
    //Nel caso il pesce sia stato inizializzato con Vz!=0 le buche vanno tutte nell'origine (errore!)
    else
    {
        pos[0] = pos[1] = pos[2] = 0;
        std::cout << "buche off";
    }
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

void Hole::TraslaBuca(float* v) {
    for (int i = 0; i < 3; i++) pos[i] += v[i] * dt;
}

void Hole::RuotaBuca(float* p, float* angle) {
    float memory[2] = { angle[0], angle[1] };
    //trovo il vettore che va dal pesce alla buca
    for (int i = 0; i < 3; i++) pos[i] -= p[i] ;
    //angle[0]=delta phi->nuovo phi, angle[1]=delta theta->nuovo theta
    angle[0] += askPhi(pos);
    angle[1] = pi-angle[1];
    //trovo il nuovo vettore che va dal pesce alla buca
    pos[0] = Distance * sin(angle[1]) * cos(angle[0]);
    pos[1] = Distance * sin(angle[1]) * sin(angle[0]);
    pos[2] = Distance * cos(angle[1]);
    //vado in buca
   for (int i = 0; i < 3; i++) pos[i] = p[i] + pos[i];
   angle[0] = memory[0];
   angle[1] = memory[1];
    
}







