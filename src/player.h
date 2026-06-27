#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"
#include "collision.h"

// Caracteristicas para el jugador
typedef struct {
    Vector3 position;
    Vector3 direction;
    Camera3D camera;
    float speed;
    int health;
} Player;

// Funciones a usar
void playerInit(MazeMap *map, Player *player);
void playerUpdate(MazeMap *map, Player *player);


#endif

