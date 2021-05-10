#include "game.h"
#include "raylib.h"

Game::Game(){

}

int main(void)
{
    Game *g = new Game();
    InitWindow(g->screenWidth, g->screenHeight, "involution");
    g->myInitGame();

    Image mybg = LoadImage("icons/map.png");
    ImageResize(&mybg, 1280, 720);
    Texture2D BG = LoadTextureFromImage(mybg);


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
                g->framesCounter += 1;
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
        
        g->myDrawGame();
        EndDrawing();
    
        if (g->framesCounter >= 180 * FPS || g->game_over) break;
    }

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
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
