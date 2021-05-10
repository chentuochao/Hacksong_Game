#include "game.h"
void Game::myDrawGame(){
    switch (currentScreen)
        {
            case 1:
            {
                 // Draw gameplay screen
                // myDrawLines();
                // myDrawPlayers()
                             
               for (int player_index=0; player_index < (int)player_number ; player_index++)
                {
                    //
                    //cerr<<"          "<<player_vector[player_index]->position.x<<" "<<player_vector[player_index]->position.y<<endl;
                    int STA=player_vector[player_index]->sta;
                    if(player_vector[player_index]->get_speed().x>0.1)
                    {
                        DrawTexture(player_vector[player_index]->player_image[3+(STA<=9)],
                        player_vector[player_index]->position.x,player_vector[player_index]->position.y,WHITE);
                        
                    }
                    else if(player_vector[player_index]->get_speed().x<-0.1)
                    {
                        DrawTexture(player_vector[player_index]->player_image[1+(STA>9)],
                        player_vector[player_index]->position.x,player_vector[player_index]->position.y,WHITE);
                    }
                    else
                    {
                        DrawTexture(player_vector[player_index]->player_image[0],
                        player_vector[player_index]->position.x,player_vector[player_index]->position.y,WHITE);
                    }
                     player_vector[player_index]->sta=(player_vector[player_index]->sta+1)%20;                               
                    //cerr<<player_vector[player_index]->position.x<<" "<<player_vector[player_index]->position.y;
                }
                // myDrawObjectsToPick();
                int num = 0;
                for(vector<unsigned int>::const_iterator citer=player_vector[0]->object_list.begin();citer!=player_vector[0]->object_list.end();citer++)
                {
                    DrawTexture(object_vector[*citer]->object_image, 20+50*num, 890 ,WHITE );
                    cerr<<"      "<<player_vector[0]->object_in_hand<<" "<<(*citer)<<endl;
                    if((*citer)==player_vector[0]->object_in_hand)DrawRectangle(20+50*num, 890, 20, 20, BLUE);
                    num++;
                }
                for (int obj_index=0; obj_index < (int)object_number ; obj_index++){
                    if(object_vector[obj_index]->get_state() == NOT_APPEAR){
                        object_vector[obj_index]->update_state(UNPICKED);
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        // TODO
                        //DrawRectangleV(obj_pos,obj_size, BLUE);
                        DrawTexture(object_vector[obj_index]->object_image, obj_pos.x, obj_pos.y,WHITE);
                        continue;
                    }
                    if (object_vector[obj_index]->get_state() == UNPICKED){
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        //TODO
                        //DrawRectangleV(obj_pos,obj_size, BLUE);
                        DrawTexture(object_vector[obj_index]->object_image, obj_pos.x, obj_pos.y,WHITE);
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
                
                DrawRectangle(170, 760, player_vector[0]->get_property().knowledge*9, 30, RED);
                DrawRectangle(170, 800, player_vector[0]->get_property().GPA*9, 30, BLUE);
                DrawRectangle(170, 840, player_vector[0]->get_property().happiness*9, 30, YELLOW);
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