#include "game.h"
#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;


void Game::init_player_list(){
    // initialize one player
    for(int i = 0; i < MAX_PLAYER; ++i)
    {
        Image image = LoadImage("icons/man-student.png");  
        ImageResize(&image, 30, 30);
        Texture2D Text = LoadTextureFromImage(image);
        Rectangle shape = { 0, 0, 50, 50 }; // lefttop-x, lefttop-y, width, height
        //----------------------------index,   name,   speed,  image, shape, color --------------
        Vector2 speed = {0, 0};
        string name = "name" + to_string(i);
        player_vector[i] = new Player( i,  name,  speed,   Text, shape, YELLOW);

        if(i + 1 >= player_number ) break;
    }
}


void Game::init_object_list(){
    // initialize one object
    Image image = LoadImage("object.png"); 
    Rectangle range = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self = {2, -2}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction = {+2, -1, -2, +1, -2, 0}; //my_knowledge_change, my_happiness_change, my_reputation_change, others_knowledge_change, others_happiness_change, others_reputation_change
    object_vector[ object_number] = new PKU_object("MATH", 0, image, range, my_self, my_interaction);
    
    object_number ++;
    Image image0 = LoadImage("object0.png"); 
    Rectangle range0 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self0 = {2, -2}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction0 = {+2, -1, -2, +1, -2, 0}; 
    object_vector[object_number] = new PKU_object("ENGLISH", 0, image0, range0, my_self0, my_interaction0);
    object_number ++;

    Image image1 = LoadImage("object1.png"); 
    Rectangle range1 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self1 = {2, -2}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction1 = {+2, -1, -2, +1, -2, 0}; 
    object_vector[object_number] = new PKU_object("CHINESE", 0, image1, range1, my_self1, my_interaction1);
    object_number ++;

    Image image2 = LoadImage("object2.png"); 
    Rectangle range2 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self2 = {2, 1}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction2 = {1, 1, 0, 1, 2, 0}; 
    object_vector[object_number] = new PKU_object("dizhengailun", 0, image2, range2, my_self2, my_interaction2);
    object_number ++;

    Image image3 = LoadImage("object3.png"); 
    Rectangle range3 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self3 = {-1, 3}; //knowledge_change_rate, happiness_change_rate
    Interaction_effect my_interaction3 = {-1, 3, 0, -2, 2, 0}; 
    object_vector[object_number] = new PKU_object("PVP", 0, image3, range3, my_self3, my_interaction3);
    object_number ++;

    Image image4 = LoadImage("object4.png"); 
    Rectangle range4 = { 0, 0, 20, 20 }; // lefttop-x, lefttop-y, width, height
    Self_effect my_self4 = {-1, 2}; //knowledge_change_rate, happiness_change_rate
    // TODO happiness for love should be ramdom
    //srand(seed);
    Interaction_effect my_interaction4 = {-1,  (rand() % 20) - 10, 0, +1, (rand() % 20) - 10, 0}; 
    object_vector[object_number] = new PKU_object("LOVE", 0, image4, range4, my_self4, my_interaction4);
    object_number ++;
}

void Game::init_event_list(){

    // initialize one even
    string information = "Midterm exam is beginning in the Teaching Building\n. Every student should take part in the exam,\n otherwise your GPA will become 0!\n";
    Event_property_requirement requirement = {10, 10, 0, 10};
    int start_time = 90;
    int time_span = 20;
    Event_property_effect property_effect = {+5, -5, 0, 0};
    event_vector[event_number] = new PKU_event("Mid Exam", 0, information, TEACHING_BUILDING, player_number, player_number, requirement, start_time, time_span, property_effect);
    event_number ++;

    string information0 = "PArticipating in the sports meeting will make you happy\nBut it will intefere with your GPA\n";
    Event_property_requirement requirement0 = {10, 10, 0, 10};
    int start_time0 = 30;
    int time_span0 = 20;
    Event_property_effect property_effect0 = {+5, -5, 0, 0};
    event_vector[event_number] = new PKU_event("Sports Meeting", 0, information0, TEACHING_BUILDING, player_number, player_number, requirement0, start_time0, time_span0, property_effect0);
    event_number ++;  

    string information1 = "It will give you long-term benefit.\nIt will also take some time from you.";
    Event_property_requirement requirement1 = {10, 10, 0, 10};
    int start_time1 = 60;
    int time_span1 = 20;
    Event_property_effect property_effect1 = {+5, -5, 0, 0};
    event_vector[event_number] = new PKU_event("Student Work", 0, information1, TEACHING_BUILDING, player_number, player_number, requirement1, start_time1, time_span1, property_effect1);
    event_number ++;  

    string information2 = "You can get friends and colorful college life.\n";
    Event_property_requirement requirement2 = {10, 10, 0, 10};
    int start_time2 = 120;
    int time_span2 = 20;
    Event_property_effect property_effect2 = {+5, -5, 0, 0};
    event_vector[event_number] = new PKU_event("Club Activity", 0, information2, TEACHING_BUILDING, player_number, player_number, requirement2, start_time2, time_span2, property_effect2);
    event_number ++;

    string information3 = "Final exam is comming!";
    Event_property_requirement requirement3 = {10, 10, 0, 10};
    int start_time3 = 150;
    int time_span3 = 20;
    Event_property_effect property_effect3 = {+5, -5, 0, 0};
    event_vector[event_number] = new PKU_event("final exam", 0, information3, TEACHING_BUILDING, player_number, player_number, requirement3, start_time3, time_span3, property_effect3);
    event_number ++;
}
