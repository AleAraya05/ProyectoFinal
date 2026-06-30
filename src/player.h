#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"
#include "collision.h"

// Caracteristicas para el jugador
typedef struct {
    Vector3 position;
    Camera3D camera;

    float speed;
    int health;

    Vector3 forward;    // Movimiento frontal
    Vector3 right;      // Movimiento lateral

    float yaw;          // Rotacion horizontal
    float pitch;        // Rotacion vertical
} Player;

// Funciones a usar
void playerInit(MazeMap *map, Player *player);
void playerUpdate(MazeMap *map, Player *player);


#endif

// Aqui lo apunto por cuestiones de recordar ya que me costo bastante investigar al respecto:
// (esta informacion se basa en un resumen que me hace google al respecto)
//
// Yaw y pitch son terminos que se utilizaban en fisica y aviacion y en este contexto describen el movimiento visual de la camara
// Pitch se refiera a arriba y abajo, Yaw a izquierda y derecha o mas entendible, Pitch es rotacion vertical y Yaw rotacion horizontal
//
// Por lo cual para obtener este modo de vision se necesita hacer la aplicacion matematica de estos utilizando funciones trigonometricas
// como seno y coseno para obtener un vector forward (adelante) que representa la direccion a la que se esta mirando
//
// Aqui he de admitir que ocupe ayuda de IA para poder comprender realmente como funciona y realizar el Yaw y Pitch correctamente
//
// Otro tipo de implementacion mas automatizada es la funcion UpdateCamera() de raylib.
