#pragma once

#include <SFML/Graphics.hpp>

#include "serverGame.h"
#include "labyrinthDrawer.h"
#include "playerDrawer.h"

#include "labyrinthDrawable.h"
#include "playerDrawable.h"

class ClientGame : public ServerGame, public sf::Drawable{
public:
    ClientGame();
    void applyPlayerAction(int &playerIndex, Command &command) override;

private:
    LabyrinthDrawer labyrinthDrawer;
    std::vector<PlayerDrawer> playerDrawer;

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
