#ifndef __GLOBALPARA__
#define __GLOBALPARA__

#include "Classes.h"
#include <vector>
using namespace std;

#define MAX_PLAYER 20
#define MAX_OBJECT 100
#define MAX_EVENT 100

extern bool game_over;

extern unsigned int player_number;
extern vector<Player> player_vector[MAX_PLAYER] ;

extern unsigned int object_number;
extern vector<PKU_object> object_vector[MAX_OBJECT];

extern unsigned int event_number;
extern vector<PKU_event> event_vector[MAX_EVENT];

#endif
