#include "game.h"

Game::Game() :
        Game(new Labyrinth){
    std::cout << "Game()" << std::endl;
    //players.emplace_back(new Player);
    isGame = 1;
}

Game::Game(Labyrinth *_l) :
    labyrinth(_l){
        isGame = 1;
}

void Game::addLocalPlayer(){
}

void Game::addPlayer(const int& playerIndex){
    if(players.find(playerIndex) == players.end()){
        players[playerIndex] = std::unique_ptr<Player>(new Player);
    }
    else{
        std::cout << "Game::addPlayer(): ERROR" << std::endl;
    }
}

void Game::delPlayer(const int& playerIndex){
    players.erase(playerIndex);
}

bool Game::checkPlayerAction(const PlayerEvent& playerEvent){
    return checkPlayerAction(localPlayer, playerEvent);
}

bool Game::checkPlayerAction(const int &playerIndex, const PlayerEvent& playerEvent){
    if(players[playerIndex]->readyForNewCommand()){
        if(labyrinth->checkCommand(*players[playerIndex], playerEvent)){
            return true;
        }
    }
    return false;
}

void Game::applyPlayerAction(const PlayerEvent& playerEvent){
    applyPlayerAction(localPlayer, playerEvent);
}

void Game::applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent){
    players[playerIndex]->applyCommand(playerEvent);
    afterPlayerAction(playerIndex);
}

void Game::setPlayerPosition(const int& playerIndex, const int& x, const int& y){
    players[playerIndex]->setPosition(x, y);
    afterPlayerAction(playerIndex);
}

void Game::afterPlayerAction(const int& playerIndex){
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
        if (player.second->getHealth() > 0){
            isGame = 1;
        }
    }
}

void Game::debugPrint(){
    std::cout << "debugPrint:"<< std::endl;
    for(const auto &player : players){
        std::cout << " " << player.first << std::endl;
    }
}

std::string Game::_info(){
    std::string msg = settings::gameMsgInfo + settings::gameMsgSep;
    for(const auto &player : players){
        msg +=
        //std::cout << " " << player.first << std::endl;
                std::to_string(player.first) + settings::gameMsgSep
                + player.second->positionToString() + settings::gameMsgSep;

    }
    return msg;
}

int Game::_joinKey(){
    return playersCounter;
}

std::string Game::_join(){
    addPlayer(playersCounter);

    std::string msg = settings::gameMsgJoin + settings::gameMsgSep
        + std::to_string(playersCounter) + settings::gameMsgSep
        + players[playersCounter]->positionToString() + settings::gameMsgSep;

    ++playersCounter;
    return msg;
}

std::string Game::_add(){
    std::string msg = settings::gameMsgAdd + settings::gameMsgSep
        + std::to_string(playersCounter-1) + settings::gameMsgSep
        + players[playersCounter-1]->positionToString() + settings::gameMsgSep;
    return msg;
}

std::string Game::_del(const int& playerIndex){

    std::string msg = settings::gameMsgDel + settings::gameMsgSep
        + std::to_string(playerIndex) + settings::gameMsgSep;
    players.erase(playerIndex);
    return msg;
}

std::string Game::_move(const int& playerIndex, const std::string& str){
    std::cout << "_move: " << playerIndex << " " << str << std::endl;
    PlayerEvent playerEvent(str);
    players[playerIndex]->applyCommand(playerEvent);

    std::string msg = settings::gameMsgMove + settings::gameMsgSep
            + std::to_string(playerIndex) + settings::gameMsgSep
            + players[playerIndex]->positionToString() + settings::gameMsgSep;
    return msg;
}

std::string Game::_state(){
    std::string state;
    int i(0);
    for (const auto& player: players){
        state.append( {"@"} );
        state.append( std::to_string(i) );
        state.append( {':'} );
        state.append( player.second->positionToString() );
        state.append( {'\n'} );
        ++i;
    }
    std::cout << state << std::endl;
    return state;
}

void Game::_handler(const std::string& msg){
    size_t startPos, endPos;
    int playerIndex, x, y;
    if(msg.substr(0, settings::gameMsgInfo.size()) == settings::gameMsgInfo) {
        std::cout << "Game::_handler: settings::gameMsgInfo" << std::endl;

        startPos = msg.find_first_of(settings::gameMsgSep) + 1;
        while(_parser(msg, startPos, endPos, playerIndex, x, y)){
            addPlayer(playerIndex);
            setPlayerPosition(playerIndex, x, y);
        }
    }
    else if(msg.substr(0, settings::gameMsgJoin.size()) == settings::gameMsgJoin){
        std::cout << "Game::_handler: settings::gameMsgJoin" << std::endl;

        startPos = msg.find_first_of(settings::gameMsgSep) + 1;
        if(_parser(msg, startPos, endPos, localPlayer, x, y)){
            addLocalPlayer();
            setPlayerPosition(localPlayer, x, y);
        }
        debugPrint();
    }
    else if(msg.substr(0, settings::gameMsgAdd.size()) == settings::gameMsgAdd){
        std::cout << "Game::_handler: settings::gameMsgAdd" << std::endl;

        startPos = msg.find_first_of(settings::gameMsgSep) + 1;
        if(_parser(msg, startPos, endPos, playerIndex, x, y)){
            addPlayer(playerIndex);
            setPlayerPosition(playerIndex, x, y);
        }
        debugPrint();
    }
    else if(msg.substr(0, settings::gameMsgDel.size()) == settings::gameMsgDel){
        std::cout << "Game::_handler: settings::gameMsgDel" << std::endl;

        startPos = msg.find_first_of(settings::gameMsgSep) + 1;
        if(_parser(msg, startPos, endPos, playerIndex)){
            delPlayer(playerIndex);
        }
        debugPrint();
    }
    else if(msg.substr(0, settings::gameMsgMove.size()) == settings::gameMsgMove){
        std::cout << "Game::_handler: settings::gameMsgMove" << std::endl;

        startPos = msg.find_first_of(settings::gameMsgSep) + 1;
        if(_parser(msg, startPos, endPos, playerIndex, x, y)){
            setPlayerPosition(playerIndex, x, y);
        }
    }
    else{
        std::cout << "Game::_handler: unknown msg" << std::endl;
    }
}

bool Game::_parser(const std::string& msg, size_t& startPos, size_t& endPos, int& key){
    std::cout << "Game::_parser(): ";

    endPos = msg.find_first_of(settings::gameMsgSep, startPos);
    if(endPos == std::string::npos) return false;
    std::cout << "key: " << msg.substr(startPos, endPos-startPos) << " ";
    key = std::stoi(msg.substr(startPos, endPos-startPos));

    return true;
}

bool Game::_parser(const std::string& msg, size_t& startPos, size_t& endPos, int& key, int& x, int& y){
    std::cout << "Game::_parser(): ";

    endPos = msg.find_first_of(settings::gameMsgSep, startPos);
    if(endPos == std::string::npos) return false;
    std::cout << "key: " << msg.substr(startPos, endPos-startPos) << " ";
    key = std::stoi(msg.substr(startPos, endPos-startPos));

    startPos = endPos + 1;
    endPos = msg.find_first_of(',', startPos);
    if(endPos == std::string::npos) return false;
    std::cout << "x: " << msg.substr(startPos, endPos-startPos) << " ";
    x = std::stoi(msg.substr(startPos, endPos-startPos));

    startPos = endPos + 1;
    endPos = msg.find_first_of(settings::gameMsgSep, startPos);
    if(endPos == std::string::npos) return false;
    std::cout << "y: " << msg.substr(startPos, endPos-startPos) << std::endl;
    y = std::stoi(msg.substr(startPos, endPos-startPos));

    return true;
}
