#pragma once

#include <SFML/Graphics.hpp>

#include "labyrinth.h"
#include "cellDrawable.h"

#include <iostream>

class LabyrinthDrawable : public Labyrinth, public sf::Drawable{
public:
    LabyrinthDrawable();
    virtual ~LabyrinthDrawable() = default;

private:

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
