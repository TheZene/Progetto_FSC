#include "School.h"


extern float dist(float*, float*); //calcolo distanza tra due pesci
extern void SetAccelerazioni(vector<School>& Oceano);



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



void School::DrawSchool()
{
	for (int i = 0; i < school.size(); i++)
	{
		school[i]->Nuota();
		glPushMatrix();
		glTranslated(school[i]->getPos()[0], school[i]->getPos()[1], school[i]->getPos()[2]);
		glCallList(SFERA);
		glPopMatrix();
	}
}







void School::Merge(School S)
{
	for (int i = 0; i < S.getSchool().size(); i++)
		school.push_back(S.getSchool()[i]);
}

vector<School> School::split()
{
	vector<School> Singoletti;
	for (int j = 0; j < school.size(); j++)
		Singoletti.push_back(School(school[j]));
	return Singoletti;
}




void Merge(vector<School>& Oceano)
{
	//splitting da perfezionare! (non essenziale)

	/*vector<School> split;
	for (int t=0; t<Oceano.size(); t++)
		if(Oceano[t].getSchool().size()>1)
		{
			//splitto il banco in tanti banchi singoletti e li aggiungo a Oceano
			split = Oceano[t].split();
			for (int o = 0; 0 < split.size(); o++)
				Oceano.push_back(split[0]);
			//elimino il banco
			Oceano.erase(Oceano.begin() + t);
		}*/

	for (int a = 0; a < Oceano.size(); a++)
		for (int b = 0; b < Oceano[a].getSchool().size(); b++)
		{
			Pesce* Fish = Oceano[a].getSchool()[b];
			for (int i = 0; i < Oceano.size(); i++)
				if (a != i)
					for (int k = 0; k < Oceano[i].getSchool().size(); k++)
						if (dist(Fish->getPos(), Oceano[i].getSchool()[k]->getPos()) < MinDist)
						{
							Oceano[a].Merge(Oceano[i]);
							Oceano.erase(Oceano.begin() + i);
						}
		}
}



void DrawOcean(vector<School>& Oceano)
{
	Merge(Oceano);
	SetAccelerazioni(Oceano);
	for (int i = 0; i < Oceano.size(); i++)
		Oceano[i].DrawSchool();
}







