#include "game.h"
#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;


void Game::init_player_list(){
    // initialize one player
    Image image = LoadImage("icons/man-student.png");  
    ImageResize(&image, 30, 30);
    Texture2D Text = LoadTextureFromImage(image);
    Rectangle shape = { 0, 0, 50, 50 }; // lefttop-x, lefttop-y, width, height
    //----------------------------index,   name,   speed,  image, shape, color --------------
    Vector2 speed = {0, 0};
    player_vector[0] = new Player( 0,  "name0",  speed,   Text, shape, YELLOW);
    player_number ++;

    // initialize one player
    Image image1 = LoadImage("icons/man-student.png");  
    ImageResize(&image1, 30, 30);
    Texture2D Text1 = LoadTextureFromImage(image);
    shape = { 0, 0, 50, 50 }; // lefttop-x, lefttop-y, width, height
    //----------------------------index,   name,   speed,  image, shape, color -------------------
    player_vector[1] = new Player( 1, "name1",  speed,   Text1, shape, RED);
    player_number ++;

}


void Game::init_object_list(){
    // initialize one object
    Image image = LoadImage("object0.png"); 
    Rectangle range = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self = {1, 1}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction = {-5, +10, -5, +1, -20, 0}; //my_knowledge_change, my_happiness_change, my_reputation_change, others_knowledge_change, others_happiness_change, others_reputation_change
    object_vector[0] = new PKU_object("gaoshu", 0, image, range, my_self, my_interaction);
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
