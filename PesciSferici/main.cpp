#include <FL/Fl.H>
#include <stdio.h>

#include "form.h"
#include "frame.h"


using namespace std;
//
extern Frame* scene;
//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{	
	scene->redraw();
	Fl::repeat_timeout(1/120, idle_cb);
}
// ********************************************************************************************************
int main(int argc, char** argv) {
	CreateMyWindow();
	Fl::add_timeout(1/120, idle_cb);
	return Fl::run();
}
