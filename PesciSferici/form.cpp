#include "form.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Multiline_Output.H>

#include "Frame.h"

void exit_callback(Fl_Widget*);
void ruotaX_callback(Fl_Widget*);
void ruotaY_callback(Fl_Widget*);
void ruotaZ_callback(Fl_Widget*);
void zoom_callback(Fl_Widget*);

Fl_Window* form;
Frame* scene;
void CreateMyWindow(void) {
    int w_est, h_est;

    w_est = 23 + SCREEN_W + 23;   h_est = 23 + SCREEN_H + 23;

    form = new Fl_Window(w_est, h_est, "FSC Esempio_1");
    scene = new Frame(23, 23, SCREEN_W, SCREEN_H, 0);
    form->end();
    form->show();
    scene->show();
 }
//-------------------------------------------------------------------------------------------------


