#include <fstream> // std::ifstream
#include <vector> // std::vector
#include <cstdlib> // std::rand()

#include <iostream>

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

bool GameMaster::isCorrect(int i, std::vector<SudokuCell*> &cells) const {
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

bool GameMaster::isFinished(std::vector<SudokuCell*> &cells) const {
    bool finished = true;
    for (int i = 0; i < 81 && finished; i++)
        if (cells[i]->getNum() == 0 || !isCorrect(i, cells))
            finished = false;
    return finished;
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

void GameMaster::backtrackIfAmbiguous(std::vector<unsigned short> fieldE, std::vector<unsigned short> field,
                                       int &numSol, std::vector<unsigned short> &iModifable, int iThis) const {
    /*for(int q = 0; q < 81; q++)
        std::cout << field[q] << ' ';
    std::cout << std::endl;*/
    for (int i = j; i < iModifable.size(); i++) {


    }

    std::cout << iThis << ' ' << numSol << std::endl;
    if (iThis < 0 || iThis >= iModifable.size() || numSol > 1)
        return;
    while (!isCorrectF(iModifable[iThis], field, false)){
        field[iModifable[iThis]]++;
        if (field[iModifable[iThis]] > 9)
            break;
        //std::cout << field[iModifable[iThis]] << std::endl;
    }
    if (field[iModifable[iThis]] > 9) {
        field[iModifable[iThis]] = 0;
        backtrackIfAmbiguous(fieldE, fieldE, numSol, iModifable, iThis - 1);
    }
    else if (isFinishedF(field)) {
        numSol++;
        field[iModifable[iThis]] = 0;
        backtrackIfAmbiguous(fieldE, fieldE, numSol, iModifable, iThis - 1);
    }
    backtrackIfAmbiguous(fieldE, fieldE, numSol, iModifable, iThis + 1);
}

void GameMaster::randomCells(std::vector<SudokuCell*> &cells) const {
    std::vector<unsigned short> field(81, 0);
    std::vector<std::vector<bool>> theseWere(81, std::vector<bool>(9, false));
    // Töltsük fell random a táblát.
    backtrackGenerate(field, theseWere, 0);
    // Távolítsunk el elemeket, amíg egyértelmű a megoldás.
    std::vector<unsigned short> iDel, valDel;
    std::vector<bool> thisWas(81, false);
    int numSol = 0;
    while (numSol < 2) {
        numSol = 0;
        unsigned short r;
        do {
            r = rand() % 81;
        } while (thisWas[r]);
        thisWas[r] = true;
        iDel.push_back(r);
        valDel.push_back(field[r]);
        field[r] = 0;
        backtrackIfAmbiguous(field, field, numSol, iDel, 0);
        //std::cout<<numSol<<std::endl;
    }
    // Az utolsó - amivel elveszett az egyértelműség - tegyük vissza, többi visszanulláz.
    //field[iDel[iDel.size() - 1]] = field[valDel[valDel.size() - 1]];
    /*iDel.pop_back();
    valDel.pop_back();
    for (unsigned short i : iDel)
        field[i] = 0;*/
    for (int i = 0; i < 81; i++)
        cells[i]->setCell(field[i]);
}

/*void GameMaster::transformSudoku(std::vector<SudokuCell*> &cells, int type) const {
    // Ötlet forrás: http://dryicons.com/blog/2009/08/14/a-simple-algorithm-for-generating-sudoku-puzzles/
    SudokuCell * tmp = new SudokuCell;
    switch (type) {
        case 0:
            for (int i = 0; i < 81; i++)
            if (i % 9 < 4) {
                tmp->makeItB(cells[i]);
                cells[i]->makeItB(cells[((i / 9) * 9 + 8) - (i - (i / 9) * 9)]);
                cells[((i / 9) * 9 + 8) - (i - (i / 9) * 9)]->makeItB(tmp);
            }
            break;
        case 1:
            for (int i = 0; i < 81; i++)
            if (i / 9 + i % 9 < 8) {
                tmp->makeItB(cells[i]);
                cells[i]->makeItB(cells[(8 - i % 9) * 9 + 8 - i / 9]);
                cells[(8 - i % 9) * 9 + 8 - i / 9]->makeItB(tmp);
            }
            break;
        case 2:
            for (int i = 0; i < 81; i++)
            if (i / 9 > i % 9) {
                tmp->makeItB(cells[i]);
                cells[i]->makeItB(cells[i / 9 + (i % 9) * 9]);
                cells[i / 9 + (i % 9) * 9]->makeItB(tmp);
            }
            break;
        case 3:
            for (int i = 0; i < 81; i++)
            if (i / 9 < 4) {
                tmp->makeItB(cells[i]);
                cells[i]->makeItB(cells[i % 9 + (8 - i / 9) * 9]);
                cells[i % 9 + (8 - i / 9) * 9]->makeItB(tmp);
            }
    }
    delete tmp;
}*/
