#include "model.h"

namespace model {

GameModel::GameModel(const uint8_t &f_s) {
    field_size = f_s;
    field.reserve(f_s);
    for(uint8_t i = 0; i < f_s; ++i)
        field[i].assign(f_s, CellState::UNDEFINED);
}

void GameModel::set_cell_state(const uint8_t &x, const uint8_t &y, const CellState &state) {
    field[x][y] = state;
    notify_update();
}

CellState GameModel::get_cell_state(const uint8_t &x, const uint8_t &y) {
    return field[x][y];
}

void GameModel::set_current_player(const CellState& state) {
    c_player = state;
    notify_update();
}

CellState GameModel::current_player() {
    return c_player;
}

void GameModel::set_winner(const CellState &w) {
    winner = w;
    notify_update();
}

CellState GameModel::get_winner() {
    return winner;
}

uint8_t GameModel::get_field_size() {
    return field_size;
}


} // namespace model