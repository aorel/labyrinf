#include "game.h"

Game::Game() :
        Game(new Labyrinth){
    std::cout << "Game()" << std::endl;
    players.emplace_back(new Player);
    isGame = 1;
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

void Game::applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent){
    players[playerIndex]->applyCommand(playerEvent);
    sf::Vector2i position = players[playerIndex]->getPosition();
    CellType place = labyrinth->getBonus(position);
    if (place == FIRE){
        players[playerIndex]->addHealth(-1);
        std::cout << " fire " << players[playerIndex]->getHealth() << std::endl;
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
        //return true;
    }
    //return false;
    isGameTest();
}

void Game::isGameTest(){
    isGame = 0;
    for (const auto &player : players){
        if (player->getHealth() > 0){
            isGame = 1;
        }
    }
}

void Game::setPlayerPosition(const int& playerIndex, const int& x, const int& y){
    players[playerIndex]->setPosition(x, y);
}

std::string Game::_info(){
    std::string msg = _infoMsg;// + labyr.toString();
    return msg;
}
std::string Game::_join(){
    players.emplace_back(new Player);


    //int playerKey(testPlayersCounter);
    testPlayers[testPlayersCounter] = std::unique_ptr<Player>(new Player);


    std::string msg = _joinMsg + "|";

    auto search = testPlayers.find(testPlayersCounter);
    if(search != testPlayers.end()) {
        msg +=  std::to_string(testPlayersCounter) + "|" +
                search->second->positionToString();
    }


    ++testPlayersCounter;
    return msg;
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
        state.append( player->positionToString() );
        state.append( {'\n'} );
        ++i;
    }
    std::cout << state << std::endl;
    return state;
}
void Game::_handler(const std::string& msg){
    if(msg.substr(0, _infoMsg.size()) == _infoMsg) {
        std::cout << "Game::_handler: _infoMsg" << std::endl;
    }
    else if(msg.substr(0, _joinMsg.size()) == _joinMsg){
        std::cout << "Game::_handler: _joinMsg" << std::endl;
        //size_t start(msg.find_first_of('@'));
    }
    else{
        std::cout << "Game::_handler: unknown msg" << std::endl;
    }
}
