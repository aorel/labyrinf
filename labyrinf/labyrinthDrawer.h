#pragma once

#include <SFML/Graphics.hpp>

#include "labyrinth.h"
#include "cellDrawer.h"

class LabyrinthDrawer : public sf::Drawable{
public:
    explicit LabyrinthDrawer(const Labyrinth *l);

private:
    const Labyrinth *labyrinth;
    std::vector<std::vector<CellDrawer>> cellDrawers;

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
