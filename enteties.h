#ifndef ENTETIES
#define ENTETIES
#define ENTETIES_SIZE 128
#define ENTETIES_MAX_SNAKES 4
#define ENTETIES_MAX_WALLS 16
#define ENTETIES_MAX_FOOD 100

#include <SDL2/SDL.h>
#include "utils.h"

enum Direction {NONE, RIGHT, DOWN, LEFT, UP};

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

    //hold the address for each ententi. Is populated when a enteti is initiated
    struct Snake_ *snakes_on_field[ENTETIES_MAX_SNAKES];

    struct Wall_ *walls_on_field[ENTETIES_MAX_WALLS];

    struct Food_ *food_on_field[ENTETIES_MAX_FOOD];

} Field;

typedef struct Snake_{

    int size;
    int max_size;
    float speed;
    float speed_control;
    float speed_control_factor;
    int health;
    int motion_direction;
    int score;

    int tile_x; // starting position
    int tile_y; // starting position
    int tile_w;
    int tile_h;

    SDL_Rect tiles[ENTETIES_SIZE];      // i think this should be times 2
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

typedef struct Food_{
    
    int health;
    int time_to_expire;

    SDL_Rect tile;
    Field *field;

} Food;


Field* Field_Init(int size_x, int size_y);
void Field_Update(Field *field);

Snake* Snake_Init(Field *field);
void Snake_Move(Snake *snake);

Wall* Wall_Init(Field *field, int size, int start_x, int start_y, int orientation);

Food* Food_Init(Field *field);
void Food_Spawn(Food *food);

int colisionDetection(Field *field, int x, int y, int direction);

#endif
