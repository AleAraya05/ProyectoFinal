# ProyectoFinal

# The Milkman (El Lechero)

## Descripcion del proyecto :

The Milkman es un videojuego de terror desarrollado en el lenguaje de programacion C utilizando la biblioteca Raylib.

El jugador se encuentra encerrado en un laberinto, el cual debera explorar para encontrar una llave y escapar del "Lechero"

Este proyecto fue desarrollado como trabajo final del curso "Programacion Bajo Plataformas Abiertas" de la UCR. En este se aplican los principios de programacion en C aprendidos a lo largo del curso, asi como investigacion independiente de la materia.

### Caracteristicas actuales

- Movimiento en primera persona
- Camara controlada por mouse
- Laberinto generado a partir de una imagen tipo .png personalizada
- Sistema de colision funcional
- Llave con aparicion aleatoria entre opciones determinadas
- Puerta de escape
- Pantalla de estado de juego (menu, controles, victoria y derrota)

### Caracteristicas pendientes

- IA del enemigo
- Implementacion de musica
- Implementacion de mist/fog

### Detalles a considerar

- Actualmente al ejecutar el juego, se imprimen las coordenadas del jugador como las de la llave en la terminal cada frame, esto con motivos de facilitar la demostracion. Para desactivar esta funcion, ingrese al archivo "key.c" y elimine o comente (colocando "//" al inicio de la linea) la informacion de la linea 47 a la 61

--- 

# Dependencias e instalacion

## Requisitos

- GCC
- CMake 3.24 o superior
- Git
- Raylib 6.0

### Linux (Arch Linux)

Instalar dependencias:

```bash
sudo pacman -S git cmake gcc raylib
```

### Ubuntu

Instalar CMake y Git
``` bash
sudo apt install build-essential cmake git
```

Instalar librerias requeridas por Raylib
```bash
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```


Clonar el repositorio:

```bash
git clone https://github.com/AleAraya05/ProyectoFinal
```

Entrar al proyecto:

```bash
cd ProyectoFinal
```

Crear carpeta de compilación:

```bash
mkdir build
cd build
```

Generar archivos de compilación:

```bash
cmake ..
```

Compilar:

```bash
cmake --build .
```

---

# Ejecución

Desde la carpeta `build` ejecutar:

```bash
./TheMilkman
```

*(Si el ejecutable tiene otro nombre, reemplazarlo por el correspondiente.)*

---

# Diseno del proyecto

El proyecto fue creado con una arquitectura tipo modulas, en la cual cada sistema es responsable de una funcionalidad distinta

- **game**: controla los estados de juego (menu, controles, partida, victoria, derrota)
- **map**: carga el mapa a partir de una imagen personalizada y dibuja el entorno en 3D
- **player**: controla movimiento del jugador y la camara, actualiza sus estados particulares y actualiza sus estadisticas
- **collision**: verifica la posicion del jugador y detecta su hay colision con el entorno
-**key**: controla la generacion, recoleccion y visualizacion de la llave
-**exit**: administra la salida y la condicion de victoria

Este formato modular fue pensado para liberar la sobrecarga de un solo archivo, permitiendo que este corra de forma fluida.

---

# Autor

- Alejandro Araya Corrales
