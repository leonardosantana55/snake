#ifndef LINKEDLIST
#define LINKEDLIST


typedef struct Node_{

    void *data;
    struct Node_ *next;

} Node;

typedef struct LinkedList_{

    int size;
    Node *tail;
    Node *head; // the head is what points to the body!!!

} LinkedList;

/******************************************************************************
                               Public interface
******************************************************************************/

LinkedList* LinkedList_Init(void);

void LinkedList_Destroy(LinkedList *list);

int LinkedList_Insert(LinkedList *list, Node *node, const void *data);

void* LinkedList_Remove(LinkedList *list, Node *node);

void LinkedList_Print(LinkedList* list, char datatype);

#endif
