#include "game.h"

void Game::myUpdate();
Vector2 Game::myReadPlayerControl(int player_index);

void Game::myMovePlayer(int player_index, Vector2 accel);
int Game::check_player_clear(int player_index, Vector2 position)
//以下是myMovePlayer的子函数

void Game::myUpdatePlayerState(int player_index);
//判断玩家是否死亡等状态

void Game::myObjectGenerate(int obj_index);
void Game::myEventCalc(int event_index);