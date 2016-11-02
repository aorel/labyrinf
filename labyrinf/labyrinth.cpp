#include "labyrinth.h"

Labyrinth::Labyrinth() :
        cells(settings::labyrinthSizeX, std::vector<Cell> (settings::labyrinthSizeY, Cell())){
    /*for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            cells[i][j].setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }
    }*/
    
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            if( i == 0 || i == settings::labyrinthSizeX-1 || j == 0 || j == settings::labyrinthSizeY-1 ){
                cells[i][j].setType(WALL);
            }
            else if( i == j){
                cells[i][j].setType(WATER);
            }
            else if( i+1 == j){
                cells[i][j].setType(FIRE);
            }
            else{
                cells[i][j].setType(GROUND);
            }
        }
    }
    
    /*for(int i(0); i<settings::labyrinthSizeX; ++i){
        cells[i][0].setType(WALL);
        cells[i][settings::labyrinthSizeY-1].setType(WALL);
    }
    for(int j(1); j<settings::labyrinthSizeY-1; ++j){
        cells[0][j].setType(WALL);
        cells[settings::labyrinthSizeX-1][j].setType(WALL);
    }*/
}

bool Labyrinth::checkCommand(Player &p, Command &command){
    sf::Vector2i position = p.getPosition();
    if(command == PlayerUp && position.y == 0){
        return false;
    }
    else if(command == PlayerDown && position.y == (settings::labyrinthSizeY-1)){
        return false;
    }
    else if(command == PlayerLeft && position.x == 0){
        return false;
    }
    else if(command == PlayerRight && position.x == (settings::labyrinthSizeX-1)){
        return false;
    }

    
    
    if(command == PlayerUp && cells[position.x][position.y-1].getType() == WALL){
        return false;
    }
    else if(command == PlayerDown && cells[position.x][position.y+1].getType() == WALL){
        return false;
    }
    else if(command == PlayerLeft && cells[position.x-1][position.y].getType() == WALL){
        return false;
    }
    else if(command == PlayerRight && cells[position.x+1][position.y].getType() == WALL){
        return false;
    }
    return true;
}

const std::vector<std::vector<Cell>>& Labyrinth::getCells() const{
    return cells;
}
