#include "game.h"
void Game::myDrawGame(){
    switch (currentScreen)
        {
            case 1:
            {
                // myDrawLines();
                // myDrawPlayers()
                
                for (int player_index=0; player_index < (int)player_number ; player_index++)
                {
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

                for (int object_index=0; object_index < (int)object_number ; object_index++){
                    DrawTexture(object_vector[object_index]->object_image,object_vector[object_index]->size.x,object_vector[object_index]->size.y,WHITE);                                
                    //cerr<<player_vector[player_index]->position.x<<" "<<player_vector[player_index]->position.y;
                    DrawTexture(object_vector[object_index]->object_image, 20+40*object_index, 890 ,WHITE );
                }

                // myDrawEventPlace();
                // myDrawInfo();
                DrawRectangle(170, 760, player_vector[0]->get_property().knowledge*9, 30, RED);
                DrawRectangle(170, 800, player_vector[0]->get_property().GPA*9, 30, BLUE);
                DrawRectangle(170, 840, player_vector[0]->get_property().happiness*9, 30, YELLOW);
            } break;
            case 2:
            {
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