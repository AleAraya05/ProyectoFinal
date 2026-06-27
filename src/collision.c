#include "collision.h"
#include <math.h>

// Revision de colision con las paredes
bool CheckCollisionWithWalls(MazeMap *map, Vector3 pos) {
    
    // Recorrido por las paredes del laberinto
    for (int i = 0; i < map->wallCount; i++) {

        Vector3 wall = map->wallPlace[i];

        // Revisa la cercania a la pared en el eje x y z utilizando valor absoluto
        if (fabsf(pos.x - wall.x) < 0.35f && fabsf(pos.z - wall.z) < 0.5f) {
            return true;
        }
    }

    return false;
}