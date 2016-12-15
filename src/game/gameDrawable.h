#pragma once

#include <SFML/Graphics.hpp>

#include "game.h"
#include "labyrinthDrawable.h"
#include "playerDrawable.h"

class GameDrawable : public Game, public sf::Drawable{
public:
    GameDrawable();
    void init() override;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
