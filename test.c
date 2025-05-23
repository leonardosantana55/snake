#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

typedef struct vec3d_{
    float x;
    float y;
    float z;
} vec3d;
 
int main(){

    int a = 1;
    int b = 2;
    int c = 3;

    LinkedList* i_list = LinkedList_Init();

    LinkedList_Insert(i_list, NULL, &a);
    LinkedList_Insert(i_list, NULL, &b);
    LinkedList_Insert(i_list, NULL, &c);

    LinkedList_Print(i_list, 'i');
//    printf("%d\n", i_list->size);
//    printf("%dtail: \n", *(int*)i_list->tail->data);

//    void* data;
//    LinkedList_Remove(i_list, NULL, &data);
//    LinkedList_Print(i_list, 'i');
//
//    LinkedList_Remove(i_list, NULL, &data);
//    LinkedList_Print(i_list, 'i');
//
//    LinkedList_Remove(i_list, NULL, &data);
//    LinkedList_Print(i_list, 'i');

    void* data;
    LinkedList_Remove(i_list, i_list->tail, &data);
    LinkedList_Print(i_list, 'i');

    LinkedList_Remove(i_list, i_list->tail, &data);
    LinkedList_Print(i_list, 'i');

    LinkedList_Remove(i_list, i_list->tail, &data);
    LinkedList_Print(i_list, 'i');


//    printf("%d\n", i_list->size);

//    vec3d* vec1 = (vec3d *)malloc(sizeof(vec3d));
//    vec1->x = 2.0;
//    vec1->y = 2.0;
//    vec1->z = 2.0;
//
//    vec3d* vec2 = (vec3d *)malloc(sizeof(vec3d));
//    vec2->x = 3.0;
//    vec2->y = 3.0;
//    vec2->z = 3.0;
//
//    LinkedList* mylist = LinkedList_Init();
//
//    LinkedList_Insert(mylist, NULL, (void*)vec1);
//    LinkedList_Insert(mylist, NULL, (void*)vec1);
//
//    printf("%f\n", ((vec3d*)mylist->head->data)->x);
//    printf("%f\n", ((vec3d*)mylist->head->next->data)->x);
//    printf("tail: %f\n", ((vec3d*)mylist->tail->data)->x);
//
//    LinkedList_Print(mylist, NULL);
//
//    free(vec1);
//    free(vec2);
//    free(mylist);
    
    return 0;
}

