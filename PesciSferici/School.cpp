#include "School.h"
School::School(vector<Pesce*> s) {
	for (int i = 0; i < s.size(); i++)
		school.push_back(s[i]);
	for (int i = 0; i < 3; i++) dir[i] = 0;
}

void School::setDir(float* arr) {
	for (int i = 0; i < 3; i++) dir[i] = arr[i];
}

void School::computeAVGDir() {
	int i = 0;
	float totV[] = { 0.0, 0.0, 0.0 };
	float totP[] = { 0.0, 0.0, 0.0 };
	resetMinMax();
	float valP = 0;
	float valV = 0.0;
	for (i = 0; i < school.size(); i++) {
		for (int j = 0; j < DIMARR; j++) {
			valV = school[i]->getVel()[j];
			valP = school[i]->getPos()[j];
			totV[j] += valV;
			totP[j] += valP;
			if (max[j] < valP) max[j] = valP;
			if (min[j] > valP) min[j] = valP;
		}
	}
	theta = atan2f(totV[1], totV[0]);
	for (int i = 0; i < DIMARR; i++)
		//dimensions[i] = max[i] - min[i];
		centro[i] = totP[i] / school.size();
}

//TODO: calcolare l'asse per centrare il banco di pesci
//ossia calcolare la lunghezza del banco (EZ) e calcolare l'angolo della direzione media del banco (?)
//come se calcola l'angolo, in base a cosa? Che poi in realtà sono due angoli, uno tra x,z e uno tra x,y o z,y dipende