#ifndef MAP_H
#define MAP_H

#include <raylib.h>

#define MAX_TILES 15000

// Posiciones de aparicion, salida, enemigo y llaves, asi como piso y paredes
typedef struct {
    Vector3 playerSpawn;
    Vector3 exitPos;
    Vector3 enemySpawn;

    Vector3 keySpawns[10];

    Vector3 wallPlace[MAX_TILES];
    Vector3 floorPlace[MAX_TILES];

    int keySpawnCount;
    int wallCount;
    int floorCount;

} MazeMap;


/// Texturas para las paredes, techo y piso del mapa
typedef struct {     
    Model wallModel;
    Model ceilingModel;
    Model floorModel;
    
    Texture2D wallTexture;
    Texture2D ceilingTexture;
    Texture2D floorTexture;

} MazeTexture;

void LoadMaze(MazeMap *map, MazeTexture *texture, const char *filename);

void DrawMaze(MazeMap *map, MazeTexture *texture);

#endif