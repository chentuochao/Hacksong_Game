#include "game.h"
#include "init.h"

int main(void)
{
    InitWindow(screenWidth, screenHeight, "sample game: snake");
    myInitGame();

#if defined(PLATFORM_WEB)

    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

#else

    SetTargetFPS(60);

    //Main game loop
    //Detect window close button or ESC key
    while (!WindowShouldClose()) 
    {
        myUpdateGame();
        myDrawGame();
    }

#endif

    //Close window and OpenGL context
    CloseWindow();

    return 0;
}
