#ifndef COLLISION_H
#define COLLISION_H

#include "map.h"      
#include "raylib.h"   

// Funcion que se utilizara para revisar las colisiones
bool CheckCollisionWithWalls(MazeMap *map, Vector3 pos);

#endif