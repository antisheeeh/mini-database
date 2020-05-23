#pragma once

#include "country.h"

#include <stdio.h>

typedef struct Node {
    Country* country;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct List {
    int size;
    Node* first;
    Node* last;
} List;

int isEmpty(List* list);

List* init(void);
List* initFromFile(FILE* db);
Node* createNode(Country* country);

List* search(List* list, char str[MAXLEN], int mode);
List* searchByRange(List* list, char name[MAXLEN], char min[MAXLEN], char max[MAXLEN], int mode);
Node* searchByIndex(List* list, int index);

void swap(List* list, Node* node1, Node* node2);
void sort(List* list, int mode, int order);
void reverse(List* list);
void pushFront(List* list, Country* country);
void pushBack(List* list, Country* country);
void insertAfter(List* list, Node* node, Country* country);
void insertBefore(List* list, Node* node, Country* country);
void removeNode(List* list, Node* node);
void clearList(List* list);

void printNode(Node* node);
void printList(List* list);