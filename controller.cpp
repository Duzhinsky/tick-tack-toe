#include "controller.h"

namespace controller {

#define cell(x,y) model->get_cell_state(x,y)

GameController::GameController(model::GameModel* m) {
    model = m;
}

GameController::~GameController() {
    
}

void GameController::make_move(const uint8_t &x, const uint8_t &y) {
    if(model->get_cell_state(x,y) != model::CellState::UNDEFINED) return;
    model->set_cell_state(x, y, model->current_player());
    model->set_current_player(model->current_player() == model::X ? model::O : model::X);
    endgame_check();
}

void GameController::endgame_check() {
    model::CellState winner = model::CellState::UNDEFINED;
    if(cell(0,0) == cell(0, 1) && cell(0, 1) == cell(0,2) && cell(0,0) != model::UNDEFINED)
        winner = cell(0,0);
    else if(cell(1,0) == cell(1, 1) && cell(1, 1) == cell(1,2) && cell(1,0) != model::UNDEFINED)
        winner = cell(1,0);
    else if(cell(2,0) == cell(2, 1) && cell(2, 1) == cell(2,2) && cell(2,0) != model::UNDEFINED)
        winner = cell(2,0);

    if(cell(0, 0) == cell(1, 0) && cell(1,0) == cell(2,0) && cell(0,0) != model::UNDEFINED)
        winner = cell(0,0);
    else if(cell(0, 1) == cell(1, 1) && cell(1,1) == cell(2,1) && cell(0,1) != model::UNDEFINED)
        winner = cell(0, 1);
    else if(cell(0, 2) == cell(1, 2) && cell(1,2) == cell(2,2) && cell(0,2) != model::UNDEFINED)
        winner = cell(0, 2);

    else if(cell(0,0) == cell(1,1) && cell(1,1) == cell(2,2) && cell(0, 0) != model::UNDEFINED)
        winner = cell(0,0);
    else if(cell(0, 2) == cell(1,1) && cell(1,1) == cell(2,0 && cell(2,0) != model::UNDEFINED))
        winner = cell(2,0);
    model->set_winner(winner);
}

}; // namespace controller