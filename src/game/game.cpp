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
    sf::Vector2i position = players[playerIndex]->getPosition();
    if (labyrinth->getBonus(position) == FIRE){
        players[playerIndex]->addHealth(-1);
        std::cout << " firee ";
    }
    else if (labyrinth->getBonus(position) == WATER){
        players[playerIndex]->changeWet();
        std::cout << " water ";
    }
    else if (labyrinth->getBonus(position) == HEART){
        players[playerIndex]->addHealth(1);
        std::cout << " heart ";
    }
}
