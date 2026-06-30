#include "collision.h"
#include <math.h>

// Revision de colision con las paredes

bool CheckCollisionWithWalls(MazeMap *map, Vector3 pos) {
    
    const float playerRadius = 0.35f;            // Se establece el radio del jugador

    // Recorrido por las paredes del laberinto
    for (int i = 0; i < map->wallCount; i++) {

        Vector3 wall = map->wallPlace[i];

        // Revisa la cercania a la pared en el eje x y z utilizando valor absoluto
        if (fabsf(pos.x - wall.x) < playerRadius && fabsf(pos.z - wall.z) < playerRadius) {
            return true;
        }
    }

    return false;
}