#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "player.h"
#include "map.h"
#include "key.h"
#include "exit.h"


// Se definen los posibles estados del juego
typedef enum {

    GAME_MENU,          // Pantalla menu
    GAME_CONTROLS,      // Pantalla de controles
    GAME_LOADING,       // Pantalla de carga
    GAME_PLAYING,       // Gameplay
    GAME_WIN,           // Pantalla de victoria
    GAME_OVER           // Pantalla de muerte

} GameState;


// Determina el estado de juego, asi como informacion correspondiente a estadisticas
typedef struct {

    GameState state;

    float timer;
    int keysCollected;

    Texture2D menuScreen;
    Texture2D winScreen;
    Texture2D gameOverScreen;

} Game;

// Funciones a usar
void gameInit(Game *game);

void gameChangeState(Game *game, GameState newState);

void gameUpdate(Game *game);

void gameStart(
    Game *game,
    Player *player,
    MazeMap *map,
    Key *key,
    ExitDoor *door
);

void gameDraw(Game *game);

void gameUnload(Game *game);

#endif 