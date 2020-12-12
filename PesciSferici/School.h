#pragma once
#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <math.h>
#include "Fish.h"




/*Class: School
* Description: classe che descrive un banco di pesci
* 
* Attributes:
*	school: vector di classe pesce
*	dir: array delle direzioni verso le quali si può muovere il banco
*Methods: 
*	i primi tre sono costruttori, il primo vuoto per dovere, il secondo passando solo un pesce, il terzo passando un vector di pesci
*	setDir: setter per l'array di direzioni
*	addPesce: aggiunge un pesce al vector
*	getShoal: restituisce il vector contenente tutti i pesci del banco
*	computeAVGDir: calcola la direzione "media" del banco dei pesci (per ora coordinate cartesiane)
*/
class School {
private:
	vector<Fish*> school; 
	float dir[3]; 
	float dimensions[3]; //dimensioni del banco (lunghezza, larghezza, altezza, modellato come un cilindro
	float max[3] = { 0, 0, 0 };
	float min[3] = { 0, 0, 0 };
    float mid[3]; //fulcro attorno al quale i pesci si stringono in presenza di un predatore
	float phi;
	float theta;
public:
	School() { dir[0] = 0.0; dir[1] = 0.0; }
	School(Fish* p) { dir[0] = 0.0; dir[1] = 0.0; school.push_back(p); }
	School(vector<Fish*> s);
	void setDir(float* arr);
	void addPesce(Fish* p) { school.push_back(p); }
	vector<Fish*> getSchool() { return school; }
	void computeAVGDir();
	void Merge(School S);
	vector<School> split();
	void DrawSchool();
	void DrawOcean(vector<School>& Oceano);
	float* getMid() { return mid; }
	float getTheta() { return theta;  }
	void resetMinMax() { for (int i = 0; i < DIMARR; i++) { min[i] = FLT_MAX; max[i] = -FLT_MAX; } }
	float* getMin() { return min; }
	float* getMax() { return max; }
	void RemoveFish (int);
	void InsertFish(Fish&, int);
};
