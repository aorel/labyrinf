#include "labyrinth.h"

Labyrinth::Labyrinth() : cells(settings::labyrinthSizeX, std::vector<Cell*> (settings::labyrinthSizeY)){
    for(int i(0); i < settings::labyrinthSizeX; ++i){
        for(int j(0); j < settings::labyrinthSizeY; ++j){
            cells[i][j] = new Cell();
            cells[i][j]->setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }
    }

    for(auto i = 0; i < 5; ++i)
    {
        for(auto j = 0; j < 1; ++j)
        {
            cells[i][j] = new Wall;
            cells[i][j]->setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }

        for(auto j = 3; j < 5; ++j)
        {
            cells[i][j] = new Wall;
            cells[i][j]->setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }
    }
}

bool Labyrinth::verifyCommand(Player &p, Command &command){
    sf::Vector2i position = p.getPosition();
    if(command == PlayerLeft)
        std::cout << "(" << position.x - 1 << "," << position.y << ")" << std::endl;
    if(command == PlayerRight)
        std::cout << "(" << position.x + 1 << "," << position.y << ")" << std::endl;
    if(command == PlayerUp)
        std::cout << "(" << position.x << "," << position.y - 1 << ")" << std::endl;
    if(command == PlayerDown)
        std::cout << "(" << position.x << "," << position.y + 1 << ")" << std::endl;

    if(position.x == 0 && command == PlayerLeft){
        return false;
    }
    else if(position.x == (settings::labyrinthSizeX - 1) && command == PlayerRight){
        return false;
    }
    else if(position.y == 0 && command == PlayerUp){
        return false;
    }
    else if(position.y == (settings::labyrinthSizeY - 1) && command == PlayerDown){
        return false;
    }
    else if(command == PlayerLeft && cells[position.x - 1][position.y]->isWall()){
        return false;
    }
    else if(command == PlayerRight && cells[position.x + 1][position.y]->isWall()){
        return false;
    }
    else if(command == PlayerDown && cells[position.x][position.y + 1]->isWall()){
        return false;
    }
    else if(command == PlayerUp && cells[position.x][position.y - 1]->isWall()){
        return false;
    }

    return true;
}

void Labyrinth::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);
    for(const auto& row : cells){
        for(const auto& elem : row){
            target.draw(*elem);
            //elem.draw(target, states);
        }
    }
}

void Labyrinth::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
}
