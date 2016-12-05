#include "game.h"

Game::Game() :
        Game(new Labyrinth){
    std::cout << "Game()" << std::endl;
}

Game::Game(Labyrinth *_l) :
    labyrinth(_l){
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

void Game::applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent){
    players[playerIndex]->applyCommand(playerEvent);
}

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
