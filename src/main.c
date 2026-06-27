
#include "raylib.h"
#include "map.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>    


int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - first person maze");
    
    MazeMap map;
    MazeTexture tex;
    
    LoadMaze(&map, &tex, "resources/maze_layout.png");

    Player player;

    playerInit(&map, &player);


    DisableCursor();                // Permite que el cursor unicamente se mueva con respecto a la pantalla de juego

    SetTargetFPS(120);               // Establece el maximo de FPS
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        playerUpdate(&map, &player);

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(player.camera);
            DrawMaze(&map, &tex);
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }


    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

//    UnloadImageColors(pixels);

    return 0;
}


// Posiblemente usar

// GetRandomValue(1,3); para las llaves
// MinimizeWindow(void); // minimizar pantalla
// MaximizeWindow(void); // makimizar pantalla
// GetScreenHeight(void);  //obtener altura del monitor
// GetScreenWidth(void);  // obtener ancho del monitor
// Texture2D background = LoadTexture("resources/... .png"); // Establecer imagen de fondo
// 
// 
// 