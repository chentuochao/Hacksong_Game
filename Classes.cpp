#include "game.h"
#include <iostream>
#include <memory.h>

using namespace std;
#define default_range 20

/*-----------------------------------   the functions for class "Player" --------------------------------*/
// initialize the player class
Player::Player(unsigned int index0,string name0,  Vector2 speed0, Image player_image0, Rectangle player_rectangle0, Color player_color0)
{
    name = name0;
    index = index0;
    speed = speed0;
    player_image = player_image0;
    player_rectangle = player_rectangle0;
    player_color = player_color0;
    object_list.clear();

    walk_state = MIDDLE;
    activity_state = STAND;

    attack_range = default_range;
    property.knowledge = 50;
    property.happiness = 50;
    property.GPA = 4.0;
    property.reputation = 50;

}

// delete the Player CLASS
Player::~Player()
{

}

Player_activity_state Player::get_activity_state(){
    return activity_state;
}

void Player::update_activity_state(Player_activity_state new_state){
    activity_state = new_state;
}

void Player::update_speed(Vector2 new_speed){
    speed = new_speed;
} // update the walking speed

Vector2 Player::get_speed(){
    return speed;
}// get the walking speed

void Player::update_knowledge(double new_knowledge){
    property.knowledge = new_knowledge;
} // update the knowledge

void Player::update_happiness(double new_happiness){
    property.happiness = new_happiness;
} // update the happiness

void Player::update_GPA(double new_GPA){
    property.GPA = new_GPA;
} // update the GPA

void Player::update_reputation(double new_reputation)
{
    property.reputation = new_reputation;
} // update the _reputation

Player_property Player::get_property(){
    return property;
} // get the direction



/*---------------------------------   the functions for class "PKU_object" --------------------------------*/
PKU_object::PKU_object(string name0, unsigned int index0, Vector2 position0, Image object_image0, Rectangle size0, Self_effect effect_to_self0, Interaction_effect effect_to_other0){
    name = name0;
    index = index0;
    position = position0;
    object_image = object_image0;
    size = size0;
    effect_to_self = effect_to_self0;
    effect_to_other = effect_to_other0;
}

PKU_object::~PKU_object()
{

}

void PKU_object::update_state(Object_state new_state){
    state = new_state;
}
Object_state PKU_object::get_state(){
    return state;
}

Self_effect PKU_object::get_self_effect(){
    return effect_to_self;
}
Interaction_effect PKU_object::get_interaction_effect(){
    return effect_to_other;
}

void PKU_object::draw_object(){

}


/*---------------------------------------   the functions for class "PKU_event" ---------------------------*/
PKU_event::PKU_event(string name0, unsigned int index0, string information0, Event_place place0, unsigned int max_human0, unsigned int min_human0, Event_property_requirement requirement0, unsigned int start_time0, unsigned int time_span0, Event_property_effect property_effect0)
{   
    name = name0;
    if_begin = false;
    index = index0;
    information = information0;
    place = place0;
    max_human = max_human0;
    min_human = min_human0;
    wait_human_num = 0;

    requirement = requirement0;
    start_time = start_time0;
    time_span = time_span0;
    property_effect = property_effect0;  

    memset(attend_players, 0, MAX_PLAYER * sizeof(bool));
}

PKU_event::~PKU_event()
{
    
}

void PKU_event::begin_competition(){

    // reset human number
    wait_human_num = 0;
    memset(attend_players, 0, MAX_PLAYER * sizeof(bool));
}

bool PKU_event::check_event_begin(double current_time) // check if in every frame
{
    if(current_time >= start_time && current_time <= start_time + time_span && if_begin == false)  if_begin = true;
    else if((current_time > start_time + time_span || max_human <= 0) && if_begin == true){
        if(wait_human_num < min_human) begin_competition(); 
    }
}

bool PKU_event::player_want_to_join(Player p){
    if(max_human <= 0 ||if_begin == false){  // the event has been already full of people
        return 0;
    }
    else{
        Player_property p_property = p.get_property();
        if(p_property.knowledge < requirement.knowledge_require || p_property.happiness < requirement.happiness_require || p_property.GPA < requirement.GPA_require || p_property.reputation < requirement.reputation_require){
            return 0;
        }
        else{
            max_human --;
            wait_human_num ++;
            attend_players[p.index] = true;
            if(wait_human_num >= min_human) begin_competition();
            return 1;
        }
    }
}


void PKU_event::draw_event(){

}