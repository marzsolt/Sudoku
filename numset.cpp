#include <string> // std::string
#include <algorithm> // std::max
#include <fstream> // std::ofstream

#include "graphics.hpp"
#include "numset.hpp"

using namespace genv;

const unsigned short h = 1 + 5 + gout.cascent() + 5 + 1; // Keret: 2 x (1 px), térköz: 2 x (5 px), szám magasság.

// Keret: 2 x (1 px), térköz: 2 x (5 px) , szám hossz.
NumSet::NumSet() {}

NumSet::NumSet(int x, int y, int _min, int _max) :
    Widget(x, y, (1 + 5 + gout.twidth(int2str(pow(10, szjsz(std::max(abs(_max), abs(_min)) + 1)) - 1)) + 5 + 1), h), num(_min), m(_min), M(_max) {}

NumSet::NumSet(int x, int y, int sx, int sy, int _num, int _min, int _max) :
    Widget(x, y, sx, sy), num(_num), m(_min), M(_max) {}

void NumSet::draw() const {
    gout << move_to(_x, _y) << color(0, 0, 0) << box(_size_x, _size_y) // Keret megrajzolása
    << move_to(_x + 1, _y + 1) << color(255, 255, 255) << box(_size_x - 2, _size_y - 2) // Belsõ fehérség
    << move_to(_x + 6, _y + h - 7) << color(0, 0, 0) << text(int2str(num)) // Szám berajzolása
    << stamp(gombokCv(), _x + _size_x - 1, _y); // Gombok berakása
}

bool NumSet::is_selected(int mouse_x, int mouse_y) const {
    return mouse_x > _x && mouse_x < _x + _size_x + h / 2 && mouse_y > _y && mouse_y < _y + _size_y;
}

short NumSet::is_selected_bt(int mouse_x, int mouse_y) const {
    if (mouse_x > _x + _size_x && mouse_x < _x + _size_x + h / 2) {
        if (mouse_y > _y && mouse_y < _y + h / 2)
            return 1;
        else if (mouse_y > _y + h / 2 && mouse_y < _y + _size_y)
            return -1;
    }
    return 0;
}

void NumSet::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left)
        num += is_selected_bt(ev.pos_x, ev.pos_y);
    else if (ev.type == ev_key) {
        if (ev.keycode == key_up || ev.keycode == key_pgup)
            num += ev.keycode == key_up ? 1 : 10;
        else if (ev.keycode == key_down || ev.keycode == key_pgdn)
            num -= ev.keycode == key_down ? 1 : 10;
    }
    if (num < m)
        num = m;
    else if (num > M)
        num = M;
}

canvas &NumSet::gombokCv() {
    static canvas G(h / 2, h);
    G << move_to(0, 0) << color(0, 0, 0) << box(h / 2, h) // Gombok keret(ek)
    << move_to(1, 1) << color(255, 255, 255) << box(h / 2 - 2, h / 2 - 1) // Felfele gomb háttér
    << move_to(1, h / 2 + 1) << color(255, 255, 255) << box(h / 2 - 2, h / 2 - 1) // Lefele gomb háttér
    << move_to(h / 6, h / 3) << color(0, 0, 0) << line_to(h / 4, h / 6) << line_to(h / 3, h / 3) // Felfele gomb jel
    << move_to(h / 6, h / 6 + h / 2) << line_to(h / 4, h / 3 + h / 2) << line_to(h / 3, h / 6 + h / 2); // Lefele gomb jel
    return G;
}

int NumSet::getNum() const {
    return num;
}
