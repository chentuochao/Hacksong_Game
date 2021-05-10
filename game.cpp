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
    while (true){
        //starting page
        bool enter = IsKeyPressed(KEY_ENTER);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(cover, 0, 0, WHITE);    
        DrawText("PRESS ENTER TO START", 450, 420, 40, BLACK);
        EndDrawing();
        if (enter) break;
    }


    while (!WindowShouldClose()) 
    {   
        srand(g->framesCounter);
        //time_seed++;
        g->myUpdate();
        g->framesCounter += 1;
        g->currentScreen = 1;//don't care about it
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);
        // Draw background (common to all screens)
        DrawTexture(BG, 0, 0, WHITE);    
        
        g->myDrawGame();
        EndDrawing();
    }
    Keys_info control2;
    memset(&control2, 0, sizeof(Keys_info));
    control2.join =2;
    g->sock->send_data((const char*)&control2, sizeof(Keys_info));

    CloseWindow();
    return 0;
}
