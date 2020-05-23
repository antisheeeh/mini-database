#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/country.h"
#include "../include/input.h"

#include "../include/doubly_linked_list.h"

#define HEADER "\nID     | Name             | Capital          | Area         | Population   | Density      | HDI          | Min height   | Max height    \n"
#define SPLIT_LINE "-------+------------------+------------------+--------------+--------------+--------------+--------------+--------------+---------------\n"

List* init(void) {
    List* list = malloc(sizeof(List));
    if(!list) {
        puts("Error allocating memory for list");
        return NULL;
    }

    list->size = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

List* initFromFile(FILE* db) {
    if(!db) return NULL;

    List* list = init();
    if(!list) return NULL;

    char buf[MAX_LENGTH];

    while(fgets(buf, MAX_LENGTH, db)) {
        pushBack(list, getCountryFromString(buf, NORMAL));
    }

    return list;
}

int isEmpty(List* list) {
    return list->size == 0;
}

Node* createNode(Country* country) {
    if(!country) return NULL;

    Node* node = malloc(sizeof(Node));
    if(!node) {
        puts("Error allocating memory for node");
        return NULL;
    }

    node->country = country;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void sort(List* list, int mode, int order) {
    for(int i = 0; i < list->size; ++i) {
        for(int j = 0; j < list->size - i - 1; ++j) {
            Node* node1 = searchByIndex(list, j);

            if(order * compaire(node1->country, node1->next->country, mode) > 0) {
                swap(list, node1, node1->next);
            }
        }
    }
}

List* search(List* list, char str[MAXLEN], int mode) {
    if(!list) return NULL;

    List* res = init();
    if(!res) return NULL;

    Country* country = getCountryFromString(str, mode);
    if(!country) return NULL;

    for(Node* node = list->first; node; node = node->next) {
        if(!compaire(node->country, country, mode)) {
            pushBack(res, node->country);
        }
    }

    return res;
}

List* searchByRange(List* list, char name[MAXLEN], char min[MAXLEN], char max[MAXLEN], int mode) {
    if(!list) return NULL;

    List* res = init();
    if(!res) return NULL;

    Country* country1 = getCountryFromString(min, mode);
    if(!country1) return NULL;

    Country* country2 = getCountryFromString(max, mode);
    if(!country2) return NULL;

    puts(name);

    for(Node* node = list->first; node; node = node->next) {
        if(!strncmp(node->country->name, name, strlen(name)) &&
            compaire(node->country, country1, mode) >= 0 && 
            compaire(node->country, country2, mode) <= 0) {
            pushBack(res, node->country);
        }
    }

    return res;
}

void reverse(List* list) {
    for(int i = list->size / 2 - 1; i >= 0; --i) {
        swap(list, searchByIndex(list, i), searchByIndex(list, list->size - i - 1));
    }
}

void swap(List* list, Node* node1, Node* node2) {
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

void pushFront(List* list, Country* country) {
    if(!list || !country) return;

    Node* node = createNode(country);
    if(!node) return;

    if(isEmpty(list)) {
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
    }

    list->first = node;
    list->size++;
}

void pushBack(List* list, Country* country) {
    if(!list || !country) return;

    Node* node = createNode(country);
    if(!node) return;

    if(isEmpty(list)) {
        list->first = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
    }

    list->last = node;
    list->size++;
}

void insertAfter(List* list, Node* node, Country* country) {
    if(!list || !node || !country) return;

    if(node == list->last) {
        pushBack(list, country);
    } else {
        Node* newNode = createNode(country);
        if(!newNode) return;

        newNode->prev = node;
        newNode->next = node->next;
        
        node->next->prev = newNode;
        node->next = newNode;

        list->size++;
    }
}

void insertBefore(List* list, Node* node, Country* country) {
    if(!list || !node || !country) return;

    if(node == list->first) {
        pushFront(list, country);
    } else {
        insertAfter(list, node->prev, country);
    }
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
    node = NULL;
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

    printf(HEADER);
    printf(SPLIT_LINE);

    Node* node = list->first;

    for(int i = 0; i < list->size; ++i) {
        printf("%-6d | ", i);
        printCountryInTable(node->country);
        if(node->next) printf(SPLIT_LINE);
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
    list = NULL;
}