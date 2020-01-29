#ifndef MODEL_H
#define MODEL_H

#include "observer.h"

#include <vector>
#include <cstdint>

namespace model {

enum CellState {
    UNDEFINED,
    X,
    O
}; // enum CellState

class GameModel : public Observable {
    public:
        GameModel(const uint8_t &f_s);

        void set_cell_state(const uint8_t &x, const uint8_t &y, const CellState &state);
        CellState get_cell_state(const uint8_t &x, const uint8_t &y);
        void set_current_player(const CellState &state);
        CellState current_player();
        void set_winner(const CellState &w);
        CellState get_winner();
        uint8_t get_field_size();
    private:
        std::vector<std::vector<CellState>>  field;
        uint8_t field_size;
        CellState c_player = X;
        CellState winner = UNDEFINED;
}; // class GameModel
 
} // namespace model

#endif // MODEL_H