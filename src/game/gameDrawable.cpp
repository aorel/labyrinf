#include "gameDrawable.h"

GameDrawable::GameDrawable(){
    std::cout << "GameDrawable()" << std::endl;
        //Game(new LabyrinthDrawable){
    //players.emplace_back(playerBuilder());
}

void GameDrawable::builder(){
    std::cout << "GameDrawable::builder" << std::endl;
    Game::builder();
    players.emplace_back(playerBuilder());
}

std::unique_ptr<Labyrinth> GameDrawable::labyrinthBuilder(){
    std::cout << "new LabyrinthDrawable"<< std::endl;
    return std::unique_ptr<Labyrinth>(new LabyrinthDrawable);
}
std::unique_ptr<Player> GameDrawable::playerBuilder(){
    std::cout << "new PlayerDrawable"<< std::endl;
    return std::unique_ptr<Player>(new PlayerDrawable);
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
        target.draw(*playerDrawable);
    }
}
