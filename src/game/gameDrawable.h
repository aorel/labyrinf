#pragma once

#include <SFML/Graphics.hpp>

#include "game.h"
#include "labyrinthDrawable.h"
#include "playerDrawable.h"

class GameDrawable : public Game, public sf::Drawable{
public:
    GameDrawable();
    void builder() override;
    //void applyPlayerAction(int &playerIndex, Command &command) override;//TODO !!!

protected:
    std::unique_ptr<Labyrinth> labyrinthBuilder() override;
    std::unique_ptr<Player> playerBuilder() override;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
