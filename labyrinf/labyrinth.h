#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "cell.h"
#include "player.h"
#include "command.h"
#include "settings.h"


class Labyrinth : public sf::Drawable{
public:
    Labyrinth();
    bool verifyCommand(Player &p, Command &command, sf::Time delta_time);

private:
    std::vector< std::vector<Cell> > cells;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
