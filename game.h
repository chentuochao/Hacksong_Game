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
    int currentScreen = 0;
    int framesCounter = 0;
    bool eventhappen = false;
    string eventnote;

    Camera camera;

    int framsCounter;
    bool game_over = 0;
    unsigned int player_number = 0;
    unsigned int object_number = 0;
    unsigned int event_number = 0;
    int current_event_number = 0;

    static constexpr double KEY_ACCEL = 200; //Acceleration when pressing key
    double max_speed = 100;

    struct keys_info Keys_info[MAX_PLAYER];

    Game();
    ~Game();

    void init_player_list(void);
    void init_object_list(void);
    void init_event_list(void);
    void myInitGame(void);
    void myUpdate(void);
    void myDrawGame(void);



    // Functions from myUpdate.cpp
    void myGetKeyboardInfo();
    //if single person, get from keyboard. If server get from net.
    Vector2 myReadPlayerControl(int player_index);
    void myMovePlayer(int player_index, Vector2 accel);
    int check_player_clear(int player_index, Vector2 position);
    void myUpdatePlayerState(int player_index);
    void myUpdateObjectList(int player_index);
    void myObjectGenerate(int obj_index);
    void myEventCalc(int event_index);

    // Functions from myDrawGame.cpp
    void myDrawBackground();
    void myDrawLines();
    void myDrawPlayers();
    void myDrawObjectsToPick();
    void myDrawEventPlace();
    void myDrawInfo();

};
#endif