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
	float appArr[] = { 0.0, 0.0, 0.0 };
	float thetaTot = 0.0;
	for (i = 0; i < school.size(); i++) {
		for (int j = 0; j < 3; j++) {
			appArr[j] += school[i]->getVel()[j] ;
		}
	}
	thetaTot = atan2f(appArr[1], appArr[0]) / school.size()* (180 / M_PI);
	
	//printf("%f, %f, %f ", appArr[0], appArr[1], appArr[2]);
}

//TODO: calcolare l'asse per centrare il banco di pesci
//ossia calcolare la lunghezza del banco (EZ) e calcolare l'angolo della direzione media del banco (?)
//come se calcola l'angolo, in base a cosa? Che poi in realtà sono due angoli, uno tra x,z e uno tra x,y o z,y dipende