#include "player.h"
#include "collision.h"
#include "map.h"

void playerInit(MazeMap *map, Player *player) {

    player->position = map->playerSpawn;
    player->speed = 1.0f;
    player->health = 1;
    
    player->camera.position = map->playerSpawn;

    player->camera.target = (Vector3){                      // Direccion que mira la camara (se establece en x+1, un  punto de distancia del jugador)
        map->playerSpawn.x + 1.0f,     
        map->playerSpawn.y,
        map->playerSpawn.z
    };

    player->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player->camera.fovy = 60.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;

}


// Obtiene el movimiento ingresado por el usuario
static void movementInput (Player *player, Vector3 *nextPosition) {

    if (IsKeyDown(KEY_W)) {                                 // W se usa para avanzar
        nextPosition->x += player->speed * GetFrameTime();   // Se escribe la direccion a avanzar
    }

    if (IsKeyDown(KEY_A)) {                                 // A se usa para ir a la izquirda
        nextPosition->z -= player->speed * GetFrameTime();   
    }

    if (IsKeyDown(KEY_S)) {                                 // S se usa para retroceder
        nextPosition->x -= player->speed * GetFrameTime();   
    }

    if (IsKeyDown(KEY_D)) {                                 // D se usa para ir a la derecha
        nextPosition->z += player->speed * GetFrameTime();   
    }
}


// Analiza el movimiento del usuario y si este colisiona con un muro y actualiza su posicion
static void movePlayer(MazeMap *map, Player *player, Vector3 nextPosition) {
    
    if (CheckCollisionWithWalls(map, nextPosition) == false) {
        player->position = nextPosition;

    } 
}

// Actualiza la direccion que mira la camara con respecto al movimiento
static void updateCamera(Player *player){
    player->camera.target = (Vector3){                      
        player->position.x+ 1.0f,     
        player->position.y,
        player->position.z
    };

    player->camera.position = (Vector3){                      
        player->position.x,     
        player->position.y,
        player->position.z
    };
}


void playerUpdate(MazeMap *map, Player *player) {

    Vector3 nextPosition = player->position;                // Obtener la proxima posicion del jugador para verificar si hay colision

    movementInput(player, &nextPosition);

    movePlayer(map, player, nextPosition);

    updateCamera(player);

}





