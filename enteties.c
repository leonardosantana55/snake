#include "enteties.h"


Field* Field_Init(int size_x, int size_y){

    Field *field = (Field *)malloc(sizeof(Field));
    if(field == NULL){
        return NULL;
    }

    field->tile_x = 0; //starting position
    field->tile_y = 0; //starting position
    field->tile_w = 16;
    field->tile_h = 16;

    //sets how many tiles the field has in each direction
    field->size_x = size_x / field->tile_w;
    field->size_y = size_y / field->tile_h;

    SDL_Rect a1 = {
        field->tile_x - field->tile_w, 
        field->tile_y - field->tile_h, 
        field->tile_w,
        field->tile_h
        };

    //init the positino of each tile based on a1
    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){

            field->tiles[i][j].x = a1.x + (a1.w * (j+1));
            field->tiles[i][j].y = a1.y + (a1.h * (i+1));
            field->tiles[i][j].w = a1.w;
            field->tiles[i][j].h = a1.h;

        }
    }

    //init the status of each tile on the field
    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){

            field->on_tile[i][j] = EMPTY;

        }
    }

    //init the address of each possible enteti in the field to 0
    for(int i=0; i<ENTETIES_MAX_SNAKES; i++){

        field->snakes_on_field[i] = 0;
    }

    for(int i=0; i<ENTETIES_MAX_WALLS; i++){

        field->walls_on_field[i] = 0;
    }

    for(int i=0; i<ENTETIES_MAX_FOOD; i++){

        field->food_on_field[i] = 0;
    }

    return field;
}


/******************************************************************************
*Function Description:
Checks the position of snakes and mark their position on the board
will be expanded to include food and walls
maybe add dynamic walls in the future

******************************************************************************/
void Field_Update(Field *field){
    int a = 0;
    int b = 0;

    //resets all status
    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){

            field->on_tile[i][j] = EMPTY;

        }
    }

    //look for each snakes position
    for(int i=0; i<ENTETIES_MAX_SNAKES; i++){

        if(field->snakes_on_field[i] != 0){
        
            for(int j=0; j < field->snakes_on_field[i]->size; j++){

                a = field->snakes_on_field[i]->tiles[j].y / field->tile_h;
                b = field->snakes_on_field[i]->tiles[j].x / field->tile_w;

                field->on_tile[a][b] = SNAKE;
//                printf("j: %d= a: %d, b: %d - ", j, a,b);

            }
//            printf("\n");
        }
    }


    //look for walls
    for(int i=0; i<ENTETIES_MAX_WALLS; i++){

        if(field->walls_on_field[i] != 0){

            for(int j=0; j < field->walls_on_field[i]->size; j++){

                a = field->walls_on_field[i]->tiles[j].y / field->tile_h;
                b = field->walls_on_field[i]->tiles[j].x / field->tile_w;

                field->on_tile[a][b] = WALL;
//                printf("j: %d= a: %d, b: %d - ", j, a,b);

            }
//            printf("\n");
        }
    }

    //look for food
    for(int i=0; i<ENTETIES_MAX_FOOD; i++){

        if(field->food_on_field[i] != 0){
        
                a = field->food_on_field[i]->tile.y / field->tile_h;
                b = field->food_on_field[i]->tile.x / field->tile_w;

                field->on_tile[a][b] = FOOD;
//                printf("j: %d= a: %d, b: %d - ", j, a,b);

//            printf("\n");
        }
    }
}


Snake* Snake_Init(Field *field){

    Snake *snake = (Snake *)malloc(sizeof(Field));
    if(snake == NULL){
        return NULL;
    }

    //init basic snakes properties
    snake->size = 3;
    // its the field size - the 4 outside walls - 1
    snake->max_size = ((field->size_x * field->size_y) - (4 * field->size_x)) - 1;
    snake->speed = 5.0;
    snake->speed_control_factor = 7.0;
    snake->speed_control = snake->speed_control_factor;
    snake->health = 1;
    snake->motion_direction = RIGHT;    // the starting moving direction
    snake->score = 0;

    snake->tile_x = field->tiles[field->size_x/2][field->size_x/2].x;    // the position of the snake depends on the coordinates of the field tiles
    snake->tile_y = field->tiles[field->size_y/2][field->size_y/2].y;
    snake->tile_w = field->tile_w;
    snake->tile_h = field->tile_h;

    //init the position of each tile of the snake
    for(int i=0; i<snake->size; i++){

        snake->tiles[i].x = snake->tile_x - (snake->tile_w * i);
        snake->tiles[i].y = snake->tile_y;
        snake->tiles[i].w = snake->tile_w;
        snake->tiles[i].h = snake->tile_h;

    }
    
    //make comunication possible betwheen objects
    //the snake being initiated tells its address to the field
    snake->field = field;

    for(int i=0; i<ENTETIES_MAX_SNAKES; i++){

        if(field->snakes_on_field[i] == 0){
            field->snakes_on_field[i] = snake;
            break;
        }

    }

    return snake;
}


void Snake_Move(Snake *snake){
    //move the head of the snake and copy the previous tile to the old head position and so on

    if (snake->speed_control < snake->speed){

        int colision = colisionDetection(snake->field, snake->tiles[0].x, snake->tiles[0].y, snake->motion_direction);

        switch(colision){

            case WALL:
                snake->health = 0;
                return;

            case SNAKE:
                snake->health = 0;
                return;

            case FOOD:
                snake->size++;
                snake->speed += 0.1;
                //here i reward the player for playing fast
                //the faster the snake, the higher the points
                //TODO: reward the player for cathing food near the walls
                snake->score += snake->speed * 100;
                snake->field->food_on_field[0]->health = 0;
                //what if a have many foods on field? the above approach would not work
                // i think that maybe i would need to pass the position of the snake,
                //and check every food to match its position
                break;

            default:
            snake->score++;
            snake->speed -= 0.001;
        }


        SDL_Rect temp_pre = snake->tiles[1];
        SDL_Rect temp = snake->tiles[0];

        switch(snake->motion_direction){

            case RIGHT:
                snake->tiles[0].x += snake->tile_w;
                break;

            case DOWN:
                snake->tiles[0].y += snake->tile_h;
                break;

            case LEFT:
                snake->tiles[0].x -= snake->tile_w;
                break;

            case UP:
                snake->tiles[0].y -= snake->tile_h;
                break;

        }

        //for loop starts on 1 because the head has moved already
        for(int i=1; i<snake->size; i++){

            temp_pre = snake->tiles[i];
            snake->tiles[i] = temp;
            temp = temp_pre;
            temp_pre = snake->tiles[i+1];

        }

        snake->speed_control = snake->speed_control_factor;
    }
    else{

        snake->speed_control -= 0.5;
    }
}


Wall* Wall_Init(Field *field, int size, int start_x, int start_y, int orientation){

    Wall* wall = (Wall *)malloc(sizeof(Wall));
    if(wall == NULL){
        return NULL;
    }

    wall->size = size;
    wall->orientation = orientation;
    wall->field = field;

    wall->tile_x = field->tiles[start_y][start_x].x;    // the position of the wall depends on the coordinates of the field tiles
    wall->tile_y = field->tiles[start_y][start_x].y;
    wall->tile_w = field->tile_w;
    wall->tile_h = field->tile_h;

    for(int i=0; i<size; i++){

        switch (orientation){

            case HORIZONTAL:
                wall->tiles[i].x = wall->tile_x + (wall->tile_w * i);
                wall->tiles[i].y = wall->tile_y;
                wall->tiles[i].w = wall->tile_w;
                wall->tiles[i].h = wall->tile_h;
                break;

            case VERTICAL:
                wall->tiles[i].x = wall->tile_x;
                wall->tiles[i].y = wall->tile_y + (wall->tile_h * i);
                wall->tiles[i].w = wall->tile_w;
                wall->tiles[i].h = wall->tile_h;
                break;

            case DIAGONAL:

                break;

        }
    }

    //make comunication possible betwheen objects
    //tell the field the address of the snakes on it
    wall->field = field;

    for(int i=0; i<ENTETIES_MAX_WALLS; i++){

        if(field->walls_on_field[i] == 0){
            field->walls_on_field[i] = wall;
            break;

        }
    }

    return wall;
}


void generateFoodPosition(Food* food){

    //generate a position and check if it is ocupied
    int min = 2;
    int max = food->field->size_x - 2;
    int x = randomIntGen(min, max) * food->field->tile_w;
    int y = randomIntGen(min, max) * food->field->tile_h;

    while (colisionDetection(food->field, x, y, NONE) != 0){

        x = randomIntGen(min, max) * food->field->tile_w;
        y = randomIntGen(min, max) * food->field->tile_h;

    }

    int b = x / food->field->tile_h;
    int a = y / food->field->tile_w;

    food->tile.x = food->field->tiles[a][b].x;
    food->tile.y = food->field->tiles[a][b].y;
}


Food* Food_Init(Field *field){

    Food* food = (Food *)malloc(sizeof(Food));
    if(food == NULL){
        return NULL;
    }

    food->health = 1;
    food->time_to_expire = 10;
    food->field = field;

    generateFoodPosition(food);
    food->tile.w = field->tile_h;
    food->tile.h = field->tile_w;

    //make comunication possible betwheen objects
    //tell the field the address of the foods on it
    for(int i=0; i<ENTETIES_MAX_FOOD; i++){

        if(field->food_on_field[i] == 0){
            field->food_on_field[i] = food;
            break;

        }
    }

    return food;
}


void Food_Spawn(Food *food){

    if (food->health == 0){

        generateFoodPosition(food);
        food->health = 1;
    }
}


int colisionDetection(Field *field, int x, int y, int direction){
    //this function gets x y pixel and uses division to get the a b index

    int a = 0;
    int b = 0;

    switch(direction){

        case RIGHT:
            b = (x / field->tile_w) + 1;
            a = y / field->tile_h;
            break;

        case DOWN:
            b = x / field->tile_w;
            a = (y / field->tile_h) + 1;
            break;

        case LEFT:
            b = (x / field->tile_w) - 1;
            a = y / field->tile_h;
            break;

        case UP:
            b = x / field->tile_w;
            a = (y / field->tile_h) - 1;
            break;

        default:
            b = x / field->tile_w;
            a = y / field->tile_h;
            break;
    }

    return field->on_tile[a][b];
}
