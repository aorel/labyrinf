#include "labyrinth.h"

Labyrinth::Labyrinth() : cells(settings::labyrinthSizeX, std::vector<Cell> (settings::labyrinthSizeY, Cell())){
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            cells[i][j].setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }
    }
}

bool Labyrinth::verifyCommand(Player &p, Command &command){
    sf::Vector2i position = p.getPosition();
    if(position.x == 0 && command == PlayerLeft){
        return false;
    }
    else if(position.x == (settings::labyrinthSizeX-1) && command == PlayerRight){
        return false;
    }
    else if(position.y == 0 && command == PlayerUp){
        return false;
    }
    else if(position.y == (settings::labyrinthSizeY-1) && command == PlayerDown){
        return false;
    }
    return true;
}

void Labyrinth::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);
    for(const auto& row : cells){
        for(const auto& elem : row){
            target.draw(elem);
            //elem.draw(target, states);
        }
    }
}

void Labyrinth::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
}
