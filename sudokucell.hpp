#ifndef SUDOKUCELL_HPP_INCLUDED
#define SUDOKUCELL_HPP_INCLUDED

#include "numset.hpp"

class SudokuCell : public NumSet{
private:
    bool _changable, isFocused, isIncorrect;
public:
    SudokuCell();
    SudokuCell(int x, int y, int num, int _min, int _max, bool changable);
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual void lost_focus(genv::event ev);
    virtual void setCorrectness(bool isCorrect);

    //virtual void deleteContent();
    //virtual void getRandomValue();
    virtual void setCell(unsigned short newNum);

    static unsigned short sizeXSudokuCell();
    static unsigned short sizeYSudokuCell();
};

#endif // SUDOKUCELL_HPP_INCLUDED
