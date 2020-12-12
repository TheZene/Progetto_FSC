#include "School.h"


extern float dist(float*, float*); //calcolo distanza tra due pesci
extern void setAccelerations(vector<School>& Oceano);



School::School(vector<Fish*> s) {
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
	phi = askPhi(totV);
	theta = askTheta(totV);
	for (i = 0; i < DIMARR; i++) {
		//dimensions[i] = max[i] - min[i];
		mid[i] = totP[i] / school.size();
	}
}

void draw_direction() {
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(10, 0, 0); glVertex3f(15, 0, 0);
	glVertex3f(13, 3, 0); glVertex3f(15, 0, 0);
	glVertex3f(13, -3, 0); glVertex3f(15, 0, 0);
	glEnd();
}

void School::DrawSchool()
{
	for (int i = 0; i < school.size(); i++)
	{
		school[i]->Nuota();
		glPushMatrix();
		glTranslated(school[i]->getPos()[0], school[i]->getPos()[1], school[i]->getPos()[2]);
		glCallList(SFERA);
		glPopMatrix();
		//qua calcolo la direzione del banco media (in teoria pesata perche' chi sta avanti comanda)
		computeAVGDir();
	}
	cout << "dist travld " << askModule(mid) << endl;
	glPushMatrix();
	glTranslatef(mid[0], mid[1], mid[2]);
	glCallList(CENTRO);
	glRotatef(phi * 180 / M_PI, 0, 0, 1);
	glRotatef(theta * 180 / M_PI, 1, 0, 0);
	draw_direction();
	glPopMatrix();
	glLoadIdentity();
	gluLookAt(mid[0], mid[1], mid[2]+150.0, mid[0], mid[1], mid[2], 0, 1, 0);
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




void Merge(vector<School> &Oceano)
{
	for (int a = 0; a < Oceano.size(); a++)
		for (int b = 0; b < Oceano[a].getSchool().size(); b++)
		{
			Fish* Fish = Oceano[a].getSchool()[b];
			for (int i = 0; i < Oceano.size(); i++)
				if(a!=i)
					for (int k = 0; k < Oceano[i].getSchool().size(); k++)
						if (dist(Fish->getPos(), Oceano[i].getSchool()[k]->getPos()) < MIN_DIST)
						{
							Oceano[a].Merge(Oceano[i]);
							Oceano.erase(Oceano.begin() + i);
						}
		}
}



void DrawOcean(vector<School>& Oceano)
{
	Merge(Oceano);
	setAccelerations(Oceano);
	for (int i = 0; i < Oceano.size(); i++)
		Oceano[i].DrawSchool();
}


void School::RemoveFish (int b)
{
	school.erase(school.begin() + b);
}

void School::InsertFish(Fish &fish, int b)
{
	school.insert(school.begin() + b, &fish);
}



