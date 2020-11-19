#define _USE_MATH_DEFINES
#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

#pragma once
//#define L 5
//#define SFERETTA 7
#define DIMARR 3

using namespace std;

/*Class: Pesce, descrive un pesce
*
* Attributes: 
*	pos: vector delle posizioni, potrebbe essere array
*	vel: vector delle velocità, potrebbe essere array
*	acc: vector delle accelerazioni, potrebbe essere array
* TODO: aggiungere i buchi in cui possono buttarsi gli altri pesci
* Methods:
*	Pesce costruttore vuoto
*	Pesce(vector, vector, vector) costruttore che inizializza le velocità, posizione e accelerazione del pesce
*	setters and getters
*	Nuota: metodo che calcola lo spostamento del pesce
*/
class Pesce {
private:
	float pos[DIMARR];
	float vel[DIMARR];
	float acc[DIMARR];
	float theta;
public:
	Pesce();
	Pesce(float* p, float* v, float* a);
	void setPos(float* p);
	void setVel(float* v);
	void setAcc(float* a);
	void setTheta(float t);
	float* getPos() { return pos; }
	float* getVel() { return vel; }
	float* getAcc() { return acc; }
	float getTheta() { return theta; }
	void Nuota();
	float computeTheta();
};
