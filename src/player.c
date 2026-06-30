#include "raymath.h"
#include "raylib.h"

#include "player.h"
#include "collision.h"
#include "map.h"

#include "stdio.h"

// Se inicializa al jugador con su informacion respectiva 
void playerInit(MazeMap *map, Player *player) {

    player->position = map->playerSpawn;
    player->speed = 1.0f;
    player->health = 1;
    
    player->yaw = 0;
    player->pitch = 0;

    player->camera.position = map->playerSpawn;

    player->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player->camera.fovy = 60.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;

}



// Obtiene la direccion de rotacion con el mouse
static void updateRotation(Player *player){

    Vector2 mouseDelta = GetMouseDelta();               // Obtiene el valor X y Y de movimiento del mouse desde el ultimo frame

    float mouseSensitivity = 0.005f;                      

    // Se establecen las posiciones con respecto al movimiento del mouse x la sensibilidad establecida
    player->yaw += mouseDelta.x * mouseSensitivity;      // En Raylib la derecha la detecta con numeros positivos (+)
    player->pitch -= mouseDelta.y * mouseSensitivity;    // En Raylib arriba lo detecta con numeros negativos (-)

    const float maxPitch = PI / 2.0f - 0.01f;            // Se establece angulo maximo de 89.99 grados (a los 90 empieza a girar la camara) 

    if (player->pitch > maxPitch) {
        player->pitch = maxPitch;                        // Se limmita el angulo maximo de vision
    }

    if (player->pitch < -maxPitch) {
        player->pitch = -maxPitch;                       // Se limita el angulo minimo de vision
    }

}



// 
static void calculateDirection(Player *player) {
    
    // Se utilizan seno y coseno ya que sus resultados siempre entraran en el rango de -1 y 1, los necesarios para determinar si la vista se
    // dirige hacia la izquierda o derecha, a 90 grados se establece el punto medio de vista, por lo cual:
    // cos(90) = 0 (centro), sen(90) = 1 (izquierda), -sen(90) =-1 (derecha)
    
    player->forward.x = cosf(player->yaw);      // x con coseno (este se considera el punto medio de la vista)
    player->forward.y = 0.0f;                   // y en 0 ya que la altura nunca se va a modificar (al menos no en esta version)
    player->forward.z = sinf(player->yaw);      // z con seno (perpendicular a x)


    player->right.x = -sinf(player->yaw);       // x con -seno (lado derecho de la vista)
    player->right.y = 0.0f;
    player->right.z = cosf(player->yaw);        // z con coseno (perpendicular a x)

    // Como se ve en este punto, como esta funcion unicamente modifica la posicion del jugador, no se utiliza el pitch ya que la direccion del movimiento siempre
    // queremos que sea sobre el suelo.
}



// Obtiene el movimiento ingresado por el usuario
static Vector3 movementInput (Player *player) {

    Vector3 movement = {0};

    if (IsKeyDown(KEY_W)) {                                 // W se usa para avanzar
        movement.x += player->forward.x;                    // Se suma el vector que dirige hacia adelante
        movement.z += player->forward.z;
    }

    if (IsKeyDown(KEY_A)) {                                 // A se usa para ir a la izquirda
        movement.x -= player->right.x;                      // Se resta el vector que dirige a la derecha
        movement.z -= player->right.z;  
    }

    if (IsKeyDown(KEY_S)) {                                 // S se usa para retroceder
        movement.x -= player->forward.x;                    // Se resta el vector que dirige hacia adelante
        movement.z -= player->forward.z; 
    }

    if (IsKeyDown(KEY_D)) {                                 // D se usa para ir a la derecha
        movement.x += player->right.x;                      // Se suma el vector que dirige a la derecha
        movement.z += player->right.z;    
    }

    // Viendo al respecto del tema, un error comun al implementar este tipo de funciones es que el movimiento diagonal es mas rapido
    // que el movimiento vectorial estandar (hacia una sola direccion es de 1, mezclando dos direcciones es de ~1.41), por lo que 
    // raymath tiene funciones para solucionar esto.

    if (Vector3Length(movement) > 0.0f) {               // Lo compara con cero (que no hay movimiento) por que si normalize recibe y divide un 0, el programa puede tener fallos
        
        movement = Vector3Normalize(movement);
    }
    return movement;
}

// player->speed * GetFrameTime();

// Analiza el movimiento del usuario y si este colisiona con un muro y actualiza su posicion
static void movePlayer(MazeMap *map, Player *player, Vector3 movement) {
    
    Vector3 nextPosition = player->position;                            // Crea una copia de la posicion actual para calcular la velocidad y colision

    // Aqui se obtiene el movimiento proximo tomando en cuenta 3 parametros: el movimiento ingresado, la velocidad establecida (unidades por segundo), y el tiempo transcurrido desde el ultimo frame
    nextPosition.x += movement.x * player->speed * GetFrameTime();      
    nextPosition.z += movement.z * player->speed * GetFrameTime();      

    // if (CheckCollisionWithWalls(map, nextPosition) == false) { 
    //     player->position = nextPosition;                                // En caso de no haber colision, la posicion actual se actualiza
    // } 


    bool collision = CheckCollisionWithWalls(map, nextPosition);

    if (!collision) {
        player->position = nextPosition;
    }
}



// Actualiza la direccion que mira la camara con respecto al movimiento
static void updateCamera(Player *player) {

    Vector3 lookDirection;                                              // Se define la direccion de la vista

    // Usando los mismos principios de calculateDirection() con sen() y cos() e implementando el pitch
    // En pitch 0 es vista al frente, 1 es vista en 90 hacia arriba y -1 es vista en 90 grados hacia abajo

    lookDirection.x = cosf(player->pitch) * cosf(player->yaw);          // Yaw se mantiene con el forward visto en calculateDirection() (constituye la misma direccion lateral), 

    lookDirection.y = sinf(player->pitch);                              // Seno del pitch calcula angulos como sen(90) = 1, la altura esperada

    lookDirection.z = cosf(player->pitch) * sinf(player->yaw);          // 

    player->camera.position = player->position;                         // Se posiciona el punto de camara junto al jugador

    player->camera.target = Vector3Add(player->camera.position, lookDirection);     // Establece el objetivo de la camara segun el vector de la posicion actual + la direccion de la mirada

}



void playerUpdate(MazeMap *map, Player *player) {

    updateRotation(player);                     // Chequea la rotacion del mouse
    
    calculateDirection(player);                 // Establece la direccion del teclado con respecto a la direccion de la vista

    Vector3 movement = movementInput(player);   // Recibe la direccion de movimiento ingresada

    movePlayer(map, player, movement);          // Mueve al personaje de lugar y chequea colisiones

    updateCamera(player);                       // Actualiza la camara del personaje

}





