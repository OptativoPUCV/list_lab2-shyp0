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

  if (list->current==list->head){
    list->head=list->current->next;
    free(list->current);
    list->current=list->head;
    list->head->prev=NULL;
  return  (void*) list->current->data;
  }
  if(list->current==list->tail){
    list->tail=list->current->prev;
    free(list->current);
    list->current=list->tail;
    list->tail->next=NULL;
    return  (void*) list->current->data;
  }
  if (list->current->prev!=NULL){
    list->current->prev->next=list->current->next;
  }
  else list->head=list->current->next;
  if(list->current->next!=NULL){
    list->current->next->prev=list->current->prev;
  }
  //list->current=list->head;
  return  (void*) list->current->data;
}
 

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}