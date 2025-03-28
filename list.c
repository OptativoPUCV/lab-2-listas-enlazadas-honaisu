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
    if (list->head) list->head->prev = newNode ; // Si la cabeza no es nulo, el previo apuntará al nuevo nodo
    else list->tail = newNode ; // Si es que no existe la cabeza, la cola también apuntará al nuevo nodo (puesto que será el primer valor)
    list->head = newNode ; // La cabeza será el nuevo nodo
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newNode = createNode(data) ;
    if (!list->current) { // Si no hay current
        pushFront(list, data) ; // Se hace un pushFront (poner el dato en primer posición)
        return ;
    }
    // Apuntar las direcciones del nuevo nodo al actual (para el previo) y el siguiente del actual (para el siguiente del nuevo)
    newNode->prev = list->current ;
    newNode->next = list->current->next ;
    if (list->current->next) {  // Si existe el siguiente de la lista
        list->current->next->prev = newNode ; // El previo del siguiente apunta al nuevo nodo
    } else list->tail = newNode ; // Si no, apunta a la cola (puesto que sería el "último" dato)
    list->current->next = newNode ; // Se asigna el siguiente del current al nuevo nodo
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
    void* data = list->current->data ; // Puntero a la direccion del dato

    if (list->current) {
        if (list->current == list->head) { // Si es que el current es la cabeza
            list->head = list->current->next ; // Muevo el current a la siguiente posición
        } 
        if (list->current == list->tail) { // Si es la cola
            list->tail = list->current->prev ; // La mueva a la posición anterior
        }
        // Pivotes que referencian la parte anterior y posterior del nodo actual
        Node* Prev = list->current->prev ;
        Node* Next = list->current->next ;
        // Si es que existen, apuntarán a su dirección
        if (Prev) Prev->next = Next ;
        if (Next) Next->prev = Prev ;
        // Liberar el current
        free(list->current) ;
        // Mover el current al siguiente nodo
        list->current = Next ;
    } else return NULL ; // Si no hay current, retorna nulo
    return data; // Si hay current, retornar el dato
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}