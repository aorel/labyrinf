#include "gameDrawable.h"

GameDrawable::GameDrawable() :
        Game(new LabyrinthDrawable){
    players.emplace_back(new PlayerDrawable);
}

void GameDrawable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void GameDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);

    //target.draw(labyrinthDrawer);
    const LabyrinthDrawable* labyrinthDrawable = dynamic_cast<LabyrinthDrawable*>(labyrinth.get());
    target.draw(*labyrinthDrawable);

    for(const auto &player : players){
        const PlayerDrawable* playerDrawable = dynamic_cast<PlayerDrawable*>(player.get());
        if (playerDrawable->getHealth() > 0){
            target.draw(*playerDrawable);
        }
        
    }
}
