#include "game.h"
void Game::myDrawGame(){
    switch (currentScreen)
        {
            case 0:
            {
                // Draw title screen
                //std::cout<<"draw0:\n";   
                DrawText("PRESS ENTER", 450, 420, 40, BLACK);

            } break;
            case 1:
            {
                 // Draw gameplay screen
                DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                // myDrawLines();
                // myDrawPlayers()


                             
                for (int player_index=0; player_index < (int)player_number ; player_index++){
                    if(return_info[player_index].throwing){
                        double my_x = player_vector[player_index]->position.x + 0.5*player_vector[player_index]->player_rectangle.width;
                        double my_y = player_vector[player_index]->position.y + 0.5*player_vector[player_index]->player_rectangle.height;
                        DrawCircle(my_x, my_y, 200, RED);    
                    }
        
                    DrawTexture(player_vector[player_index]->player_image,player_vector[player_index]->position.x,player_vector[player_index]->position.y,WHITE); 
                }


                DrawRectangle(0, 750, 640, 130, Fade(BLACK, 0.8f));
                DrawRectangle(0, 880, 1280, 70, Fade(BLACK, 0.9f));
                DrawRectangle(640, 750, 1280, 130, BLACK);
                DrawText("Knowledge", 10, 760, 30, WHITE);  
                DrawText("GPA", 10, 800, 30, WHITE);  
                DrawText("Happiness", 10, 840, 30, WHITE); 
                DrawRectangle(170, 760, player_vector[my_index]->get_property().knowledge*9, 30, RED);
                DrawRectangle(170, 800, player_vector[my_index]->get_property().GPA*9, 30, BLUE);
                DrawRectangle(170, 840, player_vector[my_index]->get_property().happiness*9, 30, YELLOW);
                int num = 0;
                
                for(vector<int>::const_iterator citer = player_vector[0]->object_list.begin(); citer!=player_vector[0]->object_list.end();citer++)
                {
                    Texture2D text = LoadTextureFromImage(object_vector[*citer]->object_image);
                    DrawTexture(text, 20+50*num, 890 ,WHITE );
                    //cerr<<"      "<<player_vector[0]->object_in_hand<<" "<<(*citer)<<endl;
                    if((*citer)==player_vector[0]->object_in_hand)DrawRectangle(20+50*num, 890, 20, 20, BLUE);
                    num++;
                }

                // myDrawObjectsToPick();
                for (int obj_index=0; obj_index < (int)object_number ; obj_index++){
                    //std::cout<<object_vector[obj_index]->get_state()<<std::endl;
                    //std::cout<<NOT_APPEAR<<std::endl;
                    /*
                    if(object_vector[obj_index]->get_state() == NOT_APPEAR){
                        object_vector[obj_index]->update_state(UNPICKED);
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        // TODO
                        DrawRectangleV(obj_pos,obj_size, BLUE);
                        continue;
                    }*/
                    if (object_vector[obj_index]->get_state() == UNPICKED){
                        Vector2 obj_pos = {object_vector[obj_index]->size.x,object_vector[obj_index]->size.y};
                        Vector2 obj_size = {object_vector[obj_index]->size.width,object_vector[obj_index]->size.height};
                        //TODO
                        //DrawRectangleV(obj_pos, obj_size, BLUE);
                        Texture2D text = LoadTextureFromImage(object_vector[obj_index]->object_image);
                        DrawTexture(text, obj_pos.x, obj_pos.y,WHITE);
                        const char* obj_name = object_vector[obj_index]->name.data();
                        DrawText(obj_name, obj_pos.x, obj_pos.y+20, 20, BLACK);
                    }
                }

                // myDrawEventPlace();
                if(eventhappen){
                    const char* event_note = eventnote.data();
                    DrawText(event_note, 20, 725, 20, RED);
                }
                // myDrawInfo();
                int player_index = my_index;
                player_property one_player_property = player_vector[player_index]->get_property();

                const char* r = ("reputation:" + doublttoString(one_player_property.reputation)).data(); 
                DrawText(r, 980 + 200*player_index, 875, 20, WHITE);                                     
                const char* h = ("happiness:" + doublttoString(one_player_property.happiness)).data();
                DrawText(h, 980 + 200*player_index, 850, 20, WHITE);
                const char* k = ("knowledge:" + doublttoString(one_player_property.knowledge)).data();
                DrawText(k, 980 + 200*player_index, 825, 20, WHITE);
                const char* g = ("GPA:" + doublttoString(one_player_property.GPA)).data();  
                DrawText(g, 980 + 200*player_index, 800, 20, WHITE);

                int index_in_hand = player_vector[player_index]->object_in_hand;
                if(index_in_hand == -1){
                    const char* l = "Object in hand: None";
                    DrawText(l, 980 + 200*player_index, 900, 20, WHITE);
                }
                else{
                    int obj_index = player_vector[player_index]->object_list[index_in_hand];
                    PKU_object* temp_obj = object_vector[obj_index];
                    const char* l = ("Object in hand:" + temp_obj->name).data();
                    DrawText(l, 980 + 200*player_index, 900, 20, WHITE);
                }

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
string Game::doublttoString(double d){
    std::stringstream ss;
    ss << std::setprecision(4) << d;
    string str = ss.str();
    return str;
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
