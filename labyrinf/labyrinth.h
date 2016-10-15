#pragma once

#include <SFML/Graphics.hpp>
#include "game_settings.h"


class Labyrinth{
private:
    int id;
    
    size_t cells_size_x;
    size_t cells_size_y;
    sf::RectangleShape cell;

public:
    Labyrinth();
    void draw(sf::RenderWindow &window);
};
