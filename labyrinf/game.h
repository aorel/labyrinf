#pragma once

#include <SFML/Graphics.hpp>

#include "command.h"

#include "labyrinthDrawable.h"//TODO
#include "playerDrawable.h"//TODO

class Game
{
public:
    Game();
    void run();
private:
    sf::RenderWindow window;
    sf::Event event;

    //Labyrinth labyrinth;
    LabyrinthDrawable labyrinth;//TODO
    //Player player;
    PlayerDrawable player;//TODO

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    void events();
    void handler();
    void update(sf::Time);
    void render();

    void verifyCommand(Command);
};
