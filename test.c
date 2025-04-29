#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
 

int randomEvenNumberGenerator(int min, int max){

    int random_num = rand() % max + min;

    while( random_num % 2 != 0 ){

        random_num = rand() % max + min;
    }

    return random_num;
}

int main(){

    int run = 1;
    srand(time(NULL));

    while(run){

        int random_int = randomEvenNumberGenerator(0, 55);
        printf("Random number:%d\n", random_int);

    }
    return 0;
}
