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


void eventLogicGamestate(SDL_Event* e, int* game_state, Field* field, Snake* snake){
     if(e->type == SDL_KEYDOWN){
         switch (e->key.keysym.sym){
            case SDLK_SPACE:
                Snake_Start(snake);
                *game_state = GAME_START;
         }
     }
}



int eventLogicMoveSnake(SDL_Event* e){

    int direction = NONE;
    if(e->type == SDL_KEYDOWN){

        switch (e->key.keysym.sym){

            case SDLK_RIGHT:
                direction = RIGHT;
                break;

            case SDLK_DOWN:
                direction = DOWN;
                break;

            case SDLK_LEFT:
                direction = LEFT;
                break;

            case SDLK_UP:
                direction = UP;
                break;
        }
    }
    return direction;
}
