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
List* initFromFile(FILE* file);
Node* createNode(Country* country);

List* searchByName(List *list, char name[MAXLEN]);
List* searchByCapital(List* list, char capital[MAXLEN]);
List* searchByArea(List* list, int area);
List* searchByPopulation(List* list, int population);
List* searchByDensity(List* list, float density);
List* searchByHdi(List* list, float hdi);
List* searchByMinHeight(List* list, int minHeight);
List* searchByMaxHeight(List* list, int maxHeight);

Node* searchByIndex(List* list, int index);

int sortByName(Node* node1, Node* node2);
int sortByCapital(Node* node1, Node* node2);
int sortByArea(Node* node1, Node* node2);
int sortByPopulation(Node* node1, Node* node2);
int sortByDensity(Node* node1, Node* node2);
int sortByHdi(Node* node1, Node* node2);
int sortByMinHeight(Node* node1, Node* node2);
int sortByMaxHeight(Node* node1, Node* node2);


void swapNodes(List* list, Node* node1, Node* node2);
void sort(List* list, int (*compaire)(Node*, Node*));
void reverse(List* list);
void pushFront(List* list, Node* node);
void pushBack(List* list, Node* node);
void insertAfter(List* list, Node* node, Node* newNode);
void insertBefore(List* list, Node* node, Node* newNode);
void removeNode(List* list, Node* node);
void clearList(List* list);

void printNode(Node* node);
void printList(List* list);