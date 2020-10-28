#include "view.h"
#include <iostream>

namespace view {

WindowView::WindowView(model::GameModel *m, controller::GameController *c) 
  : sf::Thread(&WindowView::window_callback, this) {
    model = m;
    model->add_observer(this);
    controller = c;

    cell_size =  ceil(
                 double(model->config["window"]["field_width"]) /
                 double(model->config["game"]["field_size"]) * 
                 double(model->config["window"]["cell_part"])
                 );

    cell_clearance = floor(
                     double(cell_size) / 
                     double(model->config["window"]["cell_part"]) * 
                     (1.f-double(model->config["window"]["cell_part"]))
                     );

    state_font_size = cell_size/2; 
    
    field_x0 = ((uint16_t)model->config["window"]["width"] 
                 -(uint16_t)model->config["window"]["field_width"])/2;
    field_y0 = ((uint16_t)model->config["window"]["height"] 
                 -(uint16_t)model->config["window"]["field_width"])/2;

    cell.setSize(sf::Vector2f(cell_size, cell_size));
    cell.setOutlineThickness(cell_clearance/2);
    cell.setOutlineColor(sf::Color(model->config["window"]["color"]["background"]));

    state_font.loadFromFile(model->config["window"]["font_files"]["cell_state"]);
    cell_text.setFont(state_font); 
    cell_text.setCharacterSize(state_font_size);
    cell_text.setFillColor(sf::Color(model->config["window"]["color"]["background"]));
    

    window.create(sf::VideoMode(model->config["window"]["width"], 
                                model->config["window"]["height"]),
                  (std::string)model->config["window"]["title"]);
    this->launch();
}

WindowView::~WindowView() {
    this->terminate();
}

void WindowView::window_callback() {
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    window.setSize(sf::Vector2u(model->config["window"]["width"], 
                                                model->config["window"]["height"]));
                    break;
                }
                case sf::Event::MouseMoved: {
                    mouse_x = event.mouseMove.x;
                    mouse_y = event.mouseMove.y;
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if(model->get_winner() != model::UNDEFINED) break;
                    int i = (mouse_y - field_y0)/(cell_size+cell_clearance);
                    int k = (mouse_x - field_x0)/(cell_size+cell_clearance);
                    controller->make_move(k, i);
                }
                default:
                    break;
            }
        }
        if(!window.isOpen()) break;
        update();
   }
}

void WindowView::update() {
    window.clear(sf::Color(model->config["window"]["color"]["background"]));
    
    for(uint8_t i = 0; i < model->config["game"]["field_size"]; ++i) {
        for(uint8_t k = 0; k < model->config["game"]["field_size"]; ++k) {
            cell.setPosition(field_x0 + (cell_size+cell_clearance)*k,
                             field_y0 + (cell_size+cell_clearance)*i);

            if(mouse_x >= field_x0 + (cell_size+cell_clearance)*k &&
               mouse_x <= field_x0 + (cell_size+cell_clearance)*k + cell_size &&
               mouse_y >= field_y0 + (cell_size+cell_clearance)*i &&
               mouse_y <= field_y0 + (cell_size+cell_clearance)*i + cell_size &&
               model->get_cell_state(k,i) == model::UNDEFINED &&
               model->get_winner() == model::UNDEFINED) {
                cell.setFillColor(sf::Color(model->config["window"]["color"]["cell"]));
            } else cell.setFillColor(sf::Color(model->config["window"]["color"]["cell_hover"]));

            if(model->get_cell_state(k,i) == model::X)
                cell_text.setString("X");
            else if(model->get_cell_state(k,i) == model::O)
                cell_text.setString("O");
            else
                cell_text.setString(" ");
            cell_text.setPosition(
                field_x0 + (cell_size+cell_clearance)*k + (cell_size-0.5*state_font_size)/2,
                field_y0 + (cell_size+cell_clearance)*i + (cell_size-state_font_size)/2);

            window.draw(cell);
            window.draw(cell_text);
        }
    }


    window.display();
}

} // namespace view