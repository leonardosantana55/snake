#ifndef MY_LIST
#define MYLIST


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

void LinkedList_Init(LinkedList *list);

void LinkedList_Destroy(LinkedList *list);

int LinkedList_Insert(LinkedList *list, Node *node, const void *data);

int LinkedList_Remove(LinkedList *list, Node *node, void **data);

#endif
