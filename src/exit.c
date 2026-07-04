#include "exit.h"

#include "raymath.h"


// Inicializa la salida
void exitInit(ExitDoor *door, MazeMap *map) {

    door->playerNearDoor = false;
    door->winMatch = false;

    door->doorTexture = LoadTexture("resources/door_texture.png");

    // Raylib crea la geometria de un cubo y se le asigna a su modelo
    Mesh doorMesh = GenMeshCube(1.0f, 2.0f, 1.0f);
    door->doorModel = LoadModelFromMesh(doorMesh);

    door->doorModel // Accede a la variable
    .materials[0] // Accede al primer material del modelo (textura)
    .maps[MATERIAL_MAP_DIFFUSE] // Se utiliza para modificar la textura principal
    .texture = door->doorTexture; // Se le asigna la textura que se desea

}

// Actualiza el estado de la salida
void exitUpdate(ExitDoor *door, Player *player, MazeMap *map) {

    const float doorInteractionDistance = 1.2f;          // Distancia minima para desplegar mensaje
    const float doorMinDistanceSqr = doorInteractionDistance * doorInteractionDistance; // Distancia minima para abrir la puerta al cuadrado (para la comparacion)

    float distanceFromDoorSqr = Vector3DistanceSqr(player->position, map->exitPos); // Distancia del jugador a la puerta (al cuadrado)

    // Verificacion de posibilidad de salida           
    door->playerNearDoor = distanceFromDoorSqr <= doorMinDistanceSqr;
    
    if (door->playerNearDoor) {

        if (IsKeyPressed(KEY_E) && player->hasKey) {

            door->winMatch = true;

        }
    }


}

// Carga los modelos y textura en el mapa
void exitDraw(ExitDoor *door, MazeMap *map) {

    DrawModel(
        door->doorModel,
        map->exitPos,
        1.0f,
        WHITE
    );

}


// Escribe el texto correspondiente al acercarse a la puerta
void exitDrawUI(ExitDoor *door, Player *player) {

    const char *textWarning = "Hace falta una llave...";      // Mensaje de falta de llave
    const char *textOpen = "[E] para abrir puerta";           // Mensaje para abrir puerta

    int fontSize = 25;                              // Tamano de letra
    const int marginBottom = 80;                    // Establecer una distancia de margen de la base de la pantalla
    
    int textWarningWidth = MeasureText(textWarning, fontSize);    // Medir el tamanio de un texto (para luego centrarlo en la pantalla)
    int textOpenWidth = MeasureText(textOpen, fontSize);

    if (!player->hasKey && door->playerNearDoor) {
        DrawText(textWarning, (GetScreenWidth()-textWarningWidth)/2, GetScreenHeight() - marginBottom, fontSize, RAYWHITE);
    }

    if (player->hasKey && door->playerNearDoor) {
        DrawText(textOpen, (GetScreenWidth()-textOpenWidth)/2, GetScreenHeight() - marginBottom, fontSize, RAYWHITE);
    }

}

void exitUnload(ExitDoor *door) {

    UnloadModel(door->doorModel);
    UnloadTexture(door->doorTexture);

}



