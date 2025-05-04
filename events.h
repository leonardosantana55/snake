#ifndef EVENTS
#define EVENTS

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "enteties.h"
#include "game_state.h"

void eventLogicQuit(SDL_Event* e, bool* quit);

void eventLogicKeyPrint(SDL_Event* e);

int eventLogicMoveSnake(SDL_Event* e);

void eventLogicGamestate(SDL_Event* e, int* game_state, Field* field, Snake* snake);


#endif
