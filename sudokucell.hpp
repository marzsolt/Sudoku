#ifndef SUDOKUCELL_HPP_INCLUDED
#define SUDOKUCELL_HPP_INCLUDED

#include "numset.hpp"

class SudokuCell : public NumSet{
private:
    bool isFocused;
public:
    SudokuCell(int x, int y, int num, int _min, int _max);
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual void lost_focus(genv::event ev);

    static unsigned short sizeXSudokuCell();
    static unsigned short sizeYSudokuCell();
};

#endif // SUDOKUCELL_HPP_INCLUDED
