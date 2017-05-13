#include <string> // std::string
#include <algorithm> // std::max
#include <fstream> // std::ofstream

#include "graphics.hpp"
#include "sudokucell.hpp"

using namespace genv;

const unsigned short h = 1 + 5 + gout.cascent() + 5 + 1; // Keret: 2 x (1 px), térköz: 2 x (5 px), szám magasság.

// Keret: 2 x (1 px), térköz: 2 x (5 px) , szám hossz.
SudokuCell::SudokuCell(int x, int y, int num, int _min, int _max, bool changable) :
    NumSet(x, y, (1 + 7 + gout.twidth(int2str(9)) + 7 + 1), h, num, _min, _max), _changable(!changable), isFocused(false), isIncorrect(false) {}

void SudokuCell::draw() const {
    gout << move_to(_x, _y) << color(0, 0, 0) << box(_size_x, _size_y) // Keret megrajzolása
    << move_to(_x + 1, _y + 1) << color(isFocused ? 0 : 255, isFocused ? 0 : (isIncorrect ? 0 : 255), isFocused ? 255 : (isIncorrect ? 0 : 255)) << box(_size_x - 2, _size_y - 2) // Fókusz keret
    << move_to(_x + 2, _y + 2) << color(255, 255, 255) << box(_size_x - 4, _size_y - 4); // Belsõ fehérség
    if (num != 0)
        gout << move_to(_x + 8, _y + h - 7) << color((isIncorrect ? 255 : 0), 0, isIncorrect ? 0 : (_changable ? 255 : 0)) << text(int2str(num)); // Szám berajzolása
}


void SudokuCell::handle(event ev) {
    if (!_changable)
        return;
    isFocused = true;
    if (ev.type == ev_mouse && (ev.button == btn_wheeldown || ev.button == btn_wheelup)) {
        if (ev.button == btn_wheelup)
            num++;
        else
            num--;
    }
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

void SudokuCell::lost_focus(genv::event ev) {
    isFocused = false;
}

void SudokuCell::setCorrectness(bool isCorrect) {
    isIncorrect = !isCorrect;
}

unsigned short SudokuCell::sizeYSudokuCell() {
    return h;
}
unsigned short SudokuCell::sizeXSudokuCell() {
    return 1 + 7 + gout.twidth(Widget::int2str(9)) + 7 + 1;
}
