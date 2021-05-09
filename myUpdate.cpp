#include "game.h"

void Game::myUpdate(){
    //关于人
    for (int player_index=0; player_index < player_number ; player_index++){
        /*
        myReadPlayerControl(player_index);
        myMovePlayer(player_index);
        // 计算玩家顺滑运动会到的位置
        // 计算会不会撞到墙（撞到后微弹回来）
        // 计算会不会撞到其他玩家（微弹）
        // 判断是否遇到物品
        // 判断是否进入事件范围        
        myUpdatePlayerState(player_index);
        //判断玩家是否死亡等状态
        */                                         
    }
    //关于要刷新的物品
    for (int obj_index=0; obj_index < object_number ; obj_index++){
        // myObjectGenerate(obj_index);
    }
    //关于要刷新的事件
    for (int event_index=0; event_index < event_number ; event_index++){
        // myEventCalc(event_index);
    }
}