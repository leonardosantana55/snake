#include <SDL2/SDL.h>
#include "utils.h"

void Fps_Init(Fps *fps){

    fps->time_start = 0;
    fps->time_end = 0;
    fps->elapsed = 0;
    fps->timer = 0;
    fps->frames = 0;
    fps->fps = 0;
    fps->desired_fps = 60;
    fps->surplus = 0;

}


void Fps_Measure(Fps *fps){

    fps->time_end = SDL_GetTicks();
    fps->elapsed = fps->time_end - fps->time_start;

    //measure surplus for control with SDL_Delay
    fps->surplus = ((1000/fps->desired_fps)) - fps->elapsed;

    // delay a little for each frame to achieve desired fps
    if(fps->surplus > 0){
        SDL_Delay(fps->surplus);
    }

    //measure fps
    fps->time_end = SDL_GetTicks();
    fps->elapsed = fps->time_end - fps->time_start;

    fps->timer += fps->elapsed;
    fps->frames++;

    if(fps->timer >= 1000){
        fps->fps = ((double)fps->frames / (double)fps->timer)*1000;
        fps->frames = 0;
        fps->timer -= 1000;
    }

}
