#ifndef __GAME__
#define __GAME__

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define SNAKE_LENGTH   256
#define SQUARE_SIZE     31

extern const int screenWidth;
extern const int screenHeight;

extern Camera camera;

#endif
