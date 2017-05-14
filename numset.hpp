#ifndef NUMSET_HPP_INCLUDED
#define NUMSET_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class NumSet : public Widget {
protected:
    int num, m, M;
public:
    NumSet();
    NumSet(int x, int y, int _min, int _max);
    NumSet(int x, int y, int sx, int sy, int num, int _min, int _max);
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual bool is_selected(int mouse_x, int mouse_y) const;
    virtual short is_selected_bt(int mouse_x, int mouse_y) const;
    virtual int getNum() const;

    static genv::canvas &gombokCv();
};

#endif // NUMSET_HPP_INCLUDED
