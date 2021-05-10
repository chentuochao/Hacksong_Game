#include "game.h"
#include "raylib.h"

Game::Game(){
    // init the network setttings
    char ip_add[20] = {'\0'};
	memset(ip_add, 0, 20);
	
	int port = 0;
	cout << "Please input the ip: " << endl;
	cin >> ip_add;
	cout << ip_add << " Please input the port number: " << endl;
	cin >> port;
    
    sock = new Myclient(ip_add, port);
    
    Send_data0 data0;
    sock->recvall((char*)&data0, sizeof(Send_data0));

    player_number = data0.player_number;
    my_index = data0.index;
    seed = data0.random_seed;
    srand(seed);
    cout << "Total " << player_number << " players attend this game, my index is " << my_index << endl;
    memset(&my_key, 0, sizeof(Keys_info));
}

int main(void)
{
    WSASession Session;
    // init the game and screen settings
    Game *g = new Game();
    InitWindow(g->screenWidth, g->screenHeight, "involution");
    g->myInitGame();

    Image mybg = LoadImage("endings/map.png");
    ImageResize(&mybg, 1280, 720);
    Texture2D BG = LoadTextureFromImage(mybg);


    SetTargetFPS(60);
    //Main game loop
    //Detect window close button or ESC key
    //int time_seed = 0;

    Image im_cover = LoadImage("endings/cover.png");
    ImageResize(&im_cover,1280,960);
    Texture2D cover = LoadTextureFromImage(im_cover);
    while (!WindowShouldClose()){
        //starting page
        bool enter = IsKeyPressed(KEY_ENTER);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(cover, 0, 0, WHITE);    
        DrawText("PRESS ENTER TO START", 50, 50, 40, BLACK);
        EndDrawing();
        if (enter) break;
    }


    int frame_count = 0;
    while (!WindowShouldClose()) 
    {   
        srand(g->framesCounter);
        //time_seed++;
        g->myUpdate();
        frame_count++;
        frame_count++;
        g->currentScreen = 1;//don't care about it
        //----------------------------------------------------------------------------------
        cout << "begin main loop1!" << endl;
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);
        // Draw background (common to all screens)
        DrawTexture(BG, 0, 0, WHITE);    
        cout << "begin main loop2!" << endl;
        g->myDrawGame();
        cout << "begin main loop3!" << endl;
        EndDrawing();

        if (frame_count >= 180*FPS){
            g->game_result = 0;
            break;
        }
        if (g->game_over == 1) break;
    }

    if (game_result >=0 ){
        Image im_normal = LoadImage("endings/normal.png");
        ImageResize(&im_normal, 600, 600);
        Texture2D normal = LoadTextureFromImage(im_normal);

        Image im_award = LoadImage("endings/award.png");
        ImageResize(&im_award, 600, 600);
        Texture2D award = LoadTextureFromImage(im_award);

        Image im_lonelyking = LoadImage("endings/lonelyking.png");
        ImageResize(&im_lonelyking, 600, 600);
        Texture2D lonelyking = LoadTextureFromImage(im_lonelyking);

        Image im_depression = LoadImage("endings/depression.png");
        ImageResize(&im_depression, 600, 600);
        Texture2D depression = LoadTextureFromImage(im_depression);

        Image im_failexam = LoadImage("endings/failexam.png");
        ImageResize(&im_failexam, 600, 600);
        Texture2D failexam = LoadTextureFromImage(im_failexam);

         while (!WindowShouldClose()) 
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (g->game_result)
            {
                //0 is normal, 1 is award, 2 is lonelyking, 3 is depression, 4 is failexam
                case 0:
                {
                    DrawTexture(normal, 340, 100, WHITE);  
                }break;
                case 1:
                {
                    DrawTexture(award, 340, 100, WHITE); 
                }break;
                case 2:
                {
                    DrawTexture(lonelyking, 340, 100, WHITE); 
                }break;
                case 3:
                {
                    DrawTexture(depression, 340, 100, WHITE); 
                }break;
                case 4:
                {
                    DrawTexture(failexam, 340, 100, WHITE); 
                }break;
            }
            bool enter = IsKeyPressed(KEY_ENTER);  
            DrawText("PRESS ENTER TO EXIT", 450, 420, 40, BLACK);
        if (enter) break;
            EndDrawing();
        }
    }

    Keys_info control2;
    memset(&control2, 0, sizeof(Keys_info));
    control2.join =2;
    g->sock->send_data((const char*)&control2, sizeof(Keys_info));

    CloseWindow();
    return 0;
}
