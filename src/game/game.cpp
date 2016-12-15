#include "game.h"

Game::Game() :
        Game(new Labyrinth){
//<<<<<<< HEAD
    std::cout << "Game()" << std::endl;
//=======
    players.emplace_back(new Player);
    isGame = 1;
//>>>>>>> feature/game
}

Game::Game(Labyrinth *_l) :
    labyrinth(_l){
        isGame = 1;
}

void Game::init(){
}

bool Game::checkPlayerAction(const int &playerIndex, const PlayerEvent& playerEvent){
    if(players[playerIndex]->readyForNewCommand()){
        if(labyrinth->checkCommand(*players[playerIndex], playerEvent)){
            return true;
        }
    }
    return false;
}

//<<<<<<< HEAD
/*
void Game::applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent){
    players[playerIndex]->applyCommand(playerEvent);
}
*/
void Game::setPlayerPosition(const int& playerIndex, const int& x, const int& y){
    players[playerIndex]->setPosition(x, y);
}


void Game::_join(){
    players.emplace_back(new Player);
}
void Game::_move(const int& playerIndex, const std::string& str){
    std::cout << "_move: " << playerIndex << std::endl;
    PlayerEvent playerEvent(str);
    players[playerIndex]->applyCommand(playerEvent);
}
std::string Game::_state(){
    std::string state;
    int i(0);
    for (const auto& player: players){
        state.append( {"@"} );
        state.append( std::to_string(i) );
        state.append( {':'} );
        state.append( player->getPositionInString() );
        state.append( {'\n'} );
        ++i;
    }
    std::cout << state << std::endl;
    return state;
}
//=======
bool Game::applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent){//}int &playerIndex, Command &command){
    players[playerIndex]->applyCommand(playerEvent);
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
//>>>>>>> feature/game
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
