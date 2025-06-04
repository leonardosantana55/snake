#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

typedef struct vec3d_{
    float x;
    float y;
    float z;
} vec3d;
 
int main(){

    List* i_list = List_Init();
    void* removed;

    for(int i = 0; i<10; i++){
        int* data = malloc(sizeof(int));
        *data = i;
        List_Insert(i_list, NULL, data);
    }

    List_Print(i_list, 'i');

    
    for(int i=0; i<20; i++){

//        removed = List_Remove(i_list, i_list->tail);
        removed = List_Remove(i_list, NULL);
        List_Print(i_list, 'i');
        if (removed != NULL){
            printf("rem: %d\n", *(int*)removed);
        } 
    }

    printf("tail: %p, head: %p\n", i_list->tail, i_list->head);
    List_Destroy(i_list);
    List_Print(i_list, 'i');

    return 0;
}

