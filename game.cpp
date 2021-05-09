#include "game.h"
// #include "init.h"

Game::Game(){

}


int main(void)
{
    Game *g = new Game();
    InitWindow(g->screenWidth, g->screenHeight, "sample game: snake");
    g->myInitGame();


#if defined(PLATFORM_WEB)

    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

#else

    SetTargetFPS(60);

    //Main game loop
    //Detect window close button or ESC key
    while (!WindowShouldClose()) 
    {
        g->myUpdate();
        g->myDrawGame();
    }

#endif

    //Close window and OpenGL context
    CloseWindow();

    return 0;
}
