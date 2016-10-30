#include "game.h"


Game::Game(CommandFunction vCC) :
        verifyCommandCallback(vCC){
}





/*
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
            return true;

            //verifyCommandCallback(command);
            //if(serverVerify(player, command))...
            //currentPlayer.commandApply(command);
        }
    }
    return false;
}

void Game::verifyCommand(Command command){
    if(checkCommand(command)){
        //verifyCommandCallback(command);//TODO
    }
}
