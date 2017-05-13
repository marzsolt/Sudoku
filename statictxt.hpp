#ifndef STATICTXT_H_INCLUDED
#define STATICTXT_H_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class StaticTxt : public Widget {
protected:
    std :: string str;
public:
    StaticTxt(int x, int y, int sx, int sy, std :: string s);
    virtual void draw() const;

    void dataToFile(std::ofstream &o) const;
};

#endif // STATICTXT_H_INCLUDED
