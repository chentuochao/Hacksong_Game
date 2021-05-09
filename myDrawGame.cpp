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
                             
                for (int player_index=0; player_index < (int)player_number ; player_index++){
                    DrawTexture(player_vector[player_index]->player_image,player_vector[player_index]->position.x,player_vector[player_index]->position.y,WHITE);                               
                }
                // myDrawObjectsToPick();
                for (int obj_index=0; obj_index < (int)object_number ; obj_index++){
                    if(object_vector[obj_index]->get_state() == NOT_APPEAR){
                        object_vector[obj_index]->update_state(UNPICKED);
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        // TODO
                        DrawRectangleV(obj_pos,obj_size, BLUE);
                        continue;
                    }
                    if (object_vector[obj_index]->get_state() == UNPICKED){
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        //TODO
                        DrawRectangleV(obj_pos,obj_size, BLUE);
                        const char* obj_name = object_vector[obj_index]->name.data();
                        DrawText(obj_name, obj_pos.x, obj_pos.y+20, 20, BLACK);
                    }
                }

                // myDrawEventPlace();
                if(eventhappen){
                    const char* event_note = eventnote.data();
                    DrawText(event_note, 20, 725, 20, BLACK);
                }
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