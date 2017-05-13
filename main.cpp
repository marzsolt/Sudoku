#include <vector> // std::vector
#include <sstream> // std::stringstream
#include <fstream> //std::ifstream

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
    std::vector<SudokuCell*> cells;
    StaticTxt * t, * tHITxt, * congratStr, * newHI;
    bool _isDone;
    int tHI;
public:
    Sudoku(unsigned short sizeX, unsigned short sizeY, GameMaster gm, std::string filename) : Game(sizeX, sizeY, gm), _isDone(false) {
        std::vector<unsigned short> nums = gm.loadFieldsFromFile(filename);
        for(int i = 0; i < 81; i++) {
            SudokuCell* tmp = new SudokuCell(10 + (i % 9) * (SudokuCell::sizeXSudokuCell() - 1)  + ((i % 9) / 3) * 6,
                                      10 + (i / 9) * (SudokuCell::sizeYSudokuCell() - 1) + ((i / 9) / 3) * 6, nums[i], 0, 9, nums[i]);
            cells.push_back(tmp);
            w.push_back(tmp);
        }
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
    }
    void gameLogic() {
        for (int i = 0; i < 81; i++)
            if (cells[i]->getNum() != 0)
                cells[i]->setCorrectness(_gm.isCorrect(i, cells));
        if ((_isDone = _gm.isFinished(cells))) {
            congratStr->setTxt("Congratulation, you did it!\nPress ESC for exit.", 255);
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
    GameMaster GM;
    Sudoku *sudoku = new Sudoku(XX, YY, GM, "01.txt");
    sudoku->eventLoop();
    return 0;
}
