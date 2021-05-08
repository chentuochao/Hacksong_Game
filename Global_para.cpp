#include "Global_para.h"

bool game_over = 0;

unsigned int player_number = 0;
vector<Player> player_vector[MAX_PLAYER] ;

unsigned int object_number = 0; 
vector<PKU_object> object_vector[MAX_OBJECT];

unsigned int event_number = 0;
vector<PKU_event> event_vector[MAX_EVENT];