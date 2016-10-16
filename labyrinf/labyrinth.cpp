#include "labyrinth.h"

void Labyrinth::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    //states.transform *= getTransform();
    drawCurrent(target, states);
    for(auto& row : cells){
        for(auto& elem : row){
            target.draw(elem);
            //elem.draw(target, states);
        }
    }
}

void Labyrinth::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
}

Labyrinth::Labyrinth() : id(0),
                         cells_size_x(15),
                         cells_size_y(15),
                         cells(cells_size_x, std::vector<Cell> (cells_size_y, Cell())){
    for(size_t i(0); i<cells_size_x; ++i){
        for(size_t j(0); j<cells_size_y; ++j){
            cells[i][j].setPosition(game_settings::offset_x+i*game_settings::cell_size, game_settings::offset_y+j*game_settings::cell_size);
        }
    }
}

bool Labyrinth::verify_command(Player &p, Command &c, sf::Time delta_time){
    return true;
}
