#include "clientGame.h"

ClientGame::ClientGame() :
    ServerGame(new LabyrinthDrawable(), new PlayerDrawable()),
    labyrinthDrawer(&labyrinth){
        
    //l( new LabyrinthDrawable::LabyrinthDrawable() ),
    //p( new PlayerDrawable() ){
    


    players.emplace_back();
    
    playerDrawer.emplace_back(&players[0]);
}

void ClientGame::applyPlayerAction(int &playerIndex, Command &command){
    ServerGame::applyPlayerAction(playerIndex, command);

    //sf::Vector2i position = players[playerIndex].getPosition();
    playerDrawer[playerIndex].updatePosition();
}

void ClientGame::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void ClientGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);

    target.draw(labyrinthDrawer);

    for(const auto &item : playerDrawer){
        target.draw(item);
    }
}
