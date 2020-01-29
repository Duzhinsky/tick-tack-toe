#include "view.h"

namespace view {

WindowView::WindowView(model::GameModel *m, controller::GameController *c) 
  : m_thread(&WindowView::window_callback, this),
  window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE) {
    model = m;
    controller = c;
    model->add_observer(this);
    m_thread.launch();

    font.loadFromFile("BebasNeue-Regular.ttf");
    cell.setFillColor(sf::Color(CELL_COLOR));
    cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setOutlineThickness(CELL_CLEARANCE);
    cell.setOutlineColor(sf::Color(BACKGROUND_COLOR));
    cell_text.setFont(font); 
    cell_text.setCharacterSize(CELL_FONT_SIZE);
    cell_text.setColor(sf::Color(BACKGROUND_COLOR));
}

WindowView::~WindowView() {
    m_thread.wait();
}

bool WindowView::is_running() {
    if(closed) {   
        m_thread.wait();
        return false;
    } 
    return true;
}

void WindowView::window_callback() {
    sf::Event event;
    while (window.isOpen()) {
        const int x0 = (WINDOW_WIDTH-(CELL_SIZE+2*CELL_CLEARANCE)*model->get_field_size())/2;
        const int y0 = (WINDOW_HEIGHT-(CELL_SIZE+2*CELL_CLEARANCE)*model->get_field_size())/2;  

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
                    break;
                }
                case sf::Event::MouseMoved: {
                    mouse_x = event.mouseMove.x;
                    mouse_y = event.mouseMove.y;
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if(model->get_winner() != model::UNDEFINED) break;
                    int i = (mouse_y - y0)/(CELL_SIZE+2*CELL_CLEARANCE);
                    int k = (mouse_x - x0)/(CELL_SIZE+2*CELL_CLEARANCE);
                    controller->make_move(k, i);
                }
                default:
                    break;
            }
        }
        if(!window.isOpen()) break;
        update();
   }
   closed = true;
}

void WindowView::update() {
    window.clear(sf::Color(BACKGROUND_COLOR));
    const int x0 = (WINDOW_WIDTH-(CELL_SIZE+2*CELL_CLEARANCE)*model->get_field_size())/2;
    const int y0 = (WINDOW_HEIGHT-(CELL_SIZE+2*CELL_CLEARANCE)*model->get_field_size())/2;  

    for(uint8_t i = 0; i < model->get_field_size(); ++i) {
        for(uint8_t k = 0; k < model->get_field_size(); ++k) {
            cell.setPosition(x0 + (CELL_SIZE+2*CELL_CLEARANCE)*k, y0 + (CELL_SIZE+2*CELL_CLEARANCE)*i);
            if(model->get_cell_state(k,i) == model::CellState::X)
                cell_text.setString("X");
            else if(model->get_cell_state(k,i) == model::CellState::O)
                cell_text.setString("O");
            else
                cell_text.setString(" ");
            cell_text.setPosition(
                x0 + (CELL_SIZE+2*CELL_CLEARANCE)*k + (CELL_SIZE-0.5*CELL_FONT_SIZE)/2,
                y0 + (CELL_SIZE+2*CELL_CLEARANCE)*i + (CELL_SIZE-CELL_FONT_SIZE)/2);

            if(mouse_x >= x0 + (CELL_SIZE+2*CELL_CLEARANCE)*k &&
                mouse_x <= x0 + (CELL_SIZE+2*CELL_CLEARANCE)*k + CELL_SIZE &&
                mouse_y >= y0 + (CELL_SIZE+2*CELL_CLEARANCE)*i &&
                mouse_y <= y0 + (CELL_SIZE+2*CELL_CLEARANCE)*i + CELL_SIZE &&
                model->get_cell_state(k,i) == model::CellState::UNDEFINED) {
                    
                cell.setFillColor(sf::Color(CELL_SELECTED_COLOR));
                window.draw(cell);
                cell.setFillColor(sf::Color(CELL_COLOR));
            } else window.draw(cell);
                
            window.draw(cell_text);
        }
    } 
    window.display();
}

} // namespace view