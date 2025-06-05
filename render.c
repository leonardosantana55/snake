#include "render.h"

void renderField(Field *field, SDL_Renderer *renderer){

    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){
            SDL_SetRenderDrawColor(renderer, C2, C2, C2, 255);
            SDL_RenderFillRect(renderer, &field->tiles[i][j]);
            SDL_SetRenderDrawColor(renderer, C1, C1, C1, 255);
            SDL_RenderDrawRect(renderer, &field->tiles[i][j]);
        }
    }
}


void renderSnake(Snake *snake, SDL_Renderer *renderer){

    int r = C3 * snake->speed;
    int g = C3;
    int b = C3;

    for(int i=0; i<snake->size; i++){
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &snake->tiles[i]);
        SDL_SetRenderDrawColor(renderer, C1, C1, C1, 255);
        SDL_RenderDrawRect(renderer, &snake->tiles[i]);
    }
}


void renderFood(Food *food, SDL_Renderer *renderer){

        SDL_SetRenderDrawColor(renderer, C3, C3, C3, 255);
        SDL_RenderFillRect(renderer, &food->tile);
        SDL_SetRenderDrawColor(renderer, C1, C1, C1, 255);
        SDL_RenderDrawRect(renderer, &food->tile);
}


void renderWall(Wall *wall[], int size, SDL_Renderer *renderer){

    for(int i=0; i<size; i++){
        for(int j=0; j<wall[i]->size; j++){

            SDL_SetRenderDrawColor(renderer, C4, C4, C4, 255);
            SDL_RenderFillRect(renderer, &wall[i]->tiles[j]);
            SDL_SetRenderDrawColor(renderer, C1, C1, C1, 255);
            SDL_RenderDrawRect(renderer, &wall[i]->tiles[j]);

        }
    }
}


int renderText(TTF_Font *font, const char *text, int x, int y, SDL_Renderer *renderer){

    SDL_Color color = {255,255,255,255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        SDL_Log("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstrect = {x, y, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return 0;
}
