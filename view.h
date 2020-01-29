#ifndef VIEW_H
#define VIEW_H

#include "observer.h"
#include "model.h"
#include "controller.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WINDOW_TITLE          "X-O"
#define WINDOW_WIDTH          600
#define WINDOW_HEIGHT         700
#define BACKGROUND_COLOR      0xFFFFFFFF

#define CELL_SIZE             120
#define CELL_CLEARANCE        10
#define CELL_COLOR            0x66AAE8FF
#define CELL_SELECTED_COLOR   0x0076beff
#define CELL_FONT_SIZE        72

namespace view {

class WindowView : public Observer {
    public:
        WindowView(model::GameModel *m, controller::GameController *c);
        ~WindowView();
        virtual void update();
        bool is_running();

    private:
        void window_callback();

    private:
        model::GameModel *model;
        controller::GameController *controller;
        sf::Thread m_thread;
        bool closed = false;
        
        sf::RenderWindow window;
        sf::Font font;
        sf::RectangleShape cell;
        sf::Text cell_text;

        int mouse_x = 0, mouse_y = 0;


}; // class WindowView

} // namespace view

#endif // VIEW_H