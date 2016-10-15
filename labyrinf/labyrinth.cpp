#include "labyrinth.h"

Labyrinth::Labyrinth() : id(0),
                         cells_size_x(15),
                         cells_size_y(15),
                         cell(sf::Vector2f(50, 50)){
    cell.setFillColor(sf::Color(50, 50, 50));
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color(150, 150, 150));
}

void Labyrinth::draw(sf::RenderWindow &window){
    for(size_t i(0); i<cells_size_x; ++i){
        for(size_t j(0); j<cells_size_y; ++j){
            cell.setPosition(game_settings::offset_x+i*game_settings::cell_size, game_settings::offset_y+j*game_settings::cell_size);
            window.draw(cell);
        }
    }
}
