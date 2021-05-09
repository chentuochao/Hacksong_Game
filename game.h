#ifndef __GAME__
#define __GAME__

#include "raylib.h"

#define SQUARE_SIZE 31
#define MAX_PLAYER 20
#define MAX_OBJECT 100
#define MAX_EVENT 100
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
    unsigned int object_number = 0;zdf
    unsigned int event_number = 0;
    vector<Player> player_vector[MAX_PLAYER];
    vector<PKU_object> object_vector[MAX_OBJECT];
    vector<PKU_event> event_vector[MAX_EVENT];

    Game();
    ~Game();

    void myInitGame(void);
    void myUpdate(void);
    void myDrawGame(void);
};
#endif