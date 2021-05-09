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
                
                DrawTexture(P,player_vector[0]->position.x,player_vector[0]->position.y,WHITE);
                // myDrawObjectsToPick();
                for (int obj_index=0; obj_index < (int)object_number ; obj_index++){
                    if(object_vector[obj_index]->get_state() == UNPICKED){
                        object_vector[obj_index]->update_state(UNPICKED);
                        //TODO
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        DrawRectangleV(obj_pos,obj_size, BLUE);
                    }
                }

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