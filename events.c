#include "events.h"


void eventLogicQuit(SDL_Event* e, bool* quit){
    if(e->type == SDL_QUIT){
        *quit = true;
    }

}


void eventLogicKeyPrint(SDL_Event* e){
    if(e->type == SDL_TEXTINPUT){
        printf("%s\n", e->text.text);
    }
}


void eventLogicMoveSnake(SDL_Event* e, Snake* snake){
    if(e->type == SDL_KEYDOWN){

        switch (e->key.keysym.sym){

            case SDLK_RIGHT:
                snake->motion_direction = RIGHT;
                break;

            case SDLK_DOWN:
                snake->motion_direction = DOWN;
                break;

            case SDLK_LEFT:
                snake->motion_direction = LEFT;
                break;

            case SDLK_UP:
                snake->motion_direction = UP;
                break;
        }
    }
}
