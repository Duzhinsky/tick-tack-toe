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
        model::State check_row(uint8_t index);
        model::State check_column(uint8_t index);
        model::State check_main_diagonal();
        model::State check_side_diagonal();

    private:
        model::GameModel* model;


}; // class GameController


}; // namespace controller

#endif // CONTROLLER_H