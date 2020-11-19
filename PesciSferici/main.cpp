#include <FL/Fl.H>
#include <stdio.h>

#include "form.h"
#include "frame.h"


using namespace std;
//
extern Frame* scene;
//--------------------------------------------------------------------------------------------
/*int camRotateUpX(int evt) {
	printf("hi");
	if (evt == FL_KEYDOWN) {
		printf("hi");
		if (Fl::event_key() == 'w') {
			glMatrixMode(GL_MODELVIEW);
			glRotatef(2, 1, 0, 0);
			return 1; // to indicate we used the key event
		}  // here you can test for other keys, as wanted
	}
	return 0;
}*/

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{	
	scene->redraw();
	Fl::repeat_timeout(1/120, idle_cb);
}
// ********************************************************************************************************
int main(int argc, char** argv) {
	CreateMyWindow();
	//Fl::add_handler(camRotateUpX);
	Fl::add_timeout(1/120, idle_cb);
	return Fl::run();
	/*vector<float> prova{ 5.0,2.0,3.0 };
	Pesce *p = new Pesce(prova, prova, prova);
	for (int i = 0; i < p->getAcc().size(); ++i) {
		printf("%f ", p->getAcc()[i]);
	}*/
	
}
