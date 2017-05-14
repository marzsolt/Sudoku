#include <sstream> // std::stringstream

#include "graphics.hpp"
#include "widgets.hpp"

using namespace genv;

Widget::Widget() {}

Widget::Widget(int x, int y, int sx, int sy) : _x(x), _y(y), _size_x(sx), _size_y(sy) {}

bool Widget::is_selected(int mouse_x, int mouse_y) const {
    return mouse_x > _x && mouse_x < _x + _size_x && mouse_y > _y && mouse_y < _y + _size_y;
}

void Widget::handle(event ev) {}

void Widget::lost_focus(event ev) {}

std::string Widget::int2str(int num) {
    std::stringstream ss;
    ss << num;
    std::string s;
    ss >> s;
    return s;
}

int Widget::szjsz(int num) {
    int n = 0;
    while (num != 0) {
        num /= 10;
        n++;
    }
    return n;
}

int Widget::leghszov(std::vector<std::string> str) {
    int M = 0;
    for(std::string s : str)
        if (M < gout.twidth(s))
            M = gout.twidth(s);
    return M;
}



