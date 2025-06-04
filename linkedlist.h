#ifndef LINKEDLIST
#define LINKEDLIST


typedef struct Node_{

    void *data;
    struct Node_ *next;

} Node;

typedef struct List_{

    int size;
    Node *tail;
    Node *head; // the head is what points to the body!!!

} List;

/******************************************************************************
                               Public interface
******************************************************************************/

List* List_Init(void);

void List_Destroy(List *list);

int List_Insert(List *list, Node *node, const void *data);

void* List_Remove(List *list, Node *node);

void List_Print(List* list, char datatype);

#endif
