#include "Pesce.h"
#include <iostream>

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

void Pesce::Nuota() {
    //always same size
    for (int k = 0; k < DIMARR; ++k){
        pos[k] += vel[k] * 0.001;
        printf("%d, %f ", k, pos[k]);
        //if (abs(Xp_[k]) > (L - 0.5)) Vp_[k] *= -1;  //inversione del moto
    }
}
