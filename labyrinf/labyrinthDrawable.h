#pragma once

#include <SFML/Graphics.hpp>

#include "labyrinth.h"
#include "cellDrawable.h"

class LabyrinthDrawable : public Labyrinth, public sf::Drawable{
public:
    LabyrinthDrawable();

private:
    std::vector<std::vector<CellDrawable>> cells;

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
