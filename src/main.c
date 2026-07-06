
#include "raylib.h"

#include "game.h"
#include "map.h"
#include "player.h"
#include "key.h"
#include "exit.h"

#include <stdio.h>
#include <stdlib.h> 


int main(void) {
    
    const int screenWidth = 1280;       // Se establece ancho constante de monitor
    const int screenHeight = 720;       // Se establece altura constante de monitor

    Game game;
    MazeMap map;
    MazeTexture tex;
    Player player;
    Key key;
    ExitDoor door;

    InitWindow(screenWidth, screenHeight, "The Milkman.DEMO");  // Crea la ventana con dimensiones y titulo

    gameInit(&game);                                    // Inicializa los estados de juego

    LoadMaze(&map, &tex, "resources/maze_layout.png");  // Carga el mapa

    playerInit(&map, &player);                          // Inicializa el jugador

    keyInit(&key, &map);                                // Inicializa la llave

    exitInit(&door, &map);                              // Inicializa la salida

    DisableCursor();                 // Permite que el cursor unicamente se mueva con respecto a la pantalla de juego

    SetTargetFPS(60);                // Establece el maximo de FPS
    //--------------------------------------------------------------------------------------

    // Loop principal de juego, se actualiza cada frame
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {

        if (IsKeyPressed(KEY_F11)) {    // Permite cambiar la pantalla conpleta por una ventana
            ToggleFullscreen();
        }
        
        gameUpdate(&game);              // Actualiza el estado actual del juego


        BeginDrawing();

            //----------------------------------------------------------------------
            // Dibuja, cambia y actualiza los estados de juego
            //----------------------------------------------------------------------
            switch (game.state) {

                case GAME_MENU:

                    ClearBackground(BLACK);

                    gameDraw(&game);            // Carga la imagen del estado

                    //----------------------------------------------------------------------
                    // Si el jugador presiona ENTER, cambia el estado de juego a "playing"
                    //----------------------------------------------------------------------
                    if (IsKeyPressed(KEY_ENTER)) {
                        gameStart(&game, &player, &map, &key, &door);   // Activa los reset y cambia el estado a "PLAYING"
                    }

                    if (IsKeyPressed(KEY_C)) {

                        gameChangeState(&game, GAME_CONTROLS);
                    }

                    break;

                case GAME_CONTROLS:

                    ClearBackground(BLACK);

                    gameDraw(&game);

                    if (IsKeyPressed(KEY_ENTER)) {

                        gameChangeState(&game, GAME_MENU);
                    }

                    break;
                    
                case GAME_PLAYING:

                    playerUpdate(&map, &player);        // Actualiza la informacion del jugador
                    keyUpdate(&key, &player);           // Actualiza la informacion con respecto a la llave
                    exitUpdate(&door, &player, &map);   // Actualiza la informacion con respecto a la salida

                    if (door.winMatch) {
                        gameChangeState(&game, GAME_WIN);
                    }

                    ClearBackground(BLACK);

                    BeginMode3D(player.camera); // Empieza el modo tridimensional
                    
                    DrawMaze(&map, &tex);       // Carga el mapa
                    exitDraw(&door, &map);
                    keyDraw(&key);              // Carga el objeto de llave

                    EndMode3D();                // Termina los procesos relacionados al 3D

                    keyDrawUI(&key);            // Imprime el mansaje de recoleccion de llave
                    exitDrawUI(&door, &player);

                    DrawFPS(10, 10);            // Imprime en la pantalla los FPS actuales

                    break;

                case GAME_WIN:

                    ClearBackground(BLACK);

                    gameDraw(&game);            // Carga la imagen del estado

                    if (IsKeyPressed(KEY_ENTER)) {

                        gameChangeState(&game, GAME_MENU);
                    }
                    break;

                case GAME_OVER:

                    ClearBackground(BLACK);

                    gameDraw(&game);            // Carga la imagen del estado

                    if (IsKeyPressed(KEY_ENTER)) {

                        gameChangeState(&game, GAME_MENU);
                    }
                    break;

                case GAME_LOADING:          // Para un uso futuro...

                    ClearBackground(BLACK);

                    DrawText("Loading...", 300, 200, 30, WHITE);

                    break;

            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    keyUnload(&key);                // Liberar el modelo de la llave
    UnloadMaze(&tex);               // Liberar los modelos del maze
    exitUnload(&door);              // Liberar el modelo de la puerta
    gameUnload(&game);              // Liberar las texturas de las pantallas

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}




// Player en (91, 0.5, 11)
// Exit en (120, 0.5, 61) 
// Key 1 en ( 9, 0.5, 30)
// Key 2 en ( 113, 0.5, 86)
// Key 3 en ( , , )