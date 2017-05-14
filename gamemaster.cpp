#include <fstream> // std::ifstream
#include <vector> // std::vector
#include <cstdlib> // std::rand()

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
    in.close();
    return nums;
}

bool GameMaster::isCorrectF(int i, std::vector<unsigned short> &field, bool emptyIs) const {
    if (!emptyIs && field[i] == 0)
        return false;
    bool correct = true;
    int iVal = field[i];
    int row = i / 9; // Hányadik sorban van i.
    int col = i % 9; // Hányadik oslzopban van i.
    for (int j = 0; j < 9 && correct; j++) {
        if (row * 9 + j != i && field[row * 9 + j] == iVal) // Sorok ellenőrzése.
            correct = false;
        else if (j * 9 + col != i && field[j * 9 + col] == iVal) // Oszlopok ellenőrzése.
            correct = false;
    }
    // Az egyes háromszögek ellenőrzése:
    int triangleFirst = (row / 3) * 27 + (col / 3) * 3;
    for (int j = triangleFirst; j < triangleFirst + 21 && correct; j % 3 == 2 ? j += 7 : j += 1)
        if (j != i && field[j] == iVal)
            correct = false;
    return correct;
}

bool GameMaster::isFinishedF(std::vector<unsigned short> &field) const {
    bool finished = true;
    for (int i = 0; i < 81 && finished; i++)
        if (field[i] == 0 || !isCorrectF(i, field))
            finished = false;
    return finished;
}

void GameMaster::backtrackGenerate(std::vector<unsigned short> &field, std::vector<std::vector<bool>> &theseWere, unsigned short j) const {
    for (int i = j; i < 81; i++) {
        do {
            do {
                field[i] = rand() % 9 + 1;
                int hanyVolt = 0;
                for (int q = 0; q < 9; q++)
                    if (theseWere[i][q])
                        hanyVolt++;
                if (hanyVolt == 9) {
                    field[i] = 0;
                    for (int q = 0; q < 9; q++)
                        theseWere[i][q] = false;
                    backtrackGenerate(field, theseWere, i - 1);
                }
                if (isFinishedF(field))
                    return;
            } while (theseWere[i][field[i] - 1]);
            theseWere[i][field[i] - 1] = true;
        } while (!isCorrectF(i, field));
    }
}

void GameMaster::randomCells(std::vector<SudokuCell*> &cells, std::vector<unsigned short> &fields) const {
    std::vector<unsigned short> fields2(81, 0);
    std::vector<std::vector<bool>> theseWere(81, std::vector<bool>(9, false));
    // Töltsük fell random a táblát.
    backtrackGenerate(fields2, theseWere, 0);
    // Távolítsunk el elemeket, amíg egyértelmű a megoldás.
    std::vector<bool> thisWas(81, false);
    for (int i = 0; i < 50; i++) {
        unsigned short r;
        do {
            r = rand() % 81;
        } while (thisWas[r]);
        thisWas[r] = true;
        fields2[r] = 0;
    }
    fields = fields2;
    for (int i = 0; i < 81; i++)
        cells[i]->setCell(fields[i]);
}
