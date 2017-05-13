#ifndef GAMEMASTER_HPP_INCLUDED
#define GAMEMASTER_HPP_INCLUDED

#include <vector> // std::vector

#include "sudokucell.hpp"

class GameMaster{
public:
    GameMaster();
    std::vector<unsigned short>loadFieldsFromFile(std::string filename);
    bool isCorrect(int i, std::vector<SudokuCell*> &cells) const;
    bool isFinished(std::vector<SudokuCell*> &cells) const;
    void transformSudoku(std::vector<SudokuCell*> &cells, int type) const;
};

#endif // GAMEMASTER_HPP_INCLUDED
