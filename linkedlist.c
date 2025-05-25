#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "linkedlist.h"


/******************************************************************************
*Function Description:

    inits the variable of type LinkedList like this:

    LinkedList *mylist = (LinkedList *)malloc(sizeof(LinkedList));
    if(mylist == NULL){
        return -1;

    LinkedList_Init(mylist);

******************************************************************************/
LinkedList* LinkedList_Init(void){

    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if(list == NULL){
        return NULL;
    }

    list->size = 0;
    list->tail = NULL;
    list->head = NULL;

    return list;
}


/******************************************************************************
*Function Description:

Insert any data type in the list:
To insert in the middle you must inform the addres of the node rigth before
the desired location

To insert at the head pass NULL as the *node argument

To insert as if by value you have to alocate memory:

    for(int i = 0; i<15; i++){
        int* data = malloc(sizeof(int));
        *data = i;
        LinkedList_Insert(i_list, NULL, data);
    }


******************************************************************************/
int LinkedList_Insert(LinkedList *list, Node *node, const void *data){

    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    if(new_node == NULL){
        return -1;
    }

    //assign data to the new node
    new_node->data = (void *)data;

    //insertion at the head
    if (node == NULL){

        //handle insert when list is empty
        if (list->size == 0){
            list->tail = new_node;
        }

        new_node->next = list->head;
        list->head = new_node;
    }
    //insertion when node is not null
    else {
        //when the node thats been passed is in the tail
        if(node->next == NULL){
            list->tail = new_node;
        }

        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;

    return 0;

}


/******************************************************************************
*Function Description:

The **data argument is where the value removed is pointed to
To get it its necessary to know which data type the list holds:

    float *removed = (float *)malloc(sizeof(float));
    LinkedList_Remove(mylist, NULL, (void **)&removed);
    printf("removed: %.2f\n", *removed);

if the last two arguments are passed as NULL the last item is
removed and no data is retrieved

******************************************************************************/
void* LinkedList_Remove(LinkedList *list, Node *node){

    Node* old_node;
    Node* temp = list->head;
    void* removed;

    // removal from empty list is not allowed
    if (list->size == 0){
        return NULL;
    }

    if (node == NULL){
        //remove from the head

        //this is the data being removed
        removed = list->head->data;

        //this in the node being removed
        old_node = list->head;

        //now head is the previous one
        list->head = list->head->next;

        if (list->size == 1){
//            list->tail = NULL; // maybe i created a bug here
            list->tail = list->head;
        }

    }

    else{
        //remove specified node

        if (node->next == NULL){        // if is the last node

            for(int i=list->size; i>2; i--){
                temp = temp->next;
            }

            removed = list->tail->data;
            temp->next = NULL;
            list->tail = temp;

//            return -1;
        }
        else{                           // if its in the middle

            removed = node->next->data;
            old_node = node->next;
            node->next = node->next->next;

            if (node->next == NULL){
                list->tail = node;
            }
        }

    }

    free(old_node);
    list->size--;
    if (list->size == 0){
        list->head = NULL;
    }

    return removed;
}


/******************************************************************************
*Function Description:

Simply pass a linked list and voila :)

******************************************************************************/
void LinkedList_Destroy(LinkedList *list){

    int count = 0;
    while(list->size > 0){

        LinkedList_Remove(list, NULL);
        count++;

    }

    printf("%d items removed, list destroyed\n", count);

    memset(list, 0, sizeof(LinkedList));
}


void LinkedList_Print(LinkedList* list, char datatype){

    if (list == NULL || list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = list->head;

    printf("[");

    switch(datatype){

        case 'i':

            for(int i=list->size; i>0; i--){
                printf("%d", *(int*)(temp->data));
                if(i != 1){
                    printf(", ");
                }
                temp = temp->next;
            }
            break;

        case 'f':
        case 'd':

            for(int i=list->size; i>0; i--){
                printf("%f", *(double*)(temp->data));
                if(i != 1){
                    printf(", ");
                }
                temp = temp->next;
            }
            break;

        case 's':

            for(int i=list->size; i>0; i--){
                printf("%s", (char*)(temp->data));
                if(i != 1){
                    printf(", ");
                }
                temp = temp->next;
            }
            break;

        default:

            for(int i=list->size; i>0; i--){
                printf("%p", temp->data);
                if(i != 1){
                    printf(", ");
                }
                temp = temp->next;
            }
    }

    printf("]\n");
}

//this is how to add and dereference a value on the linkedlist
//vec3d* vec1 = (vec3d *)malloc(sizeof(vec3d));
//vec1->x = 5.0;
//vec1->y = 5.0;
//vec1->z = 5.0;
//
//LinkedList* mylist = LinkedList_Init();
//
//LinkedList_Insert(mylist, NULL, (void*)vec1);
//printf("%f", ((vec3d*)mylist->head->data)->x);


