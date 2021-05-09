#include "game.h"


void Game::myUpdate(){
    //std::cout<<"Debugging:\n";
    //关于人
    
    myGetKeyboardInfo();

    for (int player_index=0; player_index < (int)player_number ; player_index++){
        Vector2 accel = myReadPlayerControl(player_index);
        myMovePlayer(player_index,accel);
        myUpdateObjectList(player_index);
        myUpdatePlayerState(player_index);
        //判断玩家是否死亡等状态                                      
    }
    std::cout<<"Debug1:\n";
    // unpicked objects position calculation
    // TODO avoid events and players
    for (int obj_index=0; obj_index < (int)object_number ; obj_index++){

        if (object_vector[obj_index]->get_state() == NOT_APPEAR)
        {           
            object_vector[obj_index]->size.x = GetRandomValue(0, screenWidth);
            object_vector[obj_index]->size.y = GetRandomValue(0, screenHeight);
        }
        

    }
    //关于要刷新的事件
    for (int event_index=0; event_index < (int)event_number ; event_index++){
        // myEventCalc(event_index);
    }
}

void Game::myGetKeyboardInfo(){
    // Now this reads player 0's info from the keyboard.
    // In multi-player version this should get all info from the
    Keys_info[0].move[0] = (IsKeyDown(KEY_W)!=0 ? 1 : 0);
    Keys_info[0].move[1] = (IsKeyDown(KEY_S)!=0 ? 1 : 0);
    Keys_info[0].move[2] = (IsKeyDown(KEY_A)!=0 ? 1 : 0);
    Keys_info[0].move[3] = (IsKeyDown(KEY_D)!=0 ? 1 : 0);

    Keys_info[0].change_object[0] = (IsKeyPressed(KEY_LEFT)!=0 ? 1 : 0);
    Keys_info[0].change_object[1] = (IsKeyPressed(KEY_RIGHT)!=0 ? 1 : 0);

    Keys_info[0].pick = (IsKeyPressed(KEY_DOWN)!=0 ? 1 : 0);
    Keys_info[0].throwing = (IsKeyPressed(KEY_UP)!=0 ? 1 : 0);
    
    Keys_info[0].join = (IsKeyPressed(KEY_SPACE)!=0 ? 1 : 0);
}

Vector2 Game::myReadPlayerControl(int player_index){
    //返回加速度的向量
    Vector2 accel = {0,0};
    if (Keys_info[player_index].move[0]) accel.y -= KEY_ACCEL;
    if (Keys_info[player_index].move[1]) accel.y += KEY_ACCEL;
    if (Keys_info[player_index].move[2]) accel.x -= KEY_ACCEL;
    if (Keys_info[player_index].move[3]) accel.x += KEY_ACCEL;
    return(accel);

}

void Game::myMovePlayer(int player_index, Vector2 accel){
    Vector2 speed = player_vector[player_index]->get_speed();
    Vector2 cur_pos = player_vector[player_index]->position;

    //检查周围一圈，只能往没有障碍物的方向加速。
    int clear = check_player_clear(player_index, cur_pos);
    bool up_clear = (((clear >> 0) & 1) == 1);
    bool down_clear = (((clear >> 1) & 1) == 1);
    bool left_clear = (((clear >> 2) & 1) == 1);
    bool right_clear = (((clear >> 3) & 1) == 1);

    // 根据键盘加减速。只能往没有阻挡的方向获得加速度。
    if (right_clear && accel.x > 0){
        speed.x += accel.x / FPS;
        speed.x = min((double)speed.x, max_speed);
    }
    if (left_clear && accel.x < 0){
        speed.x += accel.x / FPS;
        speed.x = max((double)speed.x, -max_speed);
    }
    if (down_clear && accel.y > 0){
        speed.y += accel.y / FPS;
        speed.y = min((double)speed.y, max_speed);
    }
    if (up_clear && accel.y < 0){
        speed.y += accel.y / FPS;
        speed.y = max((double)speed.y, -max_speed);
    }
    // 没有按键的方向，因为摩擦力而减速。
    double stop_accel = 2*KEY_ACCEL;
    if (accel.x == 0){
        if (speed.x > 0) speed.x = max(0.0, speed.x - stop_accel / FPS);
        if (speed.x < 0) speed.x = min(0.0, speed.x + stop_accel / FPS);
    }
    if (accel.y == 0){
        if (speed.y > 0) speed.y = max(0.0, speed.y - stop_accel / FPS);
        if (speed.y < 0) speed.y = min(0.0, speed.y + stop_accel / FPS);
    }

    // 计算玩家顺滑运动会到的位置
    Vector2 target = {cur_pos.x + speed.x / FPS, 
    cur_pos.y + speed.y / FPS};

    // Consider if the target is a clear point.
    int new_clear = check_player_clear(player_index, target);
    bool new_up_clear = (((new_clear >> 0) & 1) == 1);
    bool new_down_clear = (((new_clear >> 1) & 1) == 1);
    bool new_left_clear = (((new_clear >> 2) & 1) == 1);
    bool new_right_clear = (((new_clear >> 3) & 1) == 1);

    // If it will bump & the back is clear, bump it back. Else make it stop.
    double bump_coeff = 0.3;
    
    if (!new_up_clear && speed.y < 0){
        if (down_clear){
            speed.y = -bump_coeff * speed.y;
        }
        else{
            speed.y = 0;
        }
    }
    if (!new_down_clear && speed.y > 0){
        if (up_clear){
            speed.y = -bump_coeff * speed.y;
        }
        else{
            speed.y = 0;
        }
    }
    if (!new_left_clear && speed.x < 0){
        if (right_clear){
            speed.x = -bump_coeff * speed.x;
        }
        else{
            speed.x = 0;
        }
    }
    if (!new_right_clear && speed.x > 0){
        if (left_clear){
            speed.x = -bump_coeff * speed.x;
        }
        else{
            speed.x = 0;
        }
    }

    // Got the final speed. Now calculate the new position.
    player_vector[player_index]->update_speed(speed);
    player_vector[player_index]->position.x += (speed.x / FPS);
    player_vector[player_index]->position.y += (speed.y / FPS);

    // 判断是否遇到物品
    // 判断是否进入事件范围
}

int Game::check_player_clear(int player_index, Vector2 position){
    //返回一个int。其中第0位是上边是否clear，第1位是下边（y大）是否clear，
    //第2位是左边（x小）是否clear，第3位是右边是否clear。clear是1，blocked是0.
    //这里检查的是该范围内是否有墙，或者其他玩家。
    
    bool up_clear=1, down_clear=1, left_clear=1, right_clear=1;
    double my_w = player_vector[player_index]->player_rectangle.width;
    double my_h = player_vector[player_index]->player_rectangle.height;
    double my_x = position.x;
    double my_y = position.y;

    //判断四面墙
    if (my_x <= 0 + 1) left_clear = 0;
    if (my_y <= 0 + 1) up_clear = 0;
    if (my_x + my_w >= mapWidth - 1) right_clear = 0;
    if (my_y + my_h >= mapHeight - 1) down_clear = 0;

    //判断所有其他玩家
    double margin = 0.1; //一个常量，表示人与人之间的最小距离
    for (int i = 0; i< (int)player_number; i++){
        if (i==player_index) continue;
        double other_x = player_vector[i]->position.x;
        double other_y = player_vector[i]->position.y;

        //它挡住了右侧
        bool block_right = (other_x >= my_x + my_w) && (other_x <= my_x + my_w + margin)
        && (other_y + my_h >= my_y - margin) && (other_y <= my_y + my_h + margin);
        if (block_right) right_clear = 0;
        //它挡住了左侧
        bool block_left = (other_x + my_w <= my_x) && (other_x + my_w >= my_x - margin)
        && (other_y + my_h >= my_y - margin) && (other_y <= my_y + my_h + margin);
        if (block_left) left_clear = 0;
        //它挡住了下方
        bool block_down = (other_y >= my_y + my_h) && (other_y <= my_y + my_h + margin)
        && (other_x + my_w >= my_x - margin) && (other_x <= my_x + my_w + margin);
        if (block_down) down_clear = 0;
        //它挡住了上方
        bool block_up = (other_y + my_h <= my_y) && (other_y + my_h >= my_y - margin)
        && (other_x + my_w >= my_x - margin) && (other_x <= my_x + my_w + margin);
        if (block_up) up_clear = 0;

    }

    int clear=0;
    if (up_clear) clear = clear | (1 << 0);
    if (down_clear) clear = clear | (1 << 1);
    if (left_clear) clear = clear | (1 << 2);
    if (right_clear) clear = clear | (1 << 3);
    return(clear);
}

void Game::myUpdatePlayerState(int player_index){
    //判断玩家是否死亡等状态

}

void Game::myUpdateObjectList(int player_index){
    // Pick up an item if exists
    double pickup_range = 100*100;
    double throw_range = 200*200;
    if (Keys_info[player_index].pick == 1){
        double my_x = player_vector[player_index]->position.x + 0.5*player_vector[player_index]->player_rectangle.width;
        double my_y = player_vector[player_index]->position.y + 0.5*player_vector[player_index]->player_rectangle.height;
        for (int i=0; i < (int)object_number; i++){
            // Check if it is close enough
            if (object_vector[i]->get_state()!=UNPICKED) continue; 
            double ob_x = object_vector[i]->size.x + 0.5*object_vector[i]->size.width;
            double ob_y = object_vector[i]->size.y + 0.5*object_vector[i]->size.height;
            double dist = (ob_x-my_x)*(ob_x-my_x)+(ob_y-my_y)*(ob_y-my_y);
            if (dist < pickup_range){
                bool success = player_vector[player_index]->pick_object(i);
                if (success) object_vector[i]->be_picked();
                break;
            }
        }
    }
    else if (Keys_info[player_index].throwing == 1){
        double my_x = player_vector[player_index]->position.x + 0.5*player_vector[player_index]->player_rectangle.width;
        double my_y = player_vector[player_index]->position.y + 0.5*player_vector[player_index]->player_rectangle.height;
        int daomeidan = -1;
        for (int i=0; i < (int)player_number; i++){
            // Check if two people are close enough
            if (i == player_index) continue; 
            double op_x = player_vector[player_index]->position.x + 0.5*player_vector[player_index]->player_rectangle.width;
            double op_y = player_vector[player_index]->position.y + 0.5*player_vector[player_index]->player_rectangle.height;
            double dist = (op_x-my_x)*(op_x-my_x)+(op_y-my_y)*(op_y-my_y);
            if (dist < throw_range){
                // found someone to be thrown at
                daomeidan = i;
                break;
            }
        }
        player_vector[player_index]->throw_object(daomeidan);
    }
}

void Game::myObjectGenerate(int obj_index){

}

void Game::myEventCalc(int event_index){

}