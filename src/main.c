/*******************************************************************************************
*
*   raylib [models] example - first person maze
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "map.h"

#include <stdio.h>
#include <stdlib.h>           // Required for: free()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - first person maze");
    
    MazeMap maze;
    MazeTexture tex;
    
    LoadMaze(&maze, &tex, "resources/maze_layout.png");

    printf("Working dir: %s\n", GetWorkingDirectory());

    printf("Walls: %d\n", maze.wallCount);
    printf("Floors: %d\n", maze.floorCount);

    printf("Player: %.1f %.1f %.1f\n",
        maze.playerSpawn.x,
        maze.playerSpawn.y,
        maze.playerSpawn.z);



    printf("Spawn jugador: %.0f %.0f %.0f\n", maze.playerSpawn.x, maze.playerSpawn.y, maze.playerSpawn.z);

    Camera3D camera = {0};

    camera.position = maze.playerSpawn;

    camera.target = (Vector3){
        maze.playerSpawn.x + 1.0f,
        maze.playerSpawn.y,
        maze.playerSpawn.z
    };

    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;


    DisableCursor();                // Limit cursor to relative movement inside the window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Vector3 oldCamPos = camera.position;    // Store old camera position

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Check player collision (we simplify to 2D collision detection)
        // Vector2 playerPos = { camera.position.x, camera.position.z };
        // float playerRadius = 0.1f;  // Collision radius (player is modelled as a cilinder for collision)

        // int playerCellX = (int)(playerPos.x - mapPosition.x + 0.5f);
        // int playerCellY = (int)(playerPos.y - mapPosition.z + 0.5f);

        // // Out-of-limits security check
        // if (playerCellX < 0) playerCellX = 0;
        // else if (playerCellX >= cubicmap.width) playerCellX = cubicmap.width - 1;

        // if (playerCellY < 0) playerCellY = 0;
        // else if (playerCellY >= cubicmap.height) playerCellY = cubicmap.height - 1;

        // // Check map collisions using image data and player position against surrounding cells only
        // for (int y = playerCellY - 1; y <= playerCellY + 1; y++)
        // {
        //     // Avoid map accessing out of bounds
        //     if ((y >= 0) && (y < cubicmap.height))
        //     {
        //         for (int x = playerCellX - 1; x <= playerCellX + 1; x++)
        //         {
        //             // NOTE: Collision: Only checking R channel for white pixel
        //             if (((x >= 0) && (x < cubicmap.width)) &&
        //                 (mapPixels[y*cubicmap.width + x].r == 255) &&
        //                 (CheckCollisionCircleRec(playerPos, playerRadius,
        //                 (Rectangle){ mapPosition.x - 0.5f + x*1.0f, mapPosition.z - 0.5f + y*1.0f, 1.0f, 1.0f })))
        //             {
        //                 // Collision detected, reset camera position
        //                 camera.position = oldCamPos;
        //             }
        //         }
        //     }
        // }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
            DrawMaze(&maze, &tex);
            EndMode3D();

            // DrawTextureEx(cubicmap, (Vector2){ GetScreenWidth() - cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
            // DrawRectangleLines(GetScreenWidth() - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GREEN);

            // // Draw player position radar
            // DrawRectangle(GetScreenWidth() - cubicmap.width*4 - 20 + playerCellX*4, 20 + playerCellY*4, 4, 4, RED);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadImageColors(mapPixels);   // Unload color array

    // UnloadTexture(cubicmap);        // Unload cubicmap texture
    // UnloadTexture(texture);         // Unload map texture
    // UnloadModel(model);             // Unload map model

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

//    UnloadImageColors(pixels);

    return 0;
}
