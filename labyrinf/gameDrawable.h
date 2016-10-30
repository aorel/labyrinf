#pragma once

#include <SFML/Graphics.hpp>

#include "game.h"

#include "labyrinthDrawable.h"
#include "playerDrawable.h"

class GameDrawable : public Game, public sf::Drawable{
public:
    GameDrawable() = default;
    
    //GameDrawable(std::function< void(Command) > vCC);
    //void run();
private:
    //std::function< void(Command) > verifyCommandCallback;

    LabyrinthDrawable labyrinth;
    std::vector<Player> players;
    PlayerDrawable currentPlayer;

    /*sf::RenderWindow window;
    sf::Event event;

    LabyrinthDrawable labyrinth;
    PlayerDrawable player;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    void events();
    void handler();
    void update(sf::Time);
    void render();*/

    //void verifyCommand(Command);
    
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
