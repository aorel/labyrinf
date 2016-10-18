#pragma once

#include <SFML/Graphics.hpp>
#include "labyrinth.h"
#include "player.h"
#include "command.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;

    Player player;
    Labyrinth labyrinth;

    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f/60.f);
    
    void events();
    void handler();
    void update(sf::Time delta_time);
    void render();

    void verify_action(Action action);
public:
    Game();
    void run();
};
