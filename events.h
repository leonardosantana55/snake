#ifndef EVENTS
#define EVENTS

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "enteties.h"

void eventLogicQuit(SDL_Event* e, bool* quit);

void eventLogicKeyPrint(SDL_Event* e);

void eventLogicMoveSnake(SDL_Event* e, Snake* snake);


#endif
