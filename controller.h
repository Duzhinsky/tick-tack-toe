#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

#include <iostream>

namespace controller {

class GameController {

    public:
        GameController(model::GameModel* m);
        ~GameController();
        
        void make_move(const uint8_t &x, const uint8_t &y);
        void endgame_check();
    private:
        model::GameModel* model;


}; // class GameController


}; // namespace controller

#endif // CONTROLLER_H