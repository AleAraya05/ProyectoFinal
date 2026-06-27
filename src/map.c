#include "raylib.h"
#include "map.h"

#include <stdio.h>

// Funcion que cargara y leera el mapa en 2D
void LoadMaze(MazeMap *map, MazeTexture *texture, const char *filename) {

    //Inicializar los conteos
    map->wallCount = 0;
    map->floorCount = 0;
    map->keySpawnCount = 0;

    // Recibe la imagen y la carga para su lectura
    Image imMap = LoadImage(filename);    

    if (imMap.data == NULL)
    {
        printf("ERROR: imagen no cargada\n");
    }

    // Almacena los pixeles por el recorrido para identificar las zonas
    Color *pixels = LoadImageColors(imMap);

    
    for (int y = 0; y < imMap.height; y++) {
        for (int x = 0; x < imMap.width; x++) {

            Color pixel = pixels[y * imMap.width + x];

            // Almacena las posiciones de las paredes
            if (ColorIsEqual(pixel, BLACK)) { 
                map->wallPlace[map->wallCount] = (Vector3){x, 1.0f, y};
                map->wallCount++;
            } 

            //Almacena lo demas como piso
            else { 
                map->floorPlace[map->floorCount] = (Vector3){x, 0.0f, y};
                map->floorCount++;
            }
            
            // Toma la ubicacion en el mapa destinada para ser el punto de aparicion (fue marcado con verde)
            if (pixel.r == 0 && pixel.g == 255 && pixel.b == 0) {
                map->playerSpawn = (Vector3){x, 0.5f, y};
            }

            // Ubicacion de la salida (marcada con rojo)
            if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0) {
                map->exitPos = (Vector3){x, 0.5f, y};
            }

            // Ubicacion del enemigo (marcado con azul)
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 255) {
                map->enemySpawn = (Vector3){x, 0.5f, y};
            }

            // Posibles ubicaciones de las llaves (marcado en amarillo)
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 0) {
                map->keySpawns[map->keySpawnCount] = (Vector3){x, 0.5f, y};
                map->keySpawnCount++;
            }

        }
    }

    //Cargar las texturas de las paredes, piso y techo
    texture->wallTexture = LoadTexture("resources/wall_texture.png"); 
    texture->floorTexture = LoadTexture("resources/floor_texture.png");
    texture->ceilingTexture = LoadTexture("resources/ceiling_texture.png");

    // Raylib crea la geometria de un cubo y se le asigna a su modelo
    Mesh wallMesh = GenMeshCube(1.0f, 2.0f, 1.0f);
    texture->wallModel = LoadModelFromMesh(wallMesh);

    texture->wallModel // Accede a la variable
    .materials[0] // Accede al primer material del modelo (textura)
    .maps[MATERIAL_MAP_DIFFUSE] // Se utiliza para modificar la textura principal
    .texture = texture->wallTexture; // Se le asigna la textura que se desea


    // Geometria de plano (del techo) y se asigna a su modelo
    Mesh ceilingMesh = GenMeshCube(1.0f, 0.1f, 1.0f);   
    texture->ceilingModel = LoadModelFromMesh(ceilingMesh);

    texture->ceilingModel
    .materials[0]
    .maps[MATERIAL_MAP_DIFFUSE]
    .texture = texture->ceilingTexture;


    // Geometria de plano (del piso) y se asigna a su modelo
    Mesh floorMesh = GenMeshCube(1.0f, 0.1f, 1.0f);
    texture->floorModel = LoadModelFromMesh(floorMesh);

    texture->floorModel
    .materials[0]
    .maps[MATERIAL_MAP_DIFFUSE]
    .texture = texture->floorTexture;

    
    UnloadImage(imMap);
    UnloadImageColors(pixels);
}



void DrawMaze(MazeMap *map, MazeTexture *texture) {
    for (int i = 0; i < map->wallCount; i++) {
        DrawModel(
            texture->wallModel,
            map->wallPlace[i],
            1.0f,
            WHITE
        );
    }

    for (int i = 0; i < map->floorCount; i++) {
        DrawModel(
            texture->floorModel,
            map->floorPlace[i],
            1.0f,
            WHITE
        );
    }
        
    for (int i = 0; i < map->floorCount; i++) {
        DrawModel(
            texture->ceilingModel,
            (Vector3) {map->floorPlace[i].x, 2.0f, map->floorPlace[i].z},
            1.0f,
            WHITE
        );
    }
}




