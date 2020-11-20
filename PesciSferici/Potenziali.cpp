#include "Potenziali.h"
#include <iostream>
#include <math.h>
using namespace std;



//##########################
//Funzioni e attributi generali



float asimettry = 0.2f; //fattore di asimettria banco


float dist(float * pos1, float * pos2) //calcolo della distanza tra due punti FUNZIONA 
{
	float a=0;
	for (int i = 0; i < 3; i++)
		a += ((pos1[i] - pos2[i]) * (pos1[i] - pos2[i]));
	a = sqrtf(a);
	return a;
}

float modul3(float* Anyvect)//calcola il modulo
{
	float a = 0;
	for (int i = 0; i < 3; i++)
		a += (Anyvect[i] * Anyvect[i]);
	a = sqrtf(a);
	return a;
}

float* FindDir(float* Anyvect) // trova theta, phi per le coordinate sferiche, il primo risultato � l'angolo sul piano, il secondo � l'angolo con le zeta
{								//se siamo in 0,0,0 da {0,0}
	float a = modul3(Anyvect);
	float Directions[2]{ 0,0 };
	if (a > -0.00001f && a < 0.00001f)
		return Directions;
	if (Anyvect[0] >= -0.00001f && Anyvect[1] <= 0.00001f)
	{
		if (Anyvect[1] > 0)
			Directions[0] = PIGRECO / 2.f;
		if (Anyvect[0] <= 0)
			Directions[0] = 3.f * PIGRECO / 2.f;
	}
	if (Anyvect[0] > 0.00001f)
	{
		if (Anyvect[1] >= 0)
			Directions[0] = atanf(Anyvect[1] / Anyvect[0]);
		if (Anyvect[1] < 0)
			Directions[0] = (atanf(Anyvect[1] / Anyvect[0]) + 2 * PIGRECO);
	}
	if (Anyvect[0] < -0.00001f)
	{
		if (Anyvect[1] >= 0)
			Directions[0] = (atanf(Anyvect[1] / Anyvect[0]) + 2 * PIGRECO);
		if (Anyvect[1] < 0)
			Directions[0] = (atanf(Anyvect[1] / Anyvect[0]) + PIGRECO);
	}
	Directions[1] = acosf(Anyvect[2] / a);
	return Directions;
}

float ProdottoScalare3(float* AnyVet1, float* AnyVet2)
{
	float a = 0;
	for (int i = 0; i < 3; i++)
		a += (AnyVet1[i] * AnyVet2[i]);
	return a;
}



//##########################################
//Interazione repulsiva pesce-pesce

float RepulsiveForceFishX(float* PosFish1, float* PosFish2)  //pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	return ((12.f) * (PosFish2[0] - PosFish1[0])) / (r * (pow(r - LUNGHEZZA_PESCE / 2.f + 0.5f, 13)));
}



float RepulsiveForceFishY(float* PosFish1, float* PosFish2) //pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	return ((12.f) * (PosFish2[1] - PosFish1[1])) / (r * (pow(r - LUNGHEZZA_PESCE / 2.f + 0.5f, 13)));
}


float RepulsiveForceFishZ(float* PosFish1, float* PosFish2) //pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	return ((12.f) * (PosFish2[2] - PosFish1[2])) / (r * (pow(r - LUNGHEZZA_PESCE / 2.f + 0.5f, 13)));
}


float * RepulsiveForcesFish(float* PosFish1, float * PosFish2) //calcolo delle forze repulsive generate da un pesce FUNZIONA
																//pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	float Forze[3];
	for (int i = 0; i < 3; i++)
		Forze[i] = ((12.f) * (PosFish2[i] - PosFish1[i])) / (r * (pow(r - LUNGHEZZA_PESCE / 2.f + 0.5f, 13)));
	return Forze;

}

float RepulsivePotenzialFish(float* PosFish1, float* PosFish2) //potenziale, primo pesce crea il potenziale, il secondo lo subisce
{
	float r = dist(PosFish1, PosFish2);
	return 1.f / (pow(r - LUNGHEZZA_PESCE / 2.f + 0.5f, 12)); 
}


//####################################
//Interazioni Attrattive Banco-pesce

//si potrebbero fare due funzioni per trovare forza parallela e perp e delle funzioni per proiettare sugli assi

float AttractiveForceSchoolX(float* PosSchool,float * VelSchool, float* PosFish, float RSchool) //Forza scalare potenziale di banco, guarda il .h
{
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	return (1 - asimettry) * 2 * VelSchool[0] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV) 
			+ 2 * (PosSchool[0] - PosFish[0]) / (RSchool * RSchool);
}

float AttractiveForceSchoolY(float* PosSchool, float* VelSchool, float* PosFish, float RSchool)
{
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	return (1 - asimettry) * 2 * VelSchool[1] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV)
		+ 2 * (PosSchool[1] - PosFish[1]) / (RSchool * RSchool);
}
float AttractiveForceSchoolZ(float* PosSchool, float* VelSchool, float* PosFish, float RSchool)
{
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	return (1 - asimettry) * 2 * VelSchool[2] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV)
		+ 2 * (PosSchool[2] - PosFish[2]) / (RSchool * RSchool);
}

float* AttractiveForcesSchool(float* PosSchool, float* VelSchool, float* PosFish, float RSchool) //Forza vettoriale per il potenziale di banco
{
	float Forzexyz[3];
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	for (int i = 0; i < 3; i++)
		Forzexyz[i] = (1 - asimettry) * 2 * VelSchool[i] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV)
					+ 2 * (PosSchool[i] - PosFish[i]) / (RSchool * RSchool);
	return Forzexyz;
}

float AttractivePotenzialSchool(float* PosSchool, float* VelSchool, float* PosFish, float RSchool) //da finire
{
	return 0;
}



//##############################
//Interazioni pesce-buca

float AttractiveForceHoleX(float* PosFish, float* PosHole) //interazione scalare pesce buca, primo argomento posizione pesce, secondo posizione buco
{
	float r = dist(PosFish, PosHole);
	return expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[0] - PosHole[0]) / (DIM_BUCA * DIM_BUCA));
}

float AttractiveForceHoleY(float* PosFish, float* PosHole)
{
	float r = dist(PosFish, PosHole);
	return expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[1] - PosHole[1]) / (DIM_BUCA * DIM_BUCA));
}

float AttractiveForceHoleZ(float* PosFish, float* PosHole)
{
	float r = dist(PosFish, PosHole);
	return expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[2] - PosHole[2]) / (DIM_BUCA * DIM_BUCA));
}

float* AttractiveForcesHole(float* PosFish, float* PosHole) //interazione vettoriale pesce buca, primo argomento pos pesce, secondo pos buca
{
	float r = dist(PosFish, PosHole);
	float Forzexyz[3];
	for (int i = 0; i < 3; i++)
		Forzexyz[i] = expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[i] - PosHole[i]) / (DIM_BUCA * DIM_BUCA));

	return Forzexyz;
}


//##########################
//Forze repulsive per pesci (overload)

float RepulsiveForceFishX(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForceFishX(PesceGen.getPos(), PesceSub.getPos());
}

float RepulsiveForceFishY(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForceFishY(PesceGen.getPos(), PesceSub.getPos());
}

float RepulsiveForceFishZ(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForceFishZ(PesceGen.getPos(), PesceSub.getPos());
}



float* RepulsiveForcesFish(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForcesFish(PesceGen.getPos(), PesceSub.getPos());
}


float RepulsivePotentialFish(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	       
	return RepulsivePotenzialFish(PesceGen.getPos(), PesceSub.getPos());
}


//##########################
//Forze Attrative per pesci-Banco (overload), da rifare se si introducono attributi nuovi del banco

float AttractiveForceSchoolX(School Banco, Pesce Fish) //calcola la media della posizone dei pesci del banco(centro) e la velocità media poi fa il conto delle dimensioni massime del banco
{
	float AvgPosSchool[3]{ 0,0,0 }, AvgVelSchool[3]{ 0,0,0 }, r{ 0 }, maxR[]{ 0,0,0 };
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			AvgPosSchool[i] += Banco.getSchool()[k]->getPos()[i];
			AvgVelSchool[i] += Banco.getSchool()[k]->getVel()[i];
		}
		AvgPosSchool[i] = AvgPosSchool[i] / float(Banco.getSchool().size());
		AvgVelSchool[i] = AvgVelSchool[i] / float(Banco.getSchool().size());
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			maxR[i] = maxR[i] > abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]) ? 
					  maxR[i] : abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]);
		}
		r = maxR[i] > r ? maxR[i] : r;
	}

	return AttractiveForceSchoolX(AvgPosSchool, AvgVelSchool, Fish.getPos(),r);
}

float AttractiveForceSchoolY(School Banco, Pesce Fish) //calcola la media della posizone dei pesci del banco(centro) e la velocità media poi fa il conto delle dimensioni massime del banco
{
	float AvgPosSchool[3]{ 0,0,0 }, AvgVelSchool[3]{ 0,0,0 }, r{ 0 }, maxR[]{ 0,0,0 };
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			AvgPosSchool[i] += Banco.getSchool()[k]->getPos()[i];
			AvgVelSchool[i] += Banco.getSchool()[k]->getVel()[i];
		}
		AvgPosSchool[i] = AvgPosSchool[i] / float(Banco.getSchool().size());
		AvgVelSchool[i] = AvgVelSchool[i] / float(Banco.getSchool().size());
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			maxR[i] = maxR[i] > abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]) ?
				maxR[i] : abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]);
		}
		r = maxR[i] > r ? maxR[i] : r;
	}

	return AttractiveForceSchoolY(AvgPosSchool, AvgVelSchool, Fish.getPos(), r);
}

float AttractiveForceSchoolZ(School Banco, Pesce Fish) //calcola la media della posizone dei pesci del banco(centro) e la velocità media poi fa il conto delle dimensioni massime del banco
{
	float AvgPosSchool[3]{ 0,0,0 }, AvgVelSchool[3]{ 0,0,0 }, r{ 0 }, maxR[]{ 0,0,0 };
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			AvgPosSchool[i] += Banco.getSchool()[k]->getPos()[i];
			AvgVelSchool[i] += Banco.getSchool()[k]->getVel()[i];
		}
		AvgPosSchool[i] = AvgPosSchool[i] / float(Banco.getSchool().size());
		AvgVelSchool[i] = AvgVelSchool[i] / float(Banco.getSchool().size());
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			maxR[i] = maxR[i] > abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]) ?
				maxR[i] : abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]);
		}
		r = maxR[i] > r ? maxR[i] : r;
	}

	return AttractiveForceSchoolZ(AvgPosSchool, AvgVelSchool, Fish.getPos(), r);
}


float* AttractiveForcesSchool(School Banco, Pesce Fish) //calcola la media della posizone dei pesci del banco(centro) e la velocità media poi fa il conto delle dimensioni massime del banco
{
	float AvgPosSchool[3]{ 0,0,0 }, AvgVelSchool[3]{ 0,0,0 }, r{ 0 }, maxR[]{ 0,0,0 };
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			AvgPosSchool[i] += Banco.getSchool()[k]->getPos()[i];
			AvgVelSchool[i] += Banco.getSchool()[k]->getVel()[i];
		}
		AvgPosSchool[i] = AvgPosSchool[i] / float(Banco.getSchool().size());
		AvgVelSchool[i] = AvgVelSchool[i] / float(Banco.getSchool().size());
		for (int k = 0; k < Banco.getSchool().size(); k++)
		{
			maxR[i] = maxR[i] > abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]) ?
				maxR[i] : abs(Banco.getSchool()[k]->getPos()[i] - AvgPosSchool[i]);
		}
		r = maxR[i] > r ? maxR[i] : r;
	}

	return AttractiveForcesSchool(AvgPosSchool, AvgVelSchool, Fish.getPos(), r);
}

//##########################
//Forze Attrative per pesci-buca (overload pesce-buca)



//###########################
//Forze tra pesci complete (pesuedo overload)

//float AllForceFishX(Pesce FishGen, Pesce FishSub)  //il primo pesce è quello che subisce tutte le forze, il secondo è quello che le genera idea di base, da aggiustare
//{
//	float temporaneo = RepulsiveForceFishX(FishGen, FishSub);
//	for (int i = 0; i < 8; i++)
//		temporaneo += AttractiveForceHoleX(FishSub, FishGen.PosBuca(i));
//	return temporaneo;
//}

float AllForceFishY(Pesce FishGen, Pesce FishSub)  
{
	return 0;
}

float AllForceFishZ(Pesce FishGen, Pesce FishSub)  
{
	return 0;
}

float* AllForcesFish(Pesce FishGen, Pesce FishSub)
{
	
}
