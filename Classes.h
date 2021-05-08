#ifndef _SETTING_H
#define _SETTING_H

#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;


typedef struct player_property
{
	unsigned float knowledge; // 0-100, visible to player
	unsigned float happiness; // 0-100, visible to player
    unsigned float GPA; // 0-4.0, visible to player
    unsigned float reputation; // 0-100, invisible to player
}Player_property;


typedef struct self_effect
{
	float knowledge_change_rate; // the change of knowledge value per second 
	float happiness_change_rate; // the change of happiness value per second 
}Self_effect;

typedef struct interaction_effect
{   
    // effects for myself
	float my_knowledge_change; // the change of knowledge value for me
	float my_happiness_change; // the change of happiness value for me
    float my_reputation_change; // the change of reputation value for me

    // effects for others
	float others_knowledge_change; // the change of knowledge value for others
	float others_happiness_change; // the change of happiness value for others
    float others_reputation_change; // the change of reputation value for others    
}Interaction_effect;

// the requirement for different properties
typedef struct event_property_requirement
{
	unsigned float knowledge_require; // 0-100, visible to player
	unsigned float happiness_require; // 0-100, visible to player
    unsigned float GPA_require; // 0-4.0, visible to player
    unsigned float reputation_require; // 0-100, invisible to player
}Event_property_requirement;

// the requirement for different properties
typedef struct event_property_effect
{
	unsigned float knowledge_effect; // 0-100, visible to player
	unsigned float happiness_effect; // 0-100, visible to player
    unsigned float GPA_effect; // 0-4.0, visible to player
    unsigned float reputation_effect; // 0-100, invisible to player
}Event_property_effect;


enum Player_walk_state = {RIGHT_FOOT_UP, MIDDLE, LEFT_FOOT_UP};
enum Player_activity_state = {WALKING, STAND, DOING_EVENT, THROW_OBJECT, FAIL}; // need to update !!!!!!!!

class Player
{
    public:
        Player();
        ~Player();

        // the shape and position of player
        string name;
        Image player_image;
        Rectangle player_rectangle;
        Color player_color;

        Vector2 position; // Current positions
        Vector2 direction; // the direction of human body

    private:
        // the inside property of player
        float speed; // walking speed
        Player_walk_state walk_state;
        Player_activity_state activity_state;
        Player_property property;
        unsigned int attack_range; 
};

enum Object_state = {UNPICKED, PICKED, USING, THROWING, THROWED}; // need to update !!!!!!!!


class PKU_object
{
    public:
        PKU_object();
        ~PKU_object();

        string name;
        Vector2 position;
        Image object_image;
        Rectangle size;

    private:
        Object_state state; 
        Self_effect effect_to_self; // effect to myself
        Interaction_effect effect_to_other; // effect to others
};


enum Event_place = {TEACHING_BUILDING, CAFFE, LIBRARY}; // the place where the event happens

class PKU_event
{
    public:
        PKU_event();
        ~PKU_event();
    
        string name;
    
    private:
        Event_place place;
        unsigned int max_human;
        Event_property_requirement requirement; 
        unsigned int start_time;
        unsigned int time_span;
        Event_property_effect property_effect;
};


 

#endif