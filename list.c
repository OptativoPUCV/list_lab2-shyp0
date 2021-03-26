#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list=(List*) malloc(sizeof(List));
  list->head=NULL;
  list->tail=NULL;
  return (void*) list;
}

void * firstList(List * list) {
  if(!list->head) return NULL;
  list->current=list->head;
    return (void*) list->head->data;
}

void * nextList(List * list) {
  if (list->current && list->current->next != NULL){
    list->current=list->current->next;
  return (void*)list->current->data;
  }
  return NULL;
}

void * lastList(List * list) {
    if(!list->tail) return NULL;
    list->current=list->tail;
    return (void*) list->current->data;
}

void * prevList(List * list) {
  if (list->current && list->current->prev != NULL){
    list->current=list->current->prev;
  return (void*)list->current->data;
  }
  return NULL;
}

void pushFront(List * list, const void * data) {
 Node *aux=createNode(data);
 if (list->head==NULL){
    list->head=aux;
    list->tail=aux;
 }
 else{
    aux->next=list->head;
    list->head->prev=aux;
 }
list->head=aux;
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
    Node *aux2=createNode(data);
 if (list->head==NULL){
    list->head=aux2;
    list->tail=aux2;
 }
 else{
    aux2->prev=list->current;
    list->current->next=aux2;
 }
  list->tail=aux2;
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
  void* aux;
  //verifica que el primer dato sea la cabeza
  if (list->current==list->head){
    //mueve el valor de la cabeza 
    list->head=list->current->next;
    //libera el valor del nodo de la cabeza antigua
    aux=list->current;
    free(list->current);
    //reasigna el valor al current de la nueva cabeza
    list->current=aux;
    //senala que lo previo a la cabeza es null
    list->head->prev=NULL;
  return  (void*) list->current->data;
  }
  //verifica que el current este en el tail
  if(list->current==list->tail){
    //reasigno el valor de cola uno antes 
    list->tail=list->current->prev;
    //libero el nodo del antiguo cola
    free(list->current);
    //reasigno el valor del current por el nuevo valor de cola
    list->current=list->tail;
    //indico que el valor siguiente de la cola es null
    list->tail->next=NULL;
    return  (void*) list->current->data;
  }
  //verifica que no este en una cabeza el current
  if (list->current->prev!=NULL){
    //hace que el nodo previo al current apunte al nodo siguiente del current
    list->current->prev->next=list->current->next;
  }
  //else list->head=list->current->next;
  //verifica que no este en una cola
  if(list->current->next!=NULL){
    //hace que el nodo siguiente al current apunte al nodo previo del current
    list->current->next->prev=list->current->prev;
  }
  //aux que guarda el valor del current

  //asigno el valor a aux del current siguiente 
  aux=list->current->next;
  //libero el nodo current;
  free(list->current);
  //reasigno el valor a current por el siguiente de este que estaba guardado en aux
  list->current=aux;
  return  (void*) list->current->data;
}
 

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}