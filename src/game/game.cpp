#include "game.h"

Game::Game() :
        Game(new Labyrinth){
    players.emplace_back(new Player);
}
Game::Game(Labyrinth *_l) :
    labyrinth(_l){
}

//TODO command заменить на полное поисание действия: объект, действие
bool Game::checkPlayerAction(int &playerIndex, Command &command){
    if(players[playerIndex]->readyForNewCommand()){
        if(labyrinth->checkCommand(*players[playerIndex], command)){
            return true;
        }
    }
    return false;
}

void Game::applyPlayerAction(int &playerIndex, Command &command){
    players[playerIndex]->applyCommand(command);
}
