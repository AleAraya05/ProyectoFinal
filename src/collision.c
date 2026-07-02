#include "collision.h"
#include "raymath.h"

// Revision de colision con las paredes


// La pared al ser una coordenada en la deteccion original se percibia como el contacto del centro del jugador contra el centro del muro, por lo cual muchos
// videojuegos (e incluso el sistema que usa un ejemplo de raylib) es detectar el radio del jugador como un cilindro (un circulo en vista 2D) y los muros no
// detectarlos por su punto medio sino segun el punto donde esta la pared vista como un cubo (no como el punto que es)

bool CheckCollisionWithWalls(MazeMap *map, Vector3 pos) {
    
    const float playerRadius = 0.15f;            // Se establece el radio del jugador (se interpreta como un cilindro)

    // Recorrido por las paredes del laberinto
    for (int i = 0; i < map->wallCount; i++) {

        Vector3 wall = map->wallPlace[i];
        
        // Si la pared es un cubo de dimension 1, y el punto de esta se ubica en el medio, para medir los margenes de este se define a una distancia de 0.5 del medio
        // y por ende hay que medirlos en el eje x y en el z de cada muro.
        float minX = wall.x - 0.5f;             
        float maxX = wall.x + 0.5f;

        float minZ = wall.z - 0.5f;
        float maxZ = wall.z + 0.5f;

        // Devuelve el punto de la pared mas cercano al jugador (Clamp es funcion de raymath)
        float closestX = Clamp(pos.x, minX, maxX);
        float closestZ = Clamp(pos.z, minZ, maxZ);

        // Por medio de Pitagoras se mide la distancia entre los puntos del plano 
        float dx = pos.x - closestX;
        float dz = pos.z - closestZ;

        // Al no sacar la raiz de la distancia, mas bien esta y el radio se comparan al cuadrado
        float distanceSquared = dx*dx + dz*dz;
        const float playerRadiusSquared = playerRadius * playerRadius;

        if (distanceSquared < playerRadiusSquared) {
            return true;
        }

    }

    return false;
}