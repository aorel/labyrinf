

#include "game.h"

Game::Game() :
        Game(new Labyrinth){
    players.emplace_back(new Player);
}
Game::Game(Labyrinth *_l) :
    labyrinth(_l){
}

//TODO command заменить на полное поисание действия: объект, действие
bool Game::checkPlayerAction(int &playerIndex, const PlayerEvent& playerEvent){
    if(players[playerIndex]->readyForNewCommand()){
        if(labyrinth->checkCommand(*players[playerIndex], playerEvent)){
            return true;
        }
    }
    return false;
}

void Game::applyPlayerAction(int &playerIndex, const PlayerEvent& playerEvent){
    players[playerIndex]->applyCommand(playerEvent);
}
