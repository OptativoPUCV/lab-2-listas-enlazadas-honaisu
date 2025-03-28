#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() { // Inicializa los datos en nulo
    List* list = (List*) malloc(sizeof(List)) ;
    list->current = NULL ;
    list->head = NULL ;
    list->tail = NULL ;
    return list ;
}

void * firstList(List * list) { // Retorna el primer dato de la lista
    if (!list->head) return NULL ; // Si la cabeza no existe, retorna nulo
    list->current = list->head ; // El actual se vuelve la cabeza
    return list->head->data ;
}

void * nextList(List * list) { // Retorna el siguiente dato de la lista
    if (list->current) list->current = list->current->next ; // Si el actual no es nulo, avanza al siguiente
    return (list->current) ? list->current->data : NULL ;
}

void * lastList(List * list) {
    while (list->current->next) list->current = list->current->next ;
    return (list->current) ? list->current->data : NULL ;
}

void * prevList(List * list) {
    if (!list->current || !list->current->prev) return NULL ;
    list->current = list->current->prev ;
    return (list->current) ? list->current->data : NULL ;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data) ;
    newNode->next = list->head ;
    if (list->head) list->head->prev = newNode ;
    else list->tail = newNode ; // Si es que no existe la cabeza, la cola también apuntará al nuevo nodo (puesto que será el primer valor)
    list->head = newNode ;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newNode = createNode(data) ;
    
    if (list->current) {
        newNode->prev = list->current ;
        list->current->next->prev = newNode ;
        list->current->next = newNode ;
    } 
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}