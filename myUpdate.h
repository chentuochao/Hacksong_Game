#include "game.h"

void Game::myUpdate();
void Game::myReadPlayerControl(int player_index);

void Game::myMovePlayer(int player_index);
//以下是myMovePlayer的子函数

void Game::myUpdatePlayerState(int player_index);
//判断玩家是否死亡等状态

void Game::myObjectGenerate(int obj_index);
void Game::myEventCalc(int event_index);