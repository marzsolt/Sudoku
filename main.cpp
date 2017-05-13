#include <vector> // std::vector

//#include "widgets.hpp"
#include "sudokucell.hpp" // SudokuCell
//#include "statictxt.hpp"

#include "game.hpp" // Game
#include "gamemaster.hpp" // GameMaster

using namespace genv;

const unsigned short XX = 240, YY = 300; // Ablak mérete.

class Sudoku : public Game{
private:
    std::vector<SudokuCell*> cells;
public:
    Sudoku(unsigned short sizeX, unsigned short sizeY, GameMaster gm) : Game(sizeX, sizeY, gm) { }
    Sudoku(unsigned short sizeX, unsigned short sizeY, GameMaster gm, std::string filename) : Game(sizeX, sizeY, gm) {
        std::vector<unsigned short> nums = gm.loadFieldsFromFile(filename);
        for(int i = 0; i < 81; i++) {
            SudokuCell* tmp = new SudokuCell(10 + (i % 9) * (SudokuCell::sizeXSudokuCell() - 1)  + ((i % 9) / 3) * 6,
                                      10 + (i / 9) * (SudokuCell::sizeYSudokuCell() - 1) + ((i / 9) / 3) * 6, nums[i], 0, 9, nums[i]);
            cells.push_back(tmp);
            w.push_back(tmp);
        }
    }
    void gameLogic() {
        for (int i = 0; i < 81; i++)
            if (cells[i]->getNum() != 0)
                cells[i]->setCorrectness(_gm.isCorrect(i, cells));
    }
};

int main()
{
    GameMaster GM;
    Sudoku *sudoku = new Sudoku(XX, YY, GM, "01.txt");
    sudoku->eventLoop();
    return 0;
}
