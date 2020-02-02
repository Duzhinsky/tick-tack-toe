#include "controller.h"

namespace controller {


GameController::GameController(model::GameModel* m) {
    model = m;
}

GameController::~GameController() {
    
}

void GameController::make_move(const uint8_t &x, const uint8_t &y) {
    if(model->get_cell_state(x,y) != model::UNDEFINED) return;
    model->set_cell_state(x, y, model->get_current_player());
    model->set_current_player(model->get_current_player() == model::X ? model::O : model::X);
    endgame_check();
}

model::State GameController::check_row(uint8_t index) {
    uint8_t field_size = model->config["game"]["field_size"];
    model::State result = model->get_cell_state(index, 0);
    for(uint8_t i = 1; i < field_size && result; ++i) 
        if(model->get_cell_state(index, i) != result) 
            result = model::UNDEFINED;
    return result;
}

model::State GameController::check_column(uint8_t index) {
    uint8_t field_size = model->config["game"]["field_size"];
    model::State result = model->get_cell_state(0, index);
    for(uint8_t i = 1; i < field_size && result; ++i) 
        if(model->get_cell_state(i, index) != result) 
            result = model::UNDEFINED;
    return result;
}

model::State GameController::check_main_diagonal() {
    uint8_t field_size = model->config["game"]["field_size"];
    model::State result = model->get_cell_state(0, 0);
    for(int i = 1; i < field_size; ++i)
        if(model->get_cell_state(i, i) != result)
            result = model::UNDEFINED;
    return result;
}

model::State GameController::check_side_diagonal() {
    uint8_t field_size = model->config["game"]["field_size"];
    model::State result = model->get_cell_state(0, field_size-1);
    for(int i = 1; i < field_size; ++i)
        if(model->get_cell_state(i, (field_size-1)-i) != result)
            result = model::UNDEFINED;
    return result;
}   

void GameController::endgame_check() {
    model::State winner = model::UNDEFINED;
    for(uint8_t i = 0; i < model->config["game"]["field_size"] && !winner; ++i)
        winner = check_row(i);
    for(uint8_t i = 0; i < model->config["game"]["field_size"] && !winner; ++i)
        winner = check_column(i);
    winner = winner ? winner : check_main_diagonal();
    winner = winner ? winner : check_side_diagonal();
    model->set_winner(winner);
}

}; // namespace controller