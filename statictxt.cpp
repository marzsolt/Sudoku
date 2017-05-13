#include <fstream> // std::ofstream

#include "graphics.hpp"
#include "statictxt.hpp"

using namespace genv;

StaticTxt :: StaticTxt(int x, int y, int sx, int sy, std :: string s) : Widget(x, y, sx, sy), str(s), _r(0), _g(0), _b(0) {}
StaticTxt :: StaticTxt(int x, int y, int sx, int sy, std :: string s, unsigned char r, unsigned char g, unsigned char b) :
    Widget(x, y, sx, sy), str(s), _r(r), _g(g), _b(b) {}

void StaticTxt::draw() const {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y); // törli a helyet a statikus textboxnak
    gout << move_to(_x, _y + gout.cascent()) << color(_r, _g, _b) << text(str);
}

void StaticTxt::setTxt(std::string newTxt, unsigned char r, unsigned char g, unsigned char b) {
    str = newTxt;
    _r = r;
    _g = g;
    _b = b;
}
