#include <fstream> // std::ofstream

#include "graphics.hpp"
#include "statictxt.hpp"

using namespace genv;

StaticTxt :: StaticTxt(int x, int y, int sx, int sy, std :: string s) : Widget(x, y, sx, sy), str(s) {}

void StaticTxt :: draw() const {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y); // törli a helyet a statikus textboxnak
    gout << move_to(_x + 2, _y + 2 + gout.cascent()) << color(0, 0, 0) << text(str);
}

void StaticTxt::dataToFile(std::ofstream &o) const {
    o << "\n\nStaticTxt object: x = " << _x << "\ny = " << _y << "\nsize in x = " << _size_x << "\nsize in y = " << _size_y
    << "\ntext = " << str;
}
