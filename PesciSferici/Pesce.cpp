#include "Pesce.h"
#include <iostream>

Pesce::Pesce(vector<float> p, vector<float> v, vector<float> a) {
    //assuming everything has the same size, as it should be
    setPos(p);
    setVel(v);
    setAcc(a);
}
void Pesce::setPos(vector<float> p) {
	for (int i = 0; i < p.size(); i++)
		pos[i] = p[i];
}

void Pesce::setVel(vector<float> v) {
	for (int i = 0; i < v.size(); i++)
		vel[i] = v[i];
}

void Pesce::setAcc(vector<float> a) {
	for (int i = 0; i < a.size(); i++)
		acc[i] = a[i];
}

void Pesce::Nuota() {
    //always same size
    for (int k = 0; k < 3; ++k){
        pos[k] += vel[k] * 0.001;
        //if (abs(Xp_[k]) > (L - 0.5)) Vp_[k] *= -1;  //inversione del moto
    }
}
