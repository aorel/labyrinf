#include "labyrinth.h"

Labyrinth::Labyrinth() : Labyrinth( [](){return new Cell;} ){
    test_init();
}

Labyrinth::Labyrinth(std::function< Cell* () > cellFactory){
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        std::vector<std::unique_ptr<Cell>> cellRow;
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            cellRow.emplace_back( cellFactory() );
        }
        cells.push_back(std::move(cellRow));
    }
}

CellType Labyrinth::getBonus(sf::Vector2i place)
{
    if (cells[place.x][place.y]->getType() == HEART){
        cells[place.x][place.y]->setType(GROUND);
        return HEART;
    }
    return cells[place.x][place.y]->getType();
}

bool Labyrinth::checkCommand(const Player &p, Command &command){
    sf::Vector2i position = p.getPosition();

    if(command == PlayerUp && cells[position.x][position.y-1]->getType() == WALL){
        return false;
    }
    else if(command == PlayerDown && cells[position.x][position.y+1]->getType() == WALL){
        return false;
    }
    else if(command == PlayerLeft && cells[position.x-1][position.y]->getType() == WALL){
        return false;
    }
    else if(command == PlayerRight && cells[position.x+1][position.y]->getType() == WALL){
        return false;
    }
    return true;
}

void Labyrinth::test_init(){
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            if( i == 0 || i == settings::labyrinthSizeX-1 || j == 0 || j == settings::labyrinthSizeY-1 ){
                cells[i][j]->setType(WALL);//cells[i][j].setType(WALL);
            }
            else if( i == j){
                cells[i][j]->setType(WATER);
            }else if( i+1 == j){
                cells[i][j]->setType(HEART);
            }
            else if( i+2 == j){
                cells[i][j]->setType(FIRE);
            }
            else{
                cells[i][j]->setType(GROUND);
            }
        }
    }
}
