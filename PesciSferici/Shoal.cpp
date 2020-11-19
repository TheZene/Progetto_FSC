#include "Shoal.h"
#include <iostream>
Shoal::Shoal(vector<Pesce*> s) {
	for (int i = 0; i < s.size(); i++)
		shoal.push_back(s[i]);
	for (int i = 0; i < 3; i++) dir[i] = 0;
}

void Shoal::setDir(float* arr) {
	for (int i = 0; i < 3; i++) dir[i] = arr[i];
}

void Shoal::computeAVGDir() {
	int i = 0;
	float appArr[] = { 0.0, 0.0, 0.0 };
	for (i = 0; i < shoal.size(); i++) {
		for (int j = 0; j < 3; j++) {
			appArr[j] += shoal[i]->getPos()[j] ;
		}
	}
	for (i = 0; i < shoal.size(); i++) {
		//TOOD:aggiungi calcoli rivedi sto metodo che stavi già con la testa da un'altra parte
	}
	//printf("%f, %f, %f ", appArr[0], appArr[1], appArr[2]);
}

//TODO: calcolare l'asse per centrare il banco di pesci
//ossia calcolare la lunghezza del banco (EZ) e calcolare l'angolo della direzione media del banco (?)
//come se calcola l'angolo, in base a cosa? Che poi in realtà sono due angoli, uno tra x,z e uno tra x,y o z,y dipende