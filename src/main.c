#include "../include/main.h"

//Copie code SpaceInvader

int main(void)
{



    Game game;
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");


    // Game initialisation
    initGame(&game);

    // Main game loop
    while (!WindowShouldClose())
    {
        
        BeginDrawing();

        gameLoop(&game);

        EndDrawing();
        
    }




    // unload
    unloadGameTextures(&game);
    unloadGameMusic(&game);

    // close
    CloseAudioDevice();

    CloseWindow();


    return 0;
}