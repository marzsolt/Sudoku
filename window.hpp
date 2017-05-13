#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <vector> // std::vector

#include "graphics.hpp"
#include "widgets.hpp"

class Window {
protected:
    unsigned short _sizeX, _sizeY;
    std::vector<Widget *> w;
public:
    Window(unsigned short sizeX, unsigned short sizeY);
    virtual void eventLoop() = 0;
};

#endif // WINDOW_HPP_INCLUDED
