#include "Classes.h"
#include <iostream>

using namespace std;
#define default_range 20

/*-----------------------------------   the functions for class "Player" --------------------------------*/
// initialize the player class
Player::Player(string name0, unsigned int index0, float speed0, Image player_image0, Rectangle player_rectangle0, Color player_color0)
{
    name = name0;
    index = index0;
    speed = speed0;
    player_image = player_image0;
    player_rectangle = player_rectangle0;
    player_color = player_color0;
    object_list.clear();
    object_in_hand = -1;

    walk_state = Player::MIDDLE;
    activity_state = Player::STAND;

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
    return property;
}

void Player::update_activity_state(Player_activity_state new_state){
    activity_state = new_state;
}

void Player::update_speed(float new_speed){
    speed = new_speed;
} // update the walking speed

float Player::get_speed(){
    return speed;
}// get the walking speed

void Player::update_knowledge(unsigned float new_knowledge){
    property.knowledge += new_knowledge;
} // update the knowledge

void Player::update_happiness(unsigned float new_happiness){
    property.happiness += new_happiness;
} // update the happiness

void Player::update_GPA(unsigned float new_GPA){
    property.GPA = new_GPA;
} // update the GPA

void Player::update_reputation(unsigned float new_reputation)
{
    property.reputation += new_reputation;
} // update the _reputation

Player_property Player::get_property(){
    return property;
} // get the direction


bool Player::pick_object(unsigned int object_index){
    if(object_list.capacity() <= 0) return false;
    else if(object_list.empty()){
        object_list.push_back(object_index); 
        object_in_hand = 0;
        return true;
    }
    else{
        object_list.push_back(object_index); 
        return true;
    }
} // pick the objects

void Player::change_object(){
    if(object_list.empty()) object_in_hand = -1; // there is no object currently
    else if(object_in_hand >= object_list.size() - 1) object_in_hand = 0;
    else object_in_hand++;
} // change object

void Player::update_object_effect(){
    if(object_in_hand == -1) return;
    unsigned int hold_index = object_list.at(object_in_hand);
    PKU_object hold_object = object_vector[hold_index];

    update_knowledge(temp_object.effect_to_self.knowledge_change_rate/FPS);
    update_happiness(temp_object.effect_to_self.happiness_change_rate/FPS);
    //update_reputation(temp_object.effect_to_self.my_reputation_change);
}

void Player::throw_object(unsigned int other_index){
    if(object_in_hand == -1) return;

    unsigned int throw_index = object_list.at(object_in_hand);
    PKU_object temp_object = object_vector[throw_index];
    // update my property
    update_knowledge(temp_object.effect_to_other.my_knowledge_change);
    update_happiness(temp_object.effect_to_other.my_happiness_change);
    update_reputation(temp_object.effect_to_other.my_reputation_change);

    // remove the object from object_list
    vector<unsigned int>::iterator erase_iter = object_list.begin() + object_in_hand;
    object_list.erase(erase_iter);
    if(object_list.empty()) object_in_hand = -1;
    else object_in_hand = 0;
    

    //update others' property
    if(other_index != -1){
        player_vector[other_index].be_thrown_object(object_in_hand);
    }

} // throw object to other

void Player::be_thrown_object(unsigned int object_index){
    PKU_object temp_object = object_vector[object_index];
    // update my property
    update_knowledge(temp_object.effect_to_other.others_knowledge_change);
    update_happiness(temp_object.effect_to_other.others_happiness_change);
    update_reputation(temp_object.effect_to_other.others_reputation_change);
} // when be thrwon object



void Player::draw_player(){

}

/*---------------------------------   the functions for class "PKU_object" --------------------------------*/
PKU_object::PKU_object(string name0, unsigned int index0, Vector2 position0, Image object_image0, Rectangle size0, Self_effect effect_to_self0, Interaction_effect effect_to_other0);{
    name = name0;
    index = index0;
    position = position0;
    object_image = object_image0;
    size = size0;
    effect_to_self = effect_to_self0;
    effect_to_other = effect_to_other0;
    Object_state = UNPICKED;
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

void PKU_object::be_picked(){
    update_state(PICKED);
}

void PKU_object::be_throwned(){
    update_state(THROWING);
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
    vector<unsigned int> competition_list = vector();
    for(int i = 0; i < MAX_PLAYER; ++i)
    {
        if(attend_players[i] == 1) competition_list.push_back(i);
    }
    
    if(min_human == 1){
        unsigned int attend_index = competition_list.at(0);
        Player temp_player = player_vector[attend_index];
        temp_player.update_knowledge(property_effect.knowledge_effect);
        temp_player.update_happiness(property_effect.happiness_effect);
        temp_player.update_reputation(property_effect.reputation_effect);
    }
    else if(name == string("midterm exam")){
        continue; // to be continue
    }
    else if(name == string("final exam")){
        continue;// to be continue
    }
    else if(name == string("sports competition")){
        continue;// to be continue
    }
    // reset human number
    wait_human_num = 0;
    memset(attend_players, 0, MAX_PLAYER * sizeof(bool));
}

bool PKU_event::check_event_begin(float current_time) // check if in every frame
{
    if(current_time >= begin_time && current_time <= begin_time + time_span && if_begin == false)  if_begin = true;
    else if((current_time > begin_time + time_span || max_human <= 0) && if_begin == true){
        if(wait_human_num < min_human && wait_human_num > 0) begin_competition(); 
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