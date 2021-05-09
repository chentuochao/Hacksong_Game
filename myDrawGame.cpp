#include "myDrawGame.h"

void Game::myDrawGame(){
    if (!game_over){
        myDrawBackground();
        myDrawLines();
        myDrawPlayers();
        myDrawObjectsToPick();
        myDrawEventPlace();
        myDrawInfo();
    }
    else{
        myDrawGameEnd();
    }
}

void Game::myDrawBackground(){

}

void Game::myDrawLines(){

}

void Game::myDrawPlayers(){

}

void Game::myDrawObjectsToPick(){

}

void Game::myDrawEventPlace(){

}

void Game::myDrawInfo(){
    
}