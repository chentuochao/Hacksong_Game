#include "game.h"

void myUpdate();
void myReadPlayerControl(int player_index);

void myMovePlayer(int player_index);
//以下是myMovePlayer的子函数

void myUpdatePlayerState(int player_index);
//判断玩家是否死亡等状态

void myObjectGenerate(int obj_index);
void myEventCalc(int event_index);