#pragma once

#include <SFML/Graphics.hpp>

#include "game.h"

#include "labyrinthDrawable.h"
#include "playerDrawable.h"

class GameDrawable : public Game
{
public:
    GameDrawable();
    void run();
private:
    sf::RenderWindow window;
    sf::Event event;

    LabyrinthDrawable labyrinth;
    PlayerDrawable player;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    void events();
    void handler();
    void update(sf::Time);
    void render();

    void verifyCommand(Command);
};
