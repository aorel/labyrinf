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

Labyrinth::Labyrinth() : cells_size_x(15),
                         cells_size_y(17),
                         cells(cells_size_x, std::vector<Cell> (cells_size_y, Cell())){
    for(int i(0); i<cells_size_x; ++i){
        for(int j(0); j<cells_size_y; ++j){
            cells[i][j].setPosition(settings::cell_offset_x+i*settings::cell_size, settings::cell_offset_y+j*settings::cell_size);
        }
    }
}

bool Labyrinth::verify_command(Player &p, Command &command, sf::Time delta_time){
    sf::Vector2i position = p.get_position();
    if(position.x == 0 && command.action == Player_left){
        return false;
    }
    else if(position.x == (cells_size_x-1) && command.action == Player_right){
        return false;
    }
    else if(position.y == 0 && command.action == Player_up){
        return false;
    }
    else if(position.y == (cells_size_y-1) && command.action == Player_down){
        return false;
    }
    return true;
}
