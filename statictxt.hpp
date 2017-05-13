#ifndef STATICTXT_H_INCLUDED
#define STATICTXT_H_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class StaticTxt : public Widget {
protected:
    std :: string str;
    unsigned char _r, _g, _b;
public:
    StaticTxt(int x, int y, int sx, int sy, std :: string s, unsigned char r, unsigned char g, unsigned char b);
    StaticTxt(int x, int y, int sx, int sy, std :: string s);
    virtual void draw() const;
    void setTxt(std::string newTxt, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
};

#endif // STATICTXT_H_INCLUDED
