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
    if (list->head == NULL) return NULL ; // Si la cabeza no existe, retorna nulo
    Node* primero = list->head->data ; // Referencia al dato de la cabeza (primero)
    list->current = list->head ; // El actual se vuelve la cabeza
    return primero ;
}

void * nextList(List * list) { // Retorna el siguiente dato de la lista
    if (list->current == NULL) return NULL ; // Verifica si el actual es nulo
    Node* siguiente = list->current->next->data ;
    list->current = list->current->next ;
    return siguiente ;
}

void * lastList(List * list) {
    return NULL;
}

void * prevList(List * list) {
    return NULL;
}

void pushFront(List * list, void * data) {
    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
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