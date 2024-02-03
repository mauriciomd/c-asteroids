#include <stdlib.h>
#include "linkedlist.h"

list_t* create_list() {
    list_t* list = (list_t*) malloc(sizeof(list_t));
    list->length = 0;
    list->head = NULL;

    return list;
}

void list_insert(list_t* l, void* data) {
    node_t* node = (node_t*) malloc(sizeof(node_t));
    node->data = data;
    
    if (l->head == NULL) {
        l->head = node;
    } else {
        l->tail->next = node;
    }

    l->length++;
    l->tail = node;
}

void list_remove(list_t* l, void* data) {
    if (l == NULL || l->head == NULL)
        return;

    node_t* node = l->head;
    node_t* prev = NULL;

    while (node != NULL) {
        if (node->data == data) {
            break;
        }

        prev = node;
        node = node->next;
    }

    if (node == l->head) {
        l->head = node->next;
    } else {
        prev->next = node->next;
    }

    l->length--;
    free(node);
    
}

bool is_empty_list(list_t* l) {
    return l->head == NULL && l->length == 0;
}

void list_foreach_element(list_t* l, void* app, void (*func)(void*, void*)) {
    if (l == NULL || l->head == NULL)
        return;

    node_t* e = l->head;
    while (e != NULL) {
        void* data = e->data;
        e = e->next;

        func(app, data);
    }
}

void free_list(list_t* l) {
    node_t* current = l->head;

    while (current != NULL) {
        node_t* next = current->next;
        free(current);
        current = next;
    }

    free(l);
}
