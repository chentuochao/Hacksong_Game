#ifndef __GAME__
#define __GAME__

#include "raylib.h"

#define SQUARE_SIZE 31

#include "Classes.h"
#include <vector>
using namespace std;


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


class Game{
public:
    static const int screenWidth = 1280;
    static const int screenHeight = 920;
    static const int mapWidth = 1280;
    static const int mapHeight = 720;
    Camera camera;

    int framsCounter;
    bool game_over = 0;
    unsigned int player_number = 0;
    unsigned int object_number = 0;
    unsigned int event_number = 0;

    Game();
    ~Game();

    void myInitGame(void);
    void myUpdate(void);
    void myDrawGame(void);
};
#endif