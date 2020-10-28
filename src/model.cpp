#include "model.h"

namespace model {

GameModel::GameModel() {
    uint8_t field_size = config["game"]["field_size"];
    field = new State*[field_size];
    for(uint8_t i = 0; i < field_size; ++i) 
        field[i] = new State[field_size];
    for(uint8_t i = 0; i < field_size; ++i)
        for(uint8_t k = 0; k < field_size; ++k)
            field[i][k] = UNDEFINED;
}

GameModel::ConfigBasic::ConfigBasic() {
    std::ifstream i(".config.json");
    i >> *this;
}

void GameModel::set_cell_state(const uint8_t &x, const uint8_t &y, const State &state) {
    field[x][y] = state;
    notify_update();
}

State GameModel::get_cell_state(const uint8_t &x, const uint8_t &y) {
    return field[x][y];
}

void GameModel::set_current_player(const State& state) {
    current_player = state;
    notify_update();
}

State GameModel::get_current_player() {
    return current_player;
}

void GameModel::set_winner(const State &w) {
    winner = w;
    notify_update();
}

State GameModel::get_winner() {
    return winner;
}

} // namespace model