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

#include "enteties.h"
#include "utils.h"
#include "events.h"
#include "render.h"

// its a breeze building this program on linux or windows 
#ifdef _WIN32
#define XMAIN WinMain
#elif __linux__
#define XMAIN main
#endif


//Global variables
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;
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

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
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


enum Game_state {START_SCREEN, GAME_START, GAME_OVER, RECORD_SCREEN};


int XMAIN(){
    initSDL();
    SDL_Event e;


    // init game enteties
    Field *field = Field_Init(SCREEN_WIDTH, SCREEN_HEIGHT);

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
    Wall_Init(outside_walls[0], field, field->size_x, 0, 0, HORIZONTAL);
    Wall_Init(outside_walls[1], field, field->size_x, 0, field->size_x-1, HORIZONTAL);
    Wall_Init(outside_walls[2], field, field->size_y, 0, 0, VERTICAL);
    Wall_Init(outside_walls[3], field, field->size_y, field->size_y-1, 0, VERTICAL);

    //Wall *outside_walls[4];
    //outside_walls[0] = Wall_Init()


    //init game utils
    Fps *fps = (Fps *)malloc(sizeof(Fps));
    if(field == NULL){
        return -1;
    }
    Fps_Init(fps);


    //init font
    TTF_Font* font = TTF_OpenFont("assets/font/poxel/poxel-font.ttf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        return 1;
    }


    // quick hack section
//    int control = 0;
//    bool prin = false;

    // main loop
    bool quit = false;
    int game_state = GAME_START;

    char fps_string[5];
//    int match_score = 0;

    while(!quit){

        sprintf(fps_string, "%.2f", fps->fps);    // updates fps_string
        fps->time_start = SDL_GetTicks();

        switch(game_state){

            case GAME_START:

                // event logic loop
                while(SDL_PollEvent(&e)){

                    eventLogicMoveSnake(&e, snake);
                    eventLogicQuit(&e, &quit);
                    eventLogicKeyPrint(&e);
                }

                //game logic

                Snake_Move(snake);
                Field_Update(field);
                if(snake->health == 0){
                    game_state = GAME_OVER;
                }


                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderClear( gRenderer );


                // render game elements
                renderField(field, gRenderer);
                renderSnake(snake, gRenderer);
                renderWall(outside_walls, 4, gRenderer);
                renderText(font, fps_string, gRenderer);
                break;

            case GAME_OVER:
                printf("GAME OVER!\n");
                quit = true;
                break;
        }


        //Update screen
        SDL_RenderPresent( gRenderer );


        // control frame rate
        Fps_Measure(fps);
//        printf("fps: %.2f\n", fps->fps);



    }

    closeSDL();
    return 0;
}

//TODO:
//color blink effect
//
//colorscheme
//random position food generator
//scoring system
//colision logic
//change field->size_x to field->ntiles_x;
//add some functionability that makes use of exponential back factor: {initial delay} * (2 ^ ({current attempt number} - 1)) = backoff factor
//finish refactor of enteties init
//refactor SDL functions, init destroy, loadimg etc
//game over if snake colides with snakes body


//        if(prin){
//
//            for(int i=0; i<field->size_x; i++){
//                for(int j=0; j<field->size_y; j++){
//
//                   printf("%d ", field->on_tile[i][j]);
//
//                }
//                printf("\n");
//            }
//            printf("\n");
//            prin = false;
//
//        }
