#ifndef RENDER
#define RENDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "enteties.h"

enum Colors {
    C1 = 255/255,
    C2 = 255/8,
    C3 = 255/4,
    C4 = 255/2
};

void renderField(Field *field, SDL_Renderer *renderer);

void renderSnake(Snake *snake, SDL_Renderer *renderer);

void renderFood(Food *food, SDL_Renderer *renderer);

void renderWall(Wall *wall[], int size, SDL_Renderer *renderer);

int renderText(TTF_Font *font, const char *text, int x, int y, SDL_Renderer *renderer);


#endif
