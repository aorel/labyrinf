#include "labyrinthDrawer.h"

LabyrinthDrawer::LabyrinthDrawer(const Labyrinth *l) :
        labyrinth(l){
    for(const auto &row : labyrinth->getCells()){
        std::vector<CellDrawer> cellDrawersRow;
        for(const auto &item : row){
            cellDrawersRow.emplace_back(&item);
        }
        cellDrawers.push_back(std::move(cellDrawersRow));
    }
    
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            cellDrawers[i][j].setPosition(settings::cellOffsetX+i*settings::cellSize, settings::cellOffsetY+j*settings::cellSize);
        }
    }
}

void LabyrinthDrawer::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void LabyrinthDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);
    for(const auto& row : cellDrawers){
        for(const auto& element : row){
            target.draw(element);
        }
    }
}
