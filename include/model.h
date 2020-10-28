#ifndef MODEL_H
#define MODEL_H

#include "observer.h"

#include <fstream>
#include "json.hpp"

#include <cstdint>

namespace model {

enum State {
    UNDEFINED,
    X,
    O
}; // enum State

class GameModel : public Observable {
    public:
        GameModel();

    public:
        void  set_cell_state(const uint8_t &x, const uint8_t &y, const State &state);
        State get_cell_state(const uint8_t &x, const uint8_t &y);
        void  set_current_player(const State &state);
        State get_current_player();
        void  set_winner(const State &w);
        State get_winner();

    public:
        const struct ConfigBasic : nlohmann::json {
            ConfigBasic();
        } config;

    private:
        State **field;
        State current_player = X;
        State winner = UNDEFINED;
}; // class GameModel
 
} // namespace model

#endif // MODEL_H