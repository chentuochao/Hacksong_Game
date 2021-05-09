#ifndef _SETTING_H
#define _SETTING_H

#include <iostream>
#include <string>

#include "raylib.h"
#include <vector>
using namespace std;

#define MAX_PLAYER 20
#define MAX_OBJECT 100
#define MAX_EVENT 100
#define MAX_OBJECT_PER_PERSON 10
#define FPS 60

typedef struct player_property
{
	double knowledge; // 0-100, visible to player
	double happiness; // 0-100, visible to player
    double GPA; // 0-4.0, visible to player
    double reputation; // 0-100, invisible to player
}Player_property;


typedef struct self_effect
{
	double knowledge_change_rate; // the change of knowledge value per second 
	double happiness_change_rate; // the change of happiness value per second 
}Self_effect;

typedef struct interaction_effect
{   
    // effects for myself
	double my_knowledge_change; // the change of knowledge value for me
	double my_happiness_change; // the change of happiness value for me
    double my_reputation_change; // the change of reputation value for me

    // effects for others
	double others_knowledge_change; // the change of knowledge value for others
	double others_happiness_change; // the change of happiness value for others
    double others_reputation_change; // the change of reputation value for others    
}Interaction_effect;

// the requirement for different properties
typedef struct event_property_requirement
{
	double knowledge_require; // 0-100, visible to player
	double happiness_require; // 0-100, visible to player
    double GPA_require; // 0-4.0, visible to player
    double reputation_require; // 0-100, invisible to player
}Event_property_requirement;

// the requirement for different properties
typedef struct event_property_effect
{
	double knowledge_effect; // 0-100, visible to player
	double happiness_effect; // 0-100, visible to player
    double GPA_effect; // 0-4.0, visible to player
    double reputation_effect; // 0-100, invisible to player
}Event_property_effect;


enum Player_walk_state {RIGHT_FOOT_UP, MIDDLE, LEFT_FOOT_UP};
enum Player_activity_state {WALKING, STAND, DOING_EVENT, THROW_OBJECT, FAIL}; // need to update !!!!!!!!


class Player
{
    public:
        Player(unsigned int index0,string name0,  Vector2 speed0, Image player_image0, Rectangle player_rectangle0, Color player_color0);
        ~Player();


        // the shape and position of player
        string name;
        int index;
        Image player_image;
        Rectangle player_rectangle;
        Color player_color;

        Vector2 position; // Current positions
        double direction; // the direction of human body: degree

        void update_activity_state(Player_activity_state new_state); // update the activity state
        Player_activity_state get_activity_state(); // get the activity state

        void update_speed(Vector2 new_speed); // update the walking speed
        Vector2 get_speed(); // get the walking speed

        void update_knowledge(double new_knowledge); // update the knowledge
        void update_happiness(double new_happiness); // update the happiness
        void update_GPA(double new_GPA); // update the GPA
        void update_reputation(double new_reputation); // update the _reputation
        Player_property get_property(); // get the direction

        bool pick_object(unsigned int object_index); // pick the objects
        void change_object();  // change object
        void update_object_effect(); // update the effect of the object in the hand

        void throw_object(unsigned int other_index); // throw object to other
        void be_thrown_object(unsigned int object_index); // when be thrwon object

        void draw_player();

    private:
        // the inside property of player
        Vector2 speed; // walking speed

        vector<unsigned int> object_list;
        int object_in_hand;

        Player_walk_state walk_state;
        Player_activity_state activity_state;
        Player_property property;
        int attack_range; 
};


enum Object_state {NOT_APPEAR, UNPICKED, PICKED, USING, THROWING, THROWED}; // need to update !!!!!!!!


class PKU_object
{
    public:
        PKU_object(string name0, unsigned int index0, Image object_image0, Rectangle range0, Self_effect effect_to_self0, Interaction_effect effect_to_other0);
        ~PKU_object();

        string name;
        int index;
        Image object_image;
        Rectangle size;

        void update_state(Object_state new_state);
        Object_state get_state();

        Self_effect get_self_effect();
        Interaction_effect get_interaction_effect();

        void be_picked();
        void be_throwned();

        void draw_object();


    private:
        Object_state state; 
        Self_effect effect_to_self; // effect to myself
        Interaction_effect effect_to_other; // effect to others
};

enum Event_place {TEACHING_BUILDING, CAFFE, LIBRARY}; // the place where the event happens

class PKU_event
{
    public:
        PKU_event(string name0, unsigned int index0, string information0, Event_place place0, unsigned int max_human0, unsigned int min_human0, Event_property_requirement requirement0, unsigned int start_time0, unsigned int time_span0, Event_property_effect property_effect0);
        ~PKU_event();

        

        string name;
        bool if_begin; // if the activity begins
        int index;
        string information;
        Event_place place;

        int max_human;
        int min_human;
        int wait_human_num;

        double start_time;
        double time_span;

        void begin_competition();
        bool check_event_begin(double current_time);
        bool player_want_to_join(Player p);
        void draw_event();
        

    private:
        bool attend_players[MAX_PLAYER];
        Event_property_requirement requirement; 
        Event_property_effect property_effect;

};

extern unsigned int player_number;
extern Player* player_vector[MAX_PLAYER];

extern unsigned int object_number;
extern PKU_object* object_vector[MAX_OBJECT];

extern unsigned int event_number;
extern PKU_event* event_vector[MAX_EVENT];
 

#endif