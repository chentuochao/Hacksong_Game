#include "game.h"
#include "raylib.h"

Game::Game(){

}

int main(void)
{
    Game *g = new Game();
    InitWindow(g->screenWidth, g->screenHeight, "involution");
    g->myInitGame();

    Image mybutton = LoadImage("icons/home.png");
    ImageResize(&mybutton , 100, 100);
    Texture2D BUTTON = LoadTextureFromImage(mybutton);

    Image mycover = LoadImage("icons/cover.png");
    ImageResize(&mycover, 1280, 950);
    Texture2D COVER = LoadTextureFromImage(mycover);
    Image mybg = LoadImage("icons/map.png");
    ImageResize(&mybg, 1280, 720);
    Texture2D BG = LoadTextureFromImage(mybg);
    Image myend = LoadImage("icons/ending.png");
    ImageResize(&myend, 1280, 950);
    Texture2D END = LoadTextureFromImage(myend);

    SetTargetFPS(60);
    //Main game loop
    //Detect window close button or ESC key
    
    while (!WindowShouldClose()) 
    {
        g->myUpdate();
        switch (g->currentScreen)
        {
            case 0:
            {
                // Press enter to change to gameplay screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    g->currentScreen = 1;
                }
                
            } break;
            case 1:
            {
                
                
                // Press enter to change to ending screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    g->currentScreen = 2;
                }
                
            } break;
            case 2:
            {
                // Press enter to change to title screen
                if (IsKeyPressed(KEY_ENTER))
                {
                   g->currentScreen = 0;
                }
      
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw background (common to all screens)
        DrawTexture(BG, 0, 0, WHITE);    
        switch (g->currentScreen)
        {
        case 0:
        {
            DrawTexture(COVER, 0, 0, WHITE);
            DrawText("PRESS ENTER", 450, 420, 40, BLACK);  
            break;
        }
        case 1:
        {
            DrawTexture(BG, 0, 0, WHITE);  
            DrawRectangle(0, 750, 640, 130, Fade(BLACK, 0.8f));
            DrawRectangle(0, 880, 1280, 70, Fade(BLACK, 0.9f));
            DrawRectangle(640, 750, 1280, 130, BLACK);
            DrawText("Knowledge", 10, 760, 30, BLACK);  
            DrawText("GPA", 10, 800, 30, BLACK);  
            DrawText("Happiness", 10, 840, 30, BLACK);  
            break;
        }
        case 2:
        {
            DrawRectangle(0, 0, g->screenWidth, g->screenHeight, Fade(BLACK, 0.4f));
            DrawTexture(END, 0, 0, WHITE);  
            break;
        }
        default:
            break;
        }
        g->myDrawGame();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
