#include "game.h"

#define event_frames 60

void Game::myUpdate(){
    //srand(seed);
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
    // unpicked objects position calculation
    // TODO avoid events and players
    
    double chase_down = 10*10;
    double chase_speed = 4*max_speed;

    for (int obj_index=0; obj_index < (int)object_number ; obj_index++){

        if (object_vector[obj_index]->get_state() == NOT_APPEAR)
        {           
            //srand(seed);
            object_vector[obj_index]->size.x = rand() % screenWidth;//GetRandomValue(0, screenWidth);
            object_vector[obj_index]->size.y = rand() % screenHeight;//GetRandomValue(0, screenHeight);
            cout << obj_index << ' ' << object_vector[obj_index]->size.x  << ' ' << object_vector[obj_index]->size.y << endl;
            object_vector[obj_index]->update_state(UNPICKED);
        }
        if (object_vector[obj_index]->get_state() == THROWING){
            // If it chased down the target
            int target = object_vector[obj_index]->chasing_player;
            double t_x = player_vector[target]->position.x + 0.5*player_vector[target]->player_rectangle.width;
            double t_y = player_vector[target]->position.y + 0.5*player_vector[target]->player_rectangle.height;
            double my_x = object_vector[obj_index]->size.x+ 0.5*object_vector[obj_index]->size.width;
            double my_y = object_vector[obj_index]->size.y + 0.5*object_vector[obj_index]->size.height;
            double dist = (t_x-my_x)*(t_x-my_x)+(t_y-my_y)*(t_y-my_y);
            if (dist <= chase_down){
                object_vector[obj_index]->update_state(NOT_APPEAR);
            }
            else{
                double dx = t_x - my_x;
                double dy = t_y - my_y;
                double abs_dx = (dx>0?dx:-dx);
                double abs_dy = (dy>0?dy:-dy);
                double x_speed = chase_speed * (dx / (abs_dx + abs_dy + 1));
                double y_speed = chase_speed * (dy / (abs_dx + abs_dy + 1));
                object_vector[obj_index]->size.x += (x_speed / FPS);
                object_vector[obj_index]->size.y += (y_speed / FPS);
            }
        }

    }
    //关于要刷新的事件
    for (int event_index=0; event_index < event_number ; event_index++){
        //TODO
        int one_start_time = event_frames * event_vector[event_index]->start_time;
        int one_time_span = event_frames * event_vector[event_index]->time_span;
        int eventalarm = 20*event_frames;
        if(framesCounter < one_start_time && framesCounter > one_start_time - eventalarm){
            eventnote = event_vector[event_index]->name + " will start!";
            eventhappen = true;
            break;
        }
        else if (framesCounter > one_start_time && framesCounter < one_start_time + one_time_span){
            eventnote = event_vector[event_index]->name + " is ongoing!";
            eventhappen = true;
            current_event_number =  event_index;    
            break;   
        }     
        else if(framesCounter == one_start_time + one_time_span){
            myEventRes();
            eventhappen = false;
            break;
        }
        else{
            eventhappen = false;
        } 
    }
}

void Game::myGetKeyboardInfo(){
    // Now this reads player 0's info from the keyboard.
    // In multi-player version this should get all info from the
    my_key.move[0] = (IsKeyDown(KEY_W)!=0 ? 1 : 0);
    my_key.move[1] = (IsKeyDown(KEY_S)!=0 ? 1 : 0);
    my_key.move[2] = (IsKeyDown(KEY_A)!=0 ? 1 : 0);
    my_key.move[3] = (IsKeyDown(KEY_D)!=0 ? 1 : 0);

    my_key.change_object[0] = (IsKeyPressed(KEY_LEFT)!=0 ? 1 : 0);
    my_key.change_object[1] = (IsKeyPressed(KEY_RIGHT)!=0 ? 1 : 0);

    my_key.pick = (IsKeyPressed(KEY_DOWN)!=0 ? 1 : 0);
    my_key.throwing = (IsKeyPressed(KEY_UP)!=0 ? 1 : 0);
    
    my_key.join = (IsKeyPressed(KEY_SPACE)!=0 ? 1 : 0);

    //cout << "wait recv" <<endl;
    sock->send_data((const char*)&my_key, sizeof(Keys_info));
    
    sock->recvall(  (char*)return_info,   MAX_PLAYER*sizeof(Keys_info));
    //cout << int(return_info[0].pick) << endl;
    
    //for(int i = 0; i < player_number; ++i)
   //{
   //     cout << i  << " recv " << int(return_info[i].join) <<  ' ' << int(return_info[i].change_object[0]) <<  ' ' <<int(return_info[i].join) <<  ' ' <<int(return_info[i].pick) <<  ' ' <<int(return_info[i].move[0]) << ' ' << int(return_info[i].move[1]) << ' ' << int(return_info[i].move[2])<< ' ' << int(return_info[i].move[3])<< endl;
    //}
    
}

Vector2 Game::myReadPlayerControl(int player_index){
    //返回加速度的向量
    Vector2 accel = {0,0};
    if (return_info[player_index].move[0]) accel.y -= KEY_ACCEL;
    if (return_info[player_index].move[1]) accel.y += KEY_ACCEL;
    if (return_info[player_index].move[2]) accel.x -= KEY_ACCEL;
    if (return_info[player_index].move[3]) accel.x += KEY_ACCEL;
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
    for (int player_index=0; player_index < (int)player_number ; player_index++){
        player_vector[player_index]->update_object_effect();
    }

}

void Game::myUpdateObjectList(int player_index){
    // Pick up an item if exists
    double pickup_range = 100*100;
    double throw_range = 400*400;
    if (return_info[player_index].pick == 1){
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
    else if (return_info[player_index].throwing == 1){
        double my_x = player_vector[player_index]->position.x + 0.5*player_vector[player_index]->player_rectangle.width;
        double my_y = player_vector[player_index]->position.y + 0.5*player_vector[player_index]->player_rectangle.height;
        int daomeidan = -1;
        for (int i=0; i < (int)player_number; i++){
            // Check if two people are close enough
            if (i == player_index) continue; 
            double op_x = player_vector[i]->position.x + 0.5*player_vector[i]->player_rectangle.width;
            double op_y = player_vector[i]->position.y + 0.5*player_vector[i]->player_rectangle.height;
            double dist = (op_x-my_x)*(op_x-my_x)+(op_y-my_y)*(op_y-my_y);
            if (dist < throw_range){
                // found someone to be thrown at
                daomeidan = i;
                break;
            }
        }
        player_vector[player_index]->throw_object(daomeidan);
    }
    else if(return_info[player_index].change_object[0] ==1 || return_info[player_index].change_object[1] == 1){
        player_vector[player_index]->change_object();
    }
}

void Game::myObjectGenerate(int obj_index){

}

void Game::myEventCalc(int event_index){

}

void Game::myEventRes(){
	double all_knowledge = 0.0; // 0-100, visible to player
	double all_happiness = 0.0; // 0-100, visible to player
    double all_GPA = 0.0; // 0-4.0, visible to player
    double all_reputation = 0.0; // 0-100, invisible to player
    for (int player_index = 0; player_index < (int)player_number ; player_index++){
        all_reputation += player_vector[player_index]->get_property().reputation;
        all_happiness += player_vector[player_index]->get_property().happiness;
        all_knowledge += player_vector[player_index]->get_property().knowledge;
    }
    for (int player_index=0; player_index < (int)player_number ; player_index++){
        double knowledgerate = player_vector[player_index]->get_property().knowledge/all_knowledge;
        double reputationrate = player_vector[player_index]->get_property().reputation/all_reputation;
        double happinessrate = player_vector[player_index]->get_property().happiness/all_happiness;
        
        player_vector[player_index]->update_knowledge(knowledgerate*event_vector[current_event_number]->property_effect.knowledge_effect);       
        player_vector[player_index]->update_happiness(happinessrate*event_vector[current_event_number]->property_effect.happiness_effect);
        player_vector[player_index]->update_reputation(reputationrate*event_vector[current_event_number]->property_effect.reputation_effect);
        if(current_event_number == 0 || current_event_number == 4){
            double personscore = 80+(knowledgerate - 1/player_number)*20*player_number/(player_number-1);
            double examscore = GetRandomValue(80,personscore);
            double playerGPA = 4.0 - 3*(100-examscore)*(100-examscore)/1600;
            player_vector[player_index]->update_GPA(playerGPA);           
        }


    }
}