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



void eventLogicMoveSnake(SDL_Event* e, Snake* snake){
    if(e->type == SDL_KEYDOWN){

        switch (e->key.keysym.sym){

            case SDLK_RIGHT:
                if(snake->motion_direction != LEFT){

                    snake->motion_direction = RIGHT;
                }
                break;

            case SDLK_DOWN:
                if(snake->motion_direction != UP){

                    snake->motion_direction = DOWN;
                }
                break;

            case SDLK_LEFT:
                if(snake->motion_direction != RIGHT){

                    snake->motion_direction = LEFT;
                }
                break;

            case SDLK_UP:
                if(snake->motion_direction != DOWN){
                    snake->motion_direction = UP;
                }
                break;
        }
    }
}
