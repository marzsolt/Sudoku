#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include <vector>

#include "graphics.hpp"

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
public:
    Widget(int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y) const;
    virtual void draw() const = 0;
    virtual void handle(genv::event ev);
    virtual void lost_focus(genv::event ev);

    static std::string int2str(int num);
    static int szjsz(int num);
    static int leghszov(std::vector<std::string> str);
};

#endif // WIDGETS_HPP_INCLUDED
