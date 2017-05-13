#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "graphics.hpp"
#include "window.hpp"
#include "gamemaster.hpp"

class Game : public Window{
protected:
    GameMaster _gm;
    int _time;
public:
    Game(unsigned short sizeX, unsigned short sizeY, GameMaster gm);
    virtual void gameLogic() = 0;
    virtual void eventLoop();
    virtual void printGameTime();
};

#endif // GAME_HPP_INCLUDED
