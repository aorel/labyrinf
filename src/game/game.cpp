#include "game.h"

Game::Game(){
        //Game(new Labyrinth){
    std::cout << "Game()" << std::endl;
    //gameBuilder();
    //labyrinth = labyrinthBuilder();
    //players.emplace_back(playerBuilder());
}
void Game::builder(){
    std::cout << "Game::builder()" << std::endl;
    labyrinth = labyrinthBuilder();
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
        state.append( std::to_string(i) );
        state.append( {':'} );
        state.append( player->getPositionInString() );
        state.append( {'\n'} );
        ++i;
    }
    std::cout << state << std::endl;
    return state;
}

std::unique_ptr<Labyrinth> Game::labyrinthBuilder(){
    std::cout << "new Labyrinth" << std::endl;
    return std::unique_ptr<Labyrinth>(new Labyrinth);
}
std::unique_ptr<Player> Game::playerBuilder(){
    std::cout << "new Player" << std::endl;
    return std::unique_ptr<Player>(new Player);
}
