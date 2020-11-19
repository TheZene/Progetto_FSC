#pragma once
#ifdef PIGRECO

#else
#define PIGRECO 3.141592f

#endif


#ifdef POTENZIALI

#else
#include <math.h>
#include <iostream>
#include "Pesce.h"
#include "Shoal.h"
#define LUNGHEZZA_PESCE 2



float dist(float*, float*); //calcolo distanza tra due pesci
float modul3(float*); //modulo 3 d
float* FindDir(float*); //trova angoli delle coordinate sferiche

//==========================================
//Forze e potenziali con posizioni
//==========================================

float RepulsiveForceFishX(float*, float*); //Forze repulsive, scalari, primo argomento posizione del pesce che genera, secondo del pesce che subisce
float RepulsiveForceFishY(float*, float*);
float RepulsiveForceFishZ(float*, float*);

float* RepulsiveForcesFish(float*, float*); // Forze repulsive, vettoriali, primo argomento pos pesce che genera, secondo del pesce che la subisce

float RepulsivePotenzialFish(float*, float*); //potenziale da cui si ricavano le forze, probabilmente inutile


float AttractiveForceSchoolX(float*, float*, float*, float); //Forze del potenziale attrattivo, primo argomento posizione del banco, secondo vel banco
float AttractiveForceSchoolY(float*, float*, float*, float); //terzo pos pesce che subisce, quarto dimensioni medie del banco
float AttractiveForceSchoolZ(float*, float*, float*, float);//#### DA TESTARE ####

float* AttractiveForcesSchool(float*, float*, float*, float); //Forze del potenziale del banco attrattive, vettoriali, prima banco poi pesce

float AttractivePotenzialSchool(float*, float*, float);//potenziale attrattivo per interazioni banco-pesce


//==========================================
//Forze e potenziali con pesci (overload di pesci vari)
//==========================================

float RepulsiveForceFishX(Pesce, Pesce);  //idee per fare degli overload con pesce invece di posizioni? potrebbe essere comodo
//float RepulsiveForceFishX(Pesce *, Pesce *); 
float RepulsiveForceFishY(Pesce, Pesce); 
//float RepulsiveForceFishY(Pesce*, Pesce*);
float RepulsiveForceFishZ(Pesce, Pesce);
//float RepulsiveForceFishZ(Pesce*, Pesce*);

float* RepulsiveForcesFish(Pesce, Pesce);
//float* RepulsiveForcesFish(Pesce*, Pesce*);

float RepulsivePotenzialFish(Pesce, Pesce); 
//float RepulsivePotenzialFish(Pesce*, Pesce*); 


float AttractiveForceSchoolX(Shoal, Pesce);  //da finire di overloaddare
//float AttractiveForceSchoolY(float*, float*); 
//float AttractiveForceSchoolZ(float*, float*);

//float* AttractiveForcesSchool(float*, float*); 

//float AttractivePotenzialSchool(float*, float*);



#define POTENZIALI 
#endif
