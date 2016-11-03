#include "serverGame.h"

ServerGame::ServerGame() :
    ServerGame(new Labyrinth(), new Player()){
        //l( new Labyrinth() ),
        //p( new Player() ){
}
ServerGame::ServerGame(Labyrinth *_l, Player *_p) :
    l(_l),
    p(_p){

}

//TODO command заменить на полное поисание действия: объект, действие
bool ServerGame::checkPlayerAction(int &playerIndex, Command &command){
    if(players[playerIndex].readyForNewCommand()){
        if(labyrinth.checkCommand(players[playerIndex], command)){

            return true;
        }
    }
    return false;
}

void ServerGame::applyPlayerAction(int &playerIndex, Command &command){
    players[playerIndex].applyCommand(command);
}
