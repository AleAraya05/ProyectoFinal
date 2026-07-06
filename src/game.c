#include "game.h"


// Inicializa la informacion global del juego
void gameInit(Game *game) {

    game->state = GAME_MENU;                // Se inicia en el menu principal

    game->timer = 0.0f;                     // Se inicia el conteo de tiempo en 0

    game->menuScreen = LoadTexture("resources/menuScreen.png");             // Carga la pantalla del menu

    game->winScreen = LoadTexture("resources/winScreen.png");               // Carga la pantalla de victoria

    game->gameOverScreen = LoadTexture("resources/gameOverScreen.png");     // Carga la pantalla de muerte

}



// Cambia el estado del juego
void gameChangeState(Game *game, GameState newState) {

    game->state = newState;                 // Recibe el estado de juego a cambiar

}



// Actualiza el estado de juego (en especial el estado playing)
void gameUpdate(Game *game) {

    if (game->state == GAME_PLAYING) {

        game->timer += GetFrameTime();      // Conteo del tiempo transcurrido desde el inicio de la partida
    }

}



// Se reciben los parametros necesarios para iniciar una nueva partida
void gameStart(Game *game, Player *player, MazeMap *map, Key *key, ExitDoor *door) {

    game->timer = 0.0f;                     // Reinicia el conteo de tiempo

    // Se usan las funciones que establecen las condiciones iniciales de partida
    playerReset(map, player);               
    keyReset(key, map);
    exitReset(door);

    gameChangeState(game, GAME_PLAYING);    // Cambia el estado de juego a "PLAYING"

}


// Carga las imagenes de los diferentes estados de juego
void gameDraw(Game *game) {

    int totalSeconds = (int)game->timer;    // Timer es un float -> int

    int minutes = totalSeconds / 60;        // Obtiene los minutos segun el timer
    float seconds = totalSeconds %60;       // Obtiene los segundos segun el timer

    const char *timeText = TextFormat("Tiempo: %02i:%02i", minutes, seconds); // Despues de buscar es el formato que mejor simula un cronometro
    int fontSize = 25;

    switch (game->state)
    {
        case GAME_MENU:

            DrawTexture(game->menuScreen, 0, 0, WHITE);

            DrawText("Press [ENTER] to Play", GetScreenWidth()/4, GetScreenHeight()/2, fontSize, RAYWHITE);

            DrawText("Press [C] for controls", GetScreenWidth()/4, (GetScreenHeight()/4) *3, fontSize, RAYWHITE);

            break;

        case GAME_WIN:

            DrawTexture(game->winScreen, 0, 0, WHITE);

            DrawText("Press [ENTER] to return", GetScreenWidth()/8, (GetScreenHeight()/2) +10, fontSize, WHITE);

            DrawText(timeText, GetScreenWidth()/8, (GetScreenHeight()/2) -10, fontSize, WHITE);

            break;

        case GAME_OVER:

            DrawTexture(game->gameOverScreen, 0, 0, WHITE);

            DrawText("Press [ENTER] to return", (GetScreenWidth()/4) *3, GetScreenHeight()/2, fontSize, WHITE);

            DrawText(timeText, GetScreenWidth()/8, GetScreenHeight()/2, fontSize, WHITE);

            break;

        case GAME_CONTROLS:

            DrawTexture(game->menuScreen, 0, 0, WHITE);

            DrawText("W A S D      Move", GetScreenWidth()/8, GetScreenHeight()/2, fontSize, RAYWHITE);
            DrawText("Mouse        Look around",  GetScreenWidth()/8, GetScreenHeight()/2 +30, fontSize, RAYWHITE);
            DrawText("E            Interact",  GetScreenWidth()/8, GetScreenHeight()/2 +60, fontSize, RAYWHITE);
            DrawText("F11          Full screen",  GetScreenWidth()/8, GetScreenHeight()/2 +90, fontSize, RAYWHITE);
            DrawText("ESC          Exit game",  GetScreenWidth()/8, GetScreenHeight()/2 +120, fontSize, RAYWHITE);
            DrawText("Press [ENTER] to return", (GetScreenWidth()/8) *5, GetScreenHeight()/2 +120, fontSize, RAYWHITE);

            break;

        default:
            break;
    }

}



// Libera los recursos
void gameUnload(Game *game) {

    UnloadTexture(game->menuScreen);
    UnloadTexture(game->winScreen);
    UnloadTexture(game->gameOverScreen);    

}

