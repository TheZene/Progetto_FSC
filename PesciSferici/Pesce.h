#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <stdlib.h>
#pragma once
//#define L 5
//#define SFERETTA 7

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
	float pos[3];
	float vel[3];
	float acc[3];
public:
	Pesce() {}
	Pesce(vector<float> p, vector<float> v, vector<float> a);
	void setPos(vector<float> p);
	void setVel(vector<float> v);
	void setAcc(vector<float> a);
	float* getPos() { return pos; }
	float* getVel() { return vel; }
	float* getAcc() { return acc; }
	void Nuota();
};
