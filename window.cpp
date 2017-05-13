#include "graphics.hpp"
#include "window.hpp"

using namespace genv;

Window::Window(unsigned short sizeX, unsigned short sizeY) : _sizeX(sizeX), _sizeY(sizeY) {};

void Window::eventLoop() {
    event ev;
    int focus = -1;
    while(gin >> ev && ev.keycode != key_escape) {
        /*if (ev.type == ev_key && ev.keycode == key_tab) { // Léptetés tabbal.
            if (focus != -1)
                widgets[focus]->lost_focus(ev);
            focus = (focus + 1) % widgets.size();
        }*/
        if (ev.type == ev_mouse && ev.button == btn_left) {
            for (size_t i = 0; i < w.size(); i++) {
                if (w[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    if(focus != -1)
                        w[focus]->lost_focus(ev);
                    focus = i;
                }
            }
        }
        if (focus != -1) {
            w[focus]->handle(ev);
        }
        for (Widget * v : w)
            v->draw();
        gout << refresh;
    }
}
