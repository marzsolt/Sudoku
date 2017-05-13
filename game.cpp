#include "graphics.hpp"
#include "game.hpp"
#include "gamemaster.hpp"

using namespace genv;

Game::Game(unsigned short sizeX, unsigned short sizeY, GameMaster gm) : Window(sizeX, sizeY), _gm(gm), _time(0) {}

void Game::eventLoop() {
    gout.open(_sizeX, _sizeY);
    gout << move_to(0, 0) << color(255, 255, 255) << box(_sizeX, _sizeY) << refresh;
    gin.timer(1000);
    event ev;
    int focus = -1;
    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            for (size_t i = 0; i < w.size(); i++) {
                if (w[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    if(focus != -1)
                        w[focus]->lost_focus(ev);
                    focus = i;
                }
            }
        }
        else if (ev.type == ev_timer)
            printGameTime();
        else if (ev.type == ev_key && ev.keycode == key_enter)
            newGame();
        if (focus != -1) {
            w[focus]->handle(ev);
        }
        for (Widget * v : w)
            v->draw();
        gameLogic();
        gout << refresh;
    }
}

void Game::printGameTime() {
    _time++;
}
