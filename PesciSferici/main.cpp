#include <FL/Fl.H>
#include <stdio.h>

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <deque>

#include "form.h"
#include "frame.h"
#include "School.h"
#include "Potential.h"
#include "define.h"
using namespace std;
//
extern Frame* scene;
void idle_cb(void*)
{
	scene->redraw();
	Fl::repeat_timeout(1/120, idle_cb);
}
// ********************************************************************************************************

int main(int argc, char** argv) {
	CreateMyWindow();
	Fl::add_timeout(1/120, idle_cb);
	Fl::add_idle(idle_cb, 0);
	return Fl::run();
}
