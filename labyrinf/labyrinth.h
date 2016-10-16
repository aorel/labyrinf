#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "cell.h"
#include "player.h"
#include "command.h"
#include "game_settings.h"


class Labyrinth : public sf::Drawable{
private:
    int id;

    size_t cells_size_x;
    size_t cells_size_y;
    std::vector< std::vector<Cell> > cells;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Labyrinth();
    bool verify_command(Player &p, Command &c, sf::Time delta_time);
};
