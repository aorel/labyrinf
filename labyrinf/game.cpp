#include "game.h"

/*
Game::Game(CommandFunction vCC){
        //verifyCommandCallback(vCC){
}

void Game::checkCommand(Command command){
    if(currentPlayer.readyForNewCommand()){
        if(labyrinth.checkCommand(currentPlayer, command)){
        
            verifyCommandCallback(command);
            //if(serverVerify(player, command))...
            currentPlayer.commandApply(command);
        }
    }
}
*/

bool Game::checkCommand(Command command){
    if(currentPlayer.readyForNewCommand()){
        if(labyrinth.checkCommand(currentPlayer, command)){
            std::cout << "true" << std::endl;
            return true;

            //verifyCommandCallback(command);
            //if(serverVerify(player, command))...
            //currentPlayer.commandApply(command);
        }
    }
    return false;
}

void Game::applyCommand(Command command){
    std::cout << "applyCommand" << std::endl;
    currentPlayer.applyCommand(command);
}
