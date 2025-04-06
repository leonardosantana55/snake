#ifndef ENTETIES
#define ENTETIES
#define ENTETIES_SIZE 128
#define ENTETIES_MAX_SNAKES 4
#define ENTETIES_MAX_WALLS 16

#include <SDL2/SDL.h>

enum Direction {RIGHT, DOWN, LEFT, UP};

enum Entetie_name {EMPTY, SNAKE, FOOD, WALL};

enum Orientation {HORIZONTAL, VERTICAL, DIAGONAL};

typedef struct Field_{

    int size_x;
    int size_y;

    int tile_x;
    int tile_y;
    int tile_w;
    int tile_h;

    SDL_Rect tiles[ENTETIES_SIZE][ENTETIES_SIZE];

    //describe what enteti is on each tile
    //the function Field_Update uses it mark the position of each enteti on the field
    int on_tile[ENTETIES_SIZE][ENTETIES_SIZE];

    //hold the address for each snake inside the field
    //is populated when a snake is initiated
    struct Snake_ *snakes_on_field[ENTETIES_MAX_SNAKES];

    //hold the address for each wall inside the field
    //is populated when a wall is initiated
    struct Wall_ *walls_on_field[ENTETIES_MAX_WALLS];

} Field;

typedef struct Snake_{
    
    int size;
    int max_size;
    int speed;
    int health;

    int tile_x; // starting position
    int tile_y; // starting position
    int tile_w;
    int tile_h;

    SDL_Rect tiles[ENTETIES_SIZE];
    Field *field;

} Snake;

typedef struct Wall_{

    int size;
    int orientation;

    int tile_x; // starting position
    int tile_y; // starting position
    int tile_w;
    int tile_h;

    SDL_Rect tiles[ENTETIES_SIZE];
    Field *field;

} Wall;

void Field_Init(Field *field, int size_x, int size_y);

void Field_Update(Field *field);

void Snake_Init(Snake *snake, Field *field);

void Snake_Move(Snake *snake, int direction);

void Wall_Init(Wall *wall, Field *field, int size, int start_x, int start_y, int orientation);

int colisionDetection(Field *field, int x, int y, int direction);

#endif
