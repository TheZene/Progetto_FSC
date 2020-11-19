#pragma once
#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <stdlib.h>
#include "Pesce.h"

//#define L 5
//#define SFERETTA 7

/*Class: Shoal
* Description: classe che descrive un banco di pesci
* 
* Attributes:
*	shoal: vector di classe pesce
*	dir: array delle direzioni verso le quali si può muovere il banco
*Methods: 
*	i primi tre sono costruttori, il primo vuoto per dovere, il secondo passando solo un pesce, il terzo passando un vector di pesci
*	setDir: setter per l'array di direzioni
*	addPesce: aggiunge un pesce al vector
*	getShoal: restituisce il vector contenente tutti i pesci del banco
*	computeAVGDir: calcola la direzione "media" del banco dei pesci (per ora coordinate cartesiane)
*/
class Shoal {
private:
	vector<Pesce*> shoal; 
	float dir[3]; 
	//float dimensions[3]; //dimensioni del banco (lunghezza, larghezza, altezza, modellato come un cilindro
	//float centro; //fulcro attorno al quale i pesci si stringono in presenza di un predatore
public:
	Shoal() { dir[0] = 0.0; dir[1] = 0.0; }
	Shoal(Pesce* p) { dir[0] = 0.0; dir[1] = 0.0; shoal.push_back(p); }
	Shoal(vector<Pesce*> s);
	void setDir(float* arr);
	void addPesce(Pesce* p) { shoal.push_back(p); }
	vector<Pesce*> getShoal() { return shoal; }
	void computeAVGDir();

};