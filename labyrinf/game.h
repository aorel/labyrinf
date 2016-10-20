#pragma once

#include <SFML/Graphics.hpp>
#include "labyrinth.h"
#include "player.h"
#include "command.h"

class Game
{
public:
    Game();
    void run();
private:
    sf::RenderWindow window;
    sf::Event event;

    Player player;
    Labyrinth labyrinth;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    void events();
    void handler();
    void update(sf::Time);
    void render();

    void verifyCommand(Command);
};
