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
void LinkedList_Init(LinkedList *list){

    list->size = 0;
    list->tail = NULL;
    list->head = NULL;

    return;
}


/******************************************************************************
*Function Description:

Insert any data type in the list
To insert at the head pass NULL as the *node argument
To insert anywhere do it like this:

    int index = 0;
    Node *index_adr = NULL;
    for(int i=0; i<index; i++){
        index_adr = mylist->head->next;
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
        if (list->size == 0){
            //handle insert when list is empty
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
int LinkedList_Remove(LinkedList *list, Node *node, void **data){

    Node *old_node;

    // removal from empty list is not allowed
    if (list->size == 0){
        return -1;
    }

    if (node == NULL){
        //remove from the head

        *data = list->head->data;
        old_node = list->head;
        list->head = list->head->next;

        if (list->size == 1){
            list->tail = NULL;
        }

    }

    else{
        //remove specified node

        if (node->next == NULL){
            //to remove last item pass NULL instead
            return -1;
        }

        *data = node->next->data;
        old_node = node->next;
        node->next = node->next->next;

        if (node->next == NULL){
            list->tail = node;
        }

    }

    free(old_node);

    list->size--;

    return 0;
}


/******************************************************************************
*Function Description:

Simply pass a linked list and voila :)

******************************************************************************/
void LinkedList_Destroy(LinkedList *list){

    void *removed;

    int count = 0;
    while(list->size > 0){

        LinkedList_Remove(list, NULL, (void **)&removed);
        count++;

    }

    printf("%d items removed, list destroyed\n", count);

    memset(list, 0, sizeof(LinkedList));
}
