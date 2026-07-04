#ifndef GAME_KEY_H
#define GAME_KEY_H

#include "raylib.h"

#include "player.h"
#include "map.h"

// Caracteristicas de la llave
typedef struct {
    Model model;            // Carga como modelo la llave tipo .obj

    Vector3 position;       // Determina el punto del mapa donde se encontrara la llave

    bool collected;         // Revisa si la llave ya fue recolectada
    bool playerNearKey;     // Devuelve si el jugador se encuantra en el radio de la llave

} Key;

void keyInit(Key *key, MazeMap *map);

void keyUpdate(Key *key, Player *player);

void keyDraw(Key *key);

void keyDrawUI(Key *key);

void keyUnload(Key *key);


#endif