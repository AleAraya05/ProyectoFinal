#ifndef EXIT_H
#define EXIT_H

#include "raylib.h"

#include "map.h"
#include "player.h"

typedef struct {
    Model doorModel; 
    Texture2D doorTexture;

    bool playerNearDoor;
    bool winMatch;

} ExitDoor;

void exitInit(ExitDoor *door, MazeMap *map);

void exitUpdate(ExitDoor *door, Player *player, MazeMap *map);

void exitDraw(ExitDoor *door, MazeMap *map);

void exitDrawUI(ExitDoor *door, Player *player);

void exitUnload(ExitDoor *door);


#endif