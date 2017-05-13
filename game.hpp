#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "graphics.hpp"
#include "window.hpp"
#include "gamemaster.hpp"

class Game : public Window{
protected:
    GameMaster _gm;
    //virtual void gameLogic();
public:
    Game(unsigned short sizeX, unsigned short sizeY, GameMaster gm);
    void eventLoop();
};

#endif // GAME_HPP_INCLUDED
