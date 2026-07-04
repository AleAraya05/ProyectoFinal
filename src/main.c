
#include "raylib.h"
#include "map.h"
#include "player.h"
#include "key.h"
#include "exit.h"

#include <stdio.h>
#include <stdlib.h> 


int main(void) {
    
    const int screenWidth = 1280;       // Se establece ancho constante de monitor
    const int screenHeight = 720;       // Se establece altura constante de monitor

    InitWindow(screenWidth, screenHeight, "The Milkman.DEMO");  // Crea la ventana con dimensiones y titulo
    
    MazeMap map;
    MazeTexture tex;
    Player player;
    Key key;
    ExitDoor door;

    
    LoadMaze(&map, &tex, "resources/maze_layout.png");  // Carga el mapa

    playerInit(&map, &player);                          // Inicializa el jugador

    keyInit(&key, &map);                                // Inicializa la llave

    exitInit(&door, &map);                              // Inicializa la salida

    printf("Exit: %.2f %.2f %.2f \n", map.playerSpawn.x, map.playerSpawn.y, map.playerSpawn.z );

    DisableCursor();                 // Permite que el cursor unicamente se mueva con respecto a la pantalla de juego

    SetTargetFPS(60);                // Establece el maximo de FPS
    //--------------------------------------------------------------------------------------

    // Loop principal de juego
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {

        if (IsKeyPressed(KEY_F11)) {    // Permite cambiar la pantalla conpleta por una ventana
            ToggleFullscreen();
        }
        
        playerUpdate(&map, &player);    // Actualiza la informacion del jugador
        keyUpdate(&key, &player);       // Actualiza la informacion con respecto a la llave
        exitUpdate(&door, &player, &map);   // Actualiza la informacion con respecto a la salida

        BeginDrawing();                 // Carga el contenido de la ventana

            ClearBackground(BLACK);     // Establece un fondo base

            BeginMode3D(player.camera); // Empieza el modo tridimensional
            
            DrawMaze(&map, &tex);       // Carga el mapa
            exitDraw(&door, &map);
            keyDraw(&key);              // Carga el objeto de llave

            EndMode3D();                // Termina los procesos relacionados al 3D

            keyDrawUI(&key);            // Imprime el mansaje de recoleccion de llave
            exitDrawUI(&door, &player);

            DrawFPS(10, 10);            // Imprime en la pantalla los FPS actuales

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    keyUnload(&key);                // Liberar el modelo de la llave
    UnloadMaze(&tex);               // Liberar los modelos del maze
    exitUnload(&door);

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}


// Posiblemente usar

// Texture2D background = LoadTexture("resources/... .png"); // Establecer imagen de fondo
// Raymath
// Vector3Substract() // Util para el enemigo
// Vector3Lerp() // Util para animaciones





// Player en (91, 0.5, 11)
// Exit en (120, 0.5, 61) 
// Key 1 en ( 9, 0.5, 30)
// Key 2 en ( 113, 0.5, 86)
// Key 3 en ( , , )