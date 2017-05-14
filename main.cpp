#include <vector> // std::vector
#include <sstream> // std::stringstream
#include <fstream> //std::ifstream
#include <cstdlib> //std::srand
#include <ctime> //std::time

#include "sudokucell.hpp" // SudokuCell
#include "statictxt.hpp" // StaticTxt

#include "game.hpp" // Game
#include "gamemaster.hpp" // GameMaster

using namespace genv;

const unsigned short XX = 240, YY = 300; // Ablak mérete.

std::string time2str(int time) {
    std::stringstream ss;
    ss << (time / 60 < 10 ? "0" : "") << time / 60 << ":" << (time % 60 < 10 ? "0" : "") << time % 60;
    std::string tmp;
    getline(ss, tmp);
    return tmp;
}

class Sudoku : public Game{
private:
    std::vector<SudokuCell*> cells = std::vector<SudokuCell*>(81);
    StaticTxt * t, * tHITxt, * congratStr, * newHI;
    bool _isDone;
    int tHI;
public:
    Sudoku(unsigned short sizeX, unsigned short sizeY, GameMaster gm) : Game(sizeX, sizeY, gm), _isDone(false) {
        t = new StaticTxt(10, 280, 230, gout.cascent(), time2str(_time));
        w.push_back(t);
        std::ifstream in ("hi.ppke");
        if (in.fail())
            tHI = 0;
        else
            in >> tHI;
        in.close();
        tHITxt = new StaticTxt(60, 280, 180, gout.cascent(), "Best: " + time2str(tHI));
        w.push_back(tHITxt);
        congratStr = new StaticTxt(10, 240, 230, 2 * (gout.cascent() + gout.cdescent()), "");
        w.push_back(congratStr);
        newHI = new StaticTxt(160, 280, 80, gout.cascent() + gout.cdescent(), "");
        w.push_back(newHI);
        newGame();
    }
    void gameLogic() {
        for (int i = 0; i < 81; i++)
            if (cells[i]->getNum() != 0)
                cells[i]->setCorrectness(_gm.isCorrect(i, cells));
        if ((_isDone = _gm.isFinished(cells))) {
            congratStr->setTxt("Congratulation, you did it!\nESC: exit, ENTER: new game.", 255);
            if (_time < tHI || tHI == 0) {
                newHI->setTxt("NEW BEST", 255);
                std::ofstream out ("hi.ppke");
                out << _time;
                out.close();
                tHI = _time;
                tHITxt->setTxt("Best: " + time2str(tHI));
            }
        }
        else {
            congratStr->setTxt("");
            newHI->setTxt("");
        }
    }
    void newGame() {
        _time = -1;
        if (w.size() >= 81)
            for (int i = 0; i < 81; i++)
                w.pop_back();
        for(int i = 0; i < 81; i++) {
            SudokuCell* tmp = new SudokuCell(10 + (i % 9) * (SudokuCell::sizeXSudokuCell() - 1)  + ((i % 9) / 3) * 6,
                                      10 + (i / 9) * (SudokuCell::sizeYSudokuCell() - 1) + ((i / 9) / 3) * 6, 0, 0, 9, 0);
            cells[i] = tmp;
            w.push_back(tmp);
        }
        _gm.randomCells(cells);
    }
    void printGameTime() {
        if (!_isDone) {
            _time++;
            t->setTxt(time2str(_time));
        }
        else {
            t->setTxt(time2str(_time), 255);
        }
    }
};

int main()
{
    srand(time(NULL));
    GameMaster GM;
    Sudoku *sudoku = new Sudoku(XX, YY, GM);
    sudoku->eventLoop();
    return 0;
}
