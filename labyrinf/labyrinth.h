#pragma once

//#include <SFML/Graphics.hpp>
#include <vector>

#include "cell.h"
#include "player.h"
#include "command.h"
#include "settings.h"


class Labyrinth{
public:
    Labyrinth();
    bool verifyCommand(Player &p, Command &command);
    //const std::vector<std::vector<Cell>>& getCells() const;

private:
    std::vector<std::vector<Cell>> cells;

    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    //void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
