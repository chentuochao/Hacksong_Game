#ifndef _SETTING_H
#define _SETTING_H

#include <iostream>
#include <string>
#include "raylib.h"
#include "Global_para.h"

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




class Player
{
    public:
        Player(string name0, unsigned int index0, float speed0, Image player_image0, Rectangle player_rectangle0, Color player_color0);
        ~Player();

        enum Player_walk_state = {RIGHT_FOOT_UP, MIDDLE, LEFT_FOOT_UP};
        enum Player_activity_state = {WALKING, STAND, DOING_EVENT, THROW_OBJECT, FAIL}; // need to update !!!!!!!!

        // the shape and position of player
        string name;
        unsigned int index;
        Image player_image;
        Rectangle player_rectangle;
        Color player_color;

        Vector2 position; // Current positions
        float direction; // the direction of human body: degree

        void update_activity_state(Player_activity_state new_state); // update the activity state
        Player_activity_state get_activity_state(); // get the activity state

        void update_speed(float new_speed); // update the walking speed
        float get_speed(); // get the walking speed

        void update_knowledge(unsigned float new_knowledge); // update the knowledge
        void update_happiness(unsigned float new_happiness); // update the happiness
        void update_GPA(unsigned float new_GPA); // update the GPA
        void update_reputation(unsigned float new_reputation); // update the _reputation
        Player_property get_property(); // get the direction

        void draw_player();

    private:
        // the inside property of player
        float speed; // walking speed

        vector<unsigned int> object_list;
        Player_walk_state walk_state;
        Player_activity_state activity_state;
        Player_property property;
        unsigned int attack_range; 
};




class PKU_object
{
    public:
        PKU_object(string name0, unsigned int index0, Vector2 position0, Image object_image0, Rectangle size0, Self_effect effect_to_self0, Interaction_effect effect_to_other0);
        ~PKU_object();

        enum Object_state = {UNPICKED, PICKED, USING, THROWING, THROWED}; // need to update !!!!!!!!
        string name;
        unsigned int index;
        Vector2 position;
        Image object_image;
        Rectangle size;

        void update_state(Object_state new_state);
        Object_state get_state();

        Self_effect get_self_effect();
        Interaction_effect get_interaction_effect();

        void draw_object();

    private:
        Object_state state; 
        Self_effect effect_to_self; // effect to myself
        Interaction_effect effect_to_other; // effect to others
};



class PKU_event
{
    public:
        PKU_event(string name0, unsigned int index0, string information0, Event_place place0, unsigned int max_human0, unsigned int min_human0, Event_property_requirement requirement0, float start_time0, float time_span0, Event_property_effect property_effect0);
        ~PKU_event();

        enum Event_place = {TEACHING_BUILDING, CAFFE, LIBRARY}; // the place where the event happens

        string name;
        bool if_begin; // if the activity begins
        unsigned int index;
        string information;
        Event_place place;

        unsigned int max_human;
        unsigned int min_human;
        unsigned int wait_human_num;

        float start_time;
        float time_span;

        void begin_competition();
        bool check_event_begin(float current_time);
        bool player_want_to_join(Player p);
        void draw_event();

    private:
        bool attend_players[MAX_PLAYER];
        Event_property_requirement requirement; 
        Event_property_effect property_effect;

};


 

#endif