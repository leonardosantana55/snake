#ifndef RENDER
#define RENDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "enteties.h"


void renderField(Field *field, SDL_Renderer *renderer);

void renderSnake(Snake *snake, SDL_Renderer *renderer);

void renderWall(Wall *wall[], int size, SDL_Renderer *renderer);

int renderText(TTF_Font *font, const char *text, SDL_Renderer *renderer);


#endif
