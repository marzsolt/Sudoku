#include <fstream> // std::ifstream
#include <vector> // std::vector

#include "gamemaster.hpp"
#include "sudokucell.hpp"

GameMaster::GameMaster() { }

std::vector<unsigned short> GameMaster::loadFieldsFromFile(std::string filename) {
    std::ifstream in (filename.c_str());
    if(in.fail())
        return std::vector<unsigned short>(81, 0);
    std::vector<unsigned short> nums(81);
    for(unsigned short i = 0; i < 81; i++)
        in >> nums[i];
    return nums;
}

bool GameMaster::isCorrect(int i, std::vector<SudokuCell*> cells) const {
    bool correct = true;
    int iVal = cells[i]->getNum();
    int row = i / 9; // Hányadik sorban van i.
    int col = i % 9; // Hányadik oslzopban van i.
    for (int j = 0; j < 9 && correct; j++) {
        if (row * 9 + j != i && cells[row * 9 + j]->getNum() == iVal) // Sorok ellenőrzése.
            correct = false;
        else if (j * 9 + col != i && cells[j * 9 + col]->getNum() == iVal) // Oszlopok ellenőrzése.
            correct = false;
    }
    // Az egyes háromszögek ellenőrzése:
    int triangleFirst = (row / 3) * 27 + (col / 3) * 3;
    for (int j = triangleFirst; j < triangleFirst + 21 && correct; j % 3 == 2 ? j += 7 : j += 1)
        if (j != i && cells[j]->getNum() == iVal)
            correct = false;
    return correct;
}
