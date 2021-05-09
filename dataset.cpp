#include "game.h"
#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;


void Game::init_player_list(){
    // initialize one player
    Image image0 = LoadImage("icons/player0.png");ImageResize(&image0, 40, 50);
    Image image1 = LoadImage("icons/player1.png");ImageResize(&image1, 40, 50);
    Image image2 = LoadImage("icons/player2.png");ImageResize(&image2, 40, 50);
    Image image3 = LoadImage("icons/player3.png");ImageResize(&image3, 40, 50);
    Image image4 = LoadImage("icons/player4.png");ImageResize(&image4, 40, 50);

    vector<Texture2D> Text = {LoadTextureFromImage(image0), LoadTextureFromImage(image1), 
    LoadTextureFromImage(image2), LoadTextureFromImage(image3), LoadTextureFromImage(image4) };
    Rectangle shape = { 0, 0, 50, 50 }; // lefttop-x, lefttop-y, width, height
    //----------------------------index,   name,   speed,  image, shape, color --------------
    Vector2 speed = {0, 0};
    player_vector[0] = new Player( 0,  "name0",  speed,   Text, shape, YELLOW);
    player_number = 1;

    // initialize one player
    shape = { 0, 0, 50, 50 }; // lefttop-x, lefttop-y, width, height
    //----------------------------index,   name,   speed,  image, shape, color -------------------
    player_vector[1] = new Player( 1, "name1",  speed,   Text, shape, RED);
    player_number ++;

}


void Game::init_object_list(){
    // initialize one object

    Image image = LoadImage("icons/MATH.png"); 
    ImageResize(&image, 50, 50);
    Texture2D Text = LoadTextureFromImage(image);
    Rectangle range = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self = {3, -3}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction = {+2, -1, -2, +1, -2, 0}; //my_knowledge_change, my_happiness_change, my_reputation_change, others_knowledge_change, others_happiness_change, others_reputation_change
    object_vector[ object_number] = new PKU_object("MATH", 0, Text, range, my_self, my_interaction);
    
    object_number ++;
    Image image0 = LoadImage("icons/ENGLISH.png"); 
    ImageResize(&image0, 50, 50);
    Text = LoadTextureFromImage(image0);
    Rectangle range0 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self0 = {3, -3}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction0 = {+2, -1, -2, +1, -2, 0}; 
    object_vector[object_number] = new PKU_object("ENGLISH", 0, Text, range0, my_self0, my_interaction0);
    object_number ++;

    Image image1 = LoadImage("icons/CHINESE.png"); 
    ImageResize(&image1, 50, 50);
    Text = LoadTextureFromImage(image1);
    Rectangle range1 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self1 = {3, -3}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction1 = {+2, -1, -2, +1, -2, 0}; 
    object_vector[object_number] = new PKU_object("CHINESE", 0, Text, range1, my_self1, my_interaction1);
    object_number ++;

    Image image2 = LoadImage("icons/dizhengailun.png"); 
    ImageResize(&image2, 50, 50);
    Text = LoadTextureFromImage(image2);
    Rectangle range2 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self2 = {2, 1}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction2 = {1, 1, 0, 1, 2, 0}; 
    object_vector[object_number] = new PKU_object("dizhengailun", 0, Text, range2, my_self2, my_interaction2);
    object_number ++;

    Image image3 = LoadImage("icons/PVP"); 
    ImageResize(&image3, 50, 50);
    Text = LoadTextureFromImage(image3);
    Rectangle range3 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self3 = {-2, 3}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction3 = {-1, 3, 0, -2, 2, 0}; 
    object_vector[object_number] = new PKU_object("PVP", 0, Text, range3, my_self3, my_interaction3);
    object_number ++;

    Image image4 = LoadImage("icons/LOVE.png"); 
    ImageResize(&image4, 50, 50);
    Text = LoadTextureFromImage(image4);
    Rectangle range4 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self4 = {-1, 3}; //knowledge_change_rate, happiness_change_rate
    // TODO happiness for love should be ramdom
    Interaction_effect my_interaction4 = {-1, GetRandomValue(-10,10), 0, +1, GetRandomValue(-10,10), 0}; 
    object_vector[object_number] = new PKU_object("LOVE", 0, Text, range4, my_self4, my_interaction4);
    object_number ++;
}

void Game::init_event_list(){

    // initialize one event
    string information = "Midterm exam is beginning in the Teaching Building. Every student should take part in the exam, otherwise your GPA will become 0!";
    Event_property_requirement requirement = {10, 10, 0, 10};
    unsigned int start_time = 30;
    unsigned int time_span = 10;
    Event_property_effect property_effect = {+5, -5, 0, 0};
    event_vector[0] = new PKU_event("mid exam", 0, information, TEACHING_BUILDING, player_number, player_number, requirement, start_time, time_span, property_effect);
    event_number ++;
}
