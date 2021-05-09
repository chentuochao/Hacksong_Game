#include "game.h"
void Game::myDrawGame(){
    switch (currentScreen)
        {
            case 0:
            {
                // Draw title screen
                DrawText("PRESS ENTER", 450, 420, 40, BLACK);

            } break;
            case 1:
            {
                 // Draw gameplay screen
                DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                // myDrawLines();
                // myDrawPlayers()
                Image p = LoadImage("icons/man-student.png");
                ImageResize(&p,30,30);
                Texture2D P = LoadTextureFromImage(p);
                DrawTexture(P,500,300,WHITE);
                // myDrawObjectsToPick();
                // myDrawEventPlace();
                // myDrawInfo();
            } break;
            case 2:
            {
                // Draw ending screen
                    
                // Draw a transparent black rectangle that covers all screen
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.4f));
                    
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                // myDrawGameEnd();
            } break;
            default: break;
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