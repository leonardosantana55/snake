//To build a Snake-like game, you need to understand and implement several key data structures and algorithms. Here’s a structured overview:
//Data Structures
//Linked List:
//Use a linked list to represent the snake's body. Each segment of the snake can be a node in the linked list, allowing for efficient growth and movement. This structure makes it easy to add new segments when the snake eats food and remove the tail segment when it moves13.
//Queue:
//A queue can also be used to manage the snake's segments. You can enqueue new segments at the head and dequeue from the tail, which simplifies the logic for moving the snake and managing its length24.
//2D Array/Grid:
//Implementing a 2D array can help represent the game board. Each cell in the array can hold information about whether it contains food, is empty, or is occupied by a segment of the snake56.
//Cell Class:
//Create a Cell class to represent each point on the board, storing its state (empty, food, or part of the snake). This class can also include methods to manage interactions with food and walls3.
//Algorithms
//Movement Logic:
//Implement algorithms to handle user input for changing the snake's direction. The movement should update the position of the head based on its current direction and manage tail movement accordingly4.
//Collision Detection:
//Write functions to detect collisions with walls or the snake’s own body, which will end the game if detected34.
//Food Generation:
//Create algorithms for randomly placing food on the grid and ensuring it does not overlap with the snake's body45.
//Game Loop:
//Establish a game loop that continuously updates the game state, processes user input, checks for collisions, and renders the game graphics.
//Scoring System:
//Implement a scoring system that increases as the snake eats food, providing feedback to players on their performance


#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#include "enteties.h" //change to ententies.H
#include "utils.h"

// its a breeze building this program on linux or windows 
#ifdef _WIN32
#define XMAIN WinMain
#elif __linux__
#define XMAIN main
#endif


//Global variables
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
SDL_Window* gWindow = NULL;
SDL_Surface* gWindow_surface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool initSDL(){
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else{
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ){
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ){
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                else{
                    //Get window surface
                    gWindow_surface = SDL_GetWindowSurface( gWindow );
                }
            }
        }
    }

    return success;
}


SDL_Texture* loadTexture(char* file_path){
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(file_path);
    if(loadedSurface == NULL){
        printf( "Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError() );
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


bool loadMedia(char* file_path, SDL_Surface** surface){
    bool success = true;

    SDL_Surface* temp_surface = NULL;
    temp_surface = IMG_Load(file_path);

    if( temp_surface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError() );
    }
    else{
        // this is used for optimization
        *surface = SDL_ConvertSurface(temp_surface, gWindow_surface->format, 0);
        SDL_FreeSurface(temp_surface);

        if(*surface == NULL){
            printf( "Unable to load image %s! SDL Error: %s\n",
            file_path, SDL_GetError() );
            success = false;
        }
    }

    return success;
}


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


void closeSDL(){
    //Dealocate Surface
    SDL_FreeSurface(gWindow_surface);
    gWindow_surface = NULL;

    //Destroy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    //Destroy texture
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow_surface = NULL;

    //Quit SDL Subsystems
    SDL_Quit();
}


void renderField(Field *field){
    
    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(gRenderer, &field->tiles[i][j]);
            SDL_SetRenderDrawColor(gRenderer, 0xF0, 0xF0, 0xF0, 0xF0);
            SDL_RenderDrawRect(gRenderer, &field->tiles[i][j]);
        }
    }

}


void renderSnake(Snake *snake){

    for(int i=0; i<snake->size; i++){
        SDL_SetRenderDrawColor(gRenderer, 0x50, 0x50, 0x50, 0x50);
        SDL_RenderFillRect(gRenderer, &snake->tiles[i]);
        SDL_SetRenderDrawColor(gRenderer, 0xF0, 0xF0, 0xF0, 0xF0);
        SDL_RenderDrawRect(gRenderer, &snake->tiles[i]);
    }
}


void renderWall(Wall *wall[], int size){

    for(int i=0; i<size; i++){
        for(int j=0; j<wall[i]->size; j++){

            SDL_SetRenderDrawColor(gRenderer, 0x90, 0x30, 0xF0, 0xF0);
            SDL_RenderFillRect(gRenderer, &wall[i]->tiles[j]);
            SDL_SetRenderDrawColor(gRenderer, 0xF0, 0xF0, 0xF0, 0xF0);
            SDL_RenderDrawRect(gRenderer, &wall[i]->tiles[j]);

        }
    }
}


int XMAIN(){
    initSDL();
    SDL_Event e;


    // init game enteties
    Field *field = (Field *)malloc(sizeof(Field));
    if(field == NULL){
        return -1;
    }
    Field_Init(field, 32, 32);

    Snake *snake = (Snake *)malloc(sizeof(Field));
    if(snake == NULL){
        return -1;
    }
    Snake_Init(snake, field);

    Wall *outside_walls[4];
    for (int i=0; i<4; i++){
        outside_walls[i] = (Wall *)malloc(sizeof(Wall));
        if(outside_walls[i] == NULL){
            return -1;
        }
    }
    Wall_Init(outside_walls[0], field, 32, 0, 0, HORIZONTAL);
    Wall_Init(outside_walls[1], field, 32, 0, 31, HORIZONTAL);
    Wall_Init(outside_walls[2], field, 32, 0, 0, VERTICAL);
    Wall_Init(outside_walls[3], field, 32, 31, 0, VERTICAL);

    //init game utils
    Fps *fps = (Fps *)malloc(sizeof(Fps));
    if(field == NULL){
        return -1;
    }
    Fps_Init(fps);

    int control = 0; // quick hack
    bool prin = false;


    // main loop
    bool quit = false;
    while(!quit){
        fps->time_start = SDL_GetTicks();


        // event logic loop
        while(SDL_PollEvent(&e)){
            eventLogicQuit(&e, &quit);
            eventLogicKeyPrint(&e);
        }

        //game logic
        if(control > 10){
            Snake_Move(snake, DOWN);
            control = 0;
            prin = true;

        }
        else{
            control++;
        }

        Field_Update(field);

        if(prin){

            for(int i=0; i<field->size_x; i++){
                for(int j=0; j<field->size_y; j++){

                   printf("%d ", field->on_tile[i][j]);

                }
                printf("\n");
            }
            printf("\n");
            prin = false;

        }


        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear( gRenderer );


        // render game elements
        renderField(field);
        renderSnake(snake);
        renderWall(outside_walls, 4);


        //Update screen
        SDL_RenderPresent( gRenderer );


        // control frame rate
        Fps_Measure(fps);
//        printf("fps: %.2f\n", fps->fps);



    }

    closeSDL();
    return 0;
}

//TODO: colision detection
//colorscheme
//random position food generator
//control logic
//
