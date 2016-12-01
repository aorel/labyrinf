#include "game.h"

Game::Game() :
        Game(new Labyrinth){
    players.emplace_back(new Player);
    isGame = 1;
}
Game::Game(Labyrinth *_l) :
    labyrinth(_l){
        isGame = 1;
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

bool Game::applyPlayerAction(int &playerIndex, Command &command){
    players[playerIndex]->applyCommand(command);
    sf::Vector2i position = players[playerIndex]->getPosition();
    CellType place = labyrinth->getBonus(position);
    if (place == FIRE){
        players[playerIndex]->addHealth(-1);
        std::cout << " firee " << players[playerIndex]->getHealth() << std::endl;
    }
    else if (place == WATER){
        players[playerIndex]->changeWet();
        std::cout << " water ";
    }
    else if (place == HEART){
        players[playerIndex]->addHealth(1);
        std::cout << " heart " << players[playerIndex]->getHealth() << std::endl;
    }
    if (players[playerIndex]->getHealth() > 0){
        return true;
    }
    return false;
}

void Game::menu()
{
    isGame = 0;
    for (const auto &player : players)
    {
        if (player->getHealth() > 0){
            isGame = 1;
        }
    }
}