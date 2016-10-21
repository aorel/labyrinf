#include "labyrinthDrawable.h"

LabyrinthDrawable::LabyrinthDrawable() :
        cells(settings::labyrinthSizeX, std::vector<CellDrawable> (settings::labyrinthSizeY, CellDrawable())){
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            cells[i][j].setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }
    }
}

void LabyrinthDrawable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void LabyrinthDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);
    for(const auto& row : cells){
        for(const auto& element : row){
            target.draw(element);
        }
    }
}
