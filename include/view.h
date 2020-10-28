#ifndef VIEW_H
#define VIEW_H

#include "observer.h"
#include "model.h"
#include "controller.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace view {

class WindowView : public sf::Thread, public Observer {
    public:
        WindowView(model::GameModel *m, controller::GameController *c);
        ~WindowView();
        virtual void update();
        bool is_running();

    private:
        void window_callback();

    private:
        model::GameModel           *model;
        controller::GameController *controller;
        
        sf::RenderWindow           window;
        sf::Font                   state_font;
        sf::RectangleShape         cell;
        sf::Text                   cell_text;

        int    mouse_x = 0,        mouse_y = 0;

        int    cell_size = 0,      cell_clearance = 0; 
        int    state_font_size = 0;
        int    field_x0 = 0,       field_y0 = 0;


}; // class WindowView

} // namespace view

#endif // VIEW_H