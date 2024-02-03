#ifndef LIST
#define LIST

#include <stdbool.h>

typedef struct Node {
    void* data;
    struct Node* next;
} node_t;

typedef struct LinkedList {
    int length;
    node_t* head;
    node_t* tail;
} list_t;

list_t* create_list();
void list_insert(list_t* l, void* data);
void list_remove(list_t* l, void* data);
bool is_empty_list(list_t* l);
void list_foreach_element(list_t* l, void* app, void (*func)(void*, void*));
void free_list(list_t* l);

#endif