#include "labyrinthDrawable.h"

LabyrinthDrawable::LabyrinthDrawable() :
        Labyrinth( [](){return new CellDrawable;} ){
    generatorInit();
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            CellDrawable* cellDrawable = dynamic_cast<CellDrawable*>(cells[i][j].get());
            cellDrawable->setPosition(
                settingsDrawable::cellDrawableOffsetX+i*settingsDrawable::cellDrawableSize,
                settingsDrawable::cellDrawableOffsetY+j*settingsDrawable::cellDrawableSize
            );
        }
    }
}

void LabyrinthDrawable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void LabyrinthDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);

    for(const auto& row : cells){
        for(const auto& cell : row){
            const CellDrawable* cellDrawable = dynamic_cast<CellDrawable*>(cell.get());
            target.draw(*cellDrawable);
        }
    }

}
