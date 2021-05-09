#include "game.h"
#include "dataset.h"
//Initialize game variables
void Game::myInitGame(void)
{
    init_player_list();
    init_object_list();
    init_event_list();
    
    return;
}
