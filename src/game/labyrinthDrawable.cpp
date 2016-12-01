#include "labyrinthDrawable.h"

LabyrinthDrawable::LabyrinthDrawable() :
        Labyrinth( [](){return new CellDrawable;} ){
    test_init();
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            CellDrawable* cellDrawable = dynamic_cast<CellDrawable*>(cells[i][j].get());
            cellDrawable->setPosition(
                settings::cellDrawableOffsetX+i*settings::cellDrawableSize,
                settings::cellDrawableOffsetY+j*settings::cellDrawableSize
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
