#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/country.h"
#include "../include/input.h"

#include "../include/doubly_linked_list.h"

List* init(void) {
    List* list = malloc(sizeof(List));
    if(!list) return NULL;

    list->size = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

List* initFromFile(FILE* file) {
    if(!file) {
        puts("Cannot open input csv file");
        return NULL;
    }

    List* list = init();
    if(!list) return NULL;

    char buf[MAX_LENGTH];

    while(fgets(buf, MAX_LENGTH, file)) {
        pushBack(list, createNode(getCountryFromString(splitLine(buf))));
    }

    return list;
}

int isEmpty(List* list) {
    return list->size == 0;
}

Node* createNode(Country* country) {
    if(!country) return NULL;

    Node* node = malloc(sizeof(Node));
    if(!node) return NULL;

    node->country = country;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

int sortByName(Node* node1, Node* node2, int mode) {
    return mode * strcmp(node1->country->name, node2->country->name) > 0;
}

int sortByCapital(Node* node1, Node* node2, int mode) {
    return mode * strcmp(node1->country->capital, node2->country->capital) > 0;
}

int sortByArea(Node* node1, Node* node2, int mode) {
    return mode * (node1->country->area - node2->country->area) > 0;
}

int sortByPopulation(Node* node1, Node* node2, int mode) {
    return mode * (node1->country->population - node2->country->population) > 0;
}

int sortByDensity(Node* node1, Node* node2, int mode) {
    return mode * (node1->country->density - node2->country->density) > 0;
}

int sortByHdi(Node* node1, Node* node2, int mode) {
    return mode * (node1->country->hdi - node2->country->hdi) > 0;
}

int sortByMinHeight(Node* node1, Node* node2, int mode) {
    return mode * (node1->country->elevation[0] - node2->country->elevation[0]) > 0;
}

int sortByMaxHeight(Node* node1, Node* node2, int mode) {
    return mode * (node1->country->elevation[1] - node2->country->elevation[1]) > 0;
}

void sort(List* list, int (*compaire)(Node*, Node*, int), int mode) {
    for(int i = 0; i < list->size; ++i) {
        for(int j = 0; j < list->size - i - 1; ++j) {
            Node* node1 = searchByIndex(list, j);
            Node* node2 = searchByIndex(list, j + 1);

            if(compaire(node1, node2, mode)) {
                swapNodes(list, node1, node2);
            }
        }
    }
}

void reverse(List* list) {
    for(int i = list->size / 2 - 1; i >= 0; --i) {
        swapNodes(list, searchByIndex(list, i), searchByIndex(list, list->size - i - 1));
    }
}

void swapNodes(List* list, Node* node1, Node* node2) {
    if(!list || !node1 || !node2 || node1 == node2) return;

    if(node1->next == node2) {
        if(node1->prev) node1->prev->next = node2;
        if(node2->next) node2->next->prev = node1;

        node1->next = node2->next;
        node2->next = node1;

        node2->prev = node1->prev;
        node1->prev = node2;
    } else if(node2->next == node1) {
        if(node2->prev) node2->prev->next = node1;
        if(node1->next) node1->next->prev = node2;

        node2->next = node1->next;
        node1->next = node2;

        node1->prev = node2->prev;
        node2->prev = node1;
    } else {
        if(node1->prev) node1->prev->next = node2;
        if(node1->next) node1->next->prev = node2;

        if(node2->prev) node2->prev->next = node1;
        if(node2->next) node2->next->prev = node1;

        Node* temp = node1->prev;
        node1->prev = node2->prev;
        node2->prev = temp;

        temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }

    if(list->first == node1) list->first = node2;
    else if(list->first == node2) list->first = node1;

    if(list->last == node1) list->last = node2;
    else if(list->last == node2) list->last = node1;
}

void pushFront(List* list, Node* node) {
    if(!list || !node) return;

    node->next = list->first;

    if(!isEmpty(list)) {
        list->first->prev = node;
    }
    
    list->first = node;
    if(isEmpty(list)) list->last = node;

    list->size++;
}

void pushBack(List* list, Node* node) {
    if(!list || !node) return;

    node->prev = list->last;

    if(!isEmpty(list)) {
        list->last->next = node;
    }

    if(isEmpty(list)) list->first = node;
    list->last = node;
    
    list->size++;
}

void insertAfter(List* list, Node* node, Node* newNode) {
    if(!list || !node || !newNode) return;

    if(node == list->last) {
        pushBack(list, newNode);
    } else {
        newNode->next = node->next;
        node->next->prev = newNode;
        node->next = newNode;

        list->size++;
    }
}

void insertBefore(List* list, Node* node, Node* newNode) {
    if(!list || !node || !newNode) return;

    if(node == list->first) {
        pushFront(list, newNode);
    } else {
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;

        list->size++;
    }
}

List* searchByName(List *list, char name[MAXLEN]) {
    if(!list || !name) return NULL;

    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(!strcmp(i->country->name, name)) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByCapital(List* list, char capital[MAXLEN]) {
    if(!list || !capital) return NULL;
    
    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(!strcmp(i->country->capital, capital)) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByArea(List* list, int area) {
    if(!list || area < 0) return NULL;

    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(i->country->area == area) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByPopulation(List* list, int population) {
    if(!list || population < 0) return NULL;
    
    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(i->country->population == population) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByDensity(List* list, float density) {
    if(!list || density < 0) return NULL;
    
    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(i->country->density == density) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByHdi(List* list, float hdi) {
    if(!list || hdi < 0 || hdi > 1) return NULL;
    
    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(i->country->hdi == hdi) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByMinHeight(List* list, int minHeight) {
    if(!list) return NULL;
    
    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(i->country->elevation[0] == minHeight) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByMaxHeight(List* list, int maxHeight) {
    if(!list) return NULL;
    
    List* res = init();
    
    for(Node* i = list->first; i; i = i->next) {
        if(i->country->elevation[1] == maxHeight) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByAreaRange(List* list, int minArea, int maxArea) {
    if(!list) return NULL;

    List* res = init();

    for(Node* i = list->first; i; i = i->next) {
        int area = i->country->area;

        if(minArea <= area && area <= maxArea) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByPopulationRange(List* list, int minPopulation, int maxPopulation) {
    if(!list) return NULL;

    List* res = init();

    for(Node* i = list->first; i; i = i->next) {
        int population = i->country->population;

        if(minPopulation <= population && population <= maxPopulation) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByDensityRange(List* list, float minDensity, float maxDensity) {
    if(!list) return NULL;

    List* res = init();

    for(Node* i = list->first; i; i = i->next) {
        float density = i->country->density;

        if(minDensity <= density && density <= maxDensity) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByHdiRange(List* list, int minHdi, int maxHdi) {
    if(!list) return NULL;

    List* res = init();

    for(Node* i = list->first; i; i = i->next) {
        int hdi = i->country->hdi;

        if(minHdi <= hdi && hdi <= maxHdi) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByMinHeightRange(List* list, int minHeight, int maxHeight) {
    if(!list) return NULL;

    List* res = init();

    for(Node* i = list->first; i; i = i->next) {
        int height = i->country->elevation[0];

        if(minHeight <= height && height <= maxHeight) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

List* searchByMaxHeightRange(List* list, int minHeight, int maxHeight) {
    if(!list) return NULL;

    List* res = init();

    for(Node* i = list->first; i; i = i->next) {
        int height = i->country->elevation[1];

        if(minHeight <= height && height <= maxHeight) {
            pushBack(res, createNode(i->country));
        }
    }

    return res;
}

Node* searchByIndex(List* list, int index) {
    if(!list || index < 0 || index > list->size - 1) return NULL;

    Node* t = list->first;
    for(int i = 0; i < index; ++i) t = t->next;
    return t;
}

void removeNode(List* list, Node* node) {
    if(!list || !node) return;

    if(node == list->first) {
        list->first = node->next;
    } else {
        node->prev->next = node->next;
    }

    if(node == list->last) {
        list->last = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    list->size--;

    free(node);
}

void printNode(Node* node) {
    if(!node) return;

    printCountry(node->country);
}

void printList(List* list) {
    if(!list) return;

    if(isEmpty(list)) {
        puts("List is empty\n");
        return;
    }

    printHeader();

    Node* node = list->first;

    for(int i = 0; i < list->size; ++i) {
        printf("%-6d | ", i);
        printCountryInTable(node->country);
        if(node->next) printSepLine();
        node = node->next;
    }
}

void clearList(List* list) {
    if(!list) return;

    Node* node = list->first;

    while(node) {
        Node* temp = node->next;
        free(node);
        node = temp;
    }

    free(list);
}