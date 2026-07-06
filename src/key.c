#include "key.h"

#include "raymath.h"

#include <stdio.h>




// Inicializa la llave con su informacion respectiva
void keyInit(Key *key, MazeMap *map) {

    // key->model = LoadModel("resources/MyFirstKey.obj");     // Se carga el modelo de la llave

    // Temporal por error de carga del modelo
    Mesh cube = GenMeshCube(0.3f, 0.3f, 0.3f);
    key->model = LoadModelFromMesh(cube);

    keyReset(key, map);
}



// Establece los datos iniciales para empezar una partida
void keyReset(Key *key, MazeMap *map) {

    int spawnKeyIndex = GetRandomValue(0, map->keySpawnCount - 1);  // Se randomiza la locacion de la llave

    key->position = map->keySpawns[spawnKeyIndex];          // Se almacena posicion de spawn de la llave

    key->collected = false;                                 // Se asigna el valor al elemento tipo bool
    key->playerNearKey = false;

}



// Actualiza la informacion de la llave
void keyUpdate(Key *key, Player *player) {

    const float keyMinimumDistance = 0.7f;          // Distancia minima para recoger la llave
    const float keyMinDistanceSqr = keyMinimumDistance * keyMinimumDistance; // Distancia minima para recoger la llave al cuadrado (para la comparacion)

    float distanceFromKeySqr = Vector3DistanceSqr(player->position, key->position); // Distancia del jugador a la llave (al cuadrado)


    printf(
        "Jugador: (%.2f, %.2f, %.2f) | Llave: (%.2f, %.2f, %.2f) | Dist²: %.3f | hasKey: %d\n",
        player->position.x,
        player->position.y,
        player->position.z,

        key->position.x,
        key->position.y,
        key->position.z,

        distanceFromKeySqr,

        player->hasKey

    );


    // Verificar si la llave fue recogida
    if (key->collected) {
        return;
    }


    // Verificacion si la llave no ha sido recogida            
    key->playerNearKey = distanceFromKeySqr <= keyMinDistanceSqr;
    if (key->playerNearKey) {

        if (IsKeyPressed(KEY_E)) {
            key->collected = true;
            player->hasKey = true;
        }
    }

}


// Dibuja el modelo de la llave
void keyDraw(Key *key) {

    if (!key->collected) {
        DrawModel(key->model, key->position, 0.3f, WHITE);    
    }
}


// Dibuja el texto al acercarse a la llave
void keyDrawUI(Key *key) {

    const char *text = "[E] para tomar llave";      // Mensaje para recojer llave
    int fontSize = 25;                              // Tamano de letra
    const int marginBottom = 80;                    // Establecer una distancia de margen de la base de la pantalla
    int textWidth = MeasureText(text, fontSize);    // Medir el tamanio de un texto (para luego centrarlo en la pantalla)

    if (!key->collected && key->playerNearKey) {
        DrawText(text, (GetScreenWidth()-textWidth)/2, GetScreenHeight() - marginBottom, fontSize, RAYWHITE);
    }
}

// Libera la memoria de la llave
void keyUnload(Key *key) {

    UnloadModel(key->model);

}
