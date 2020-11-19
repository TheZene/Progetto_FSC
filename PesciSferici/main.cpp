#include <FL/Fl.H>
#include <stdio.h>

#include "form.h"
#include "frame.h"
#include "Pesce.h"
#include "Shoal.h"


using namespace std;
//
extern Frame* scene;
//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
	scene->redraw();
}
// ********************************************************************************************************
int main(int argc, char** argv) {
	CreateMyWindow();
	Fl::add_idle(idle_cb, 0);
	return Fl::run();
	/*vector<float> prova{ 5.0,2.0,3.0 };
	Pesce *p = new Pesce(prova, prova, prova);
	for (int i = 0; i < p->getAcc().size(); ++i) {
		printf("%f ", p->getAcc()[i]);
	}*/
	
}
