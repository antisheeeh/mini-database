#include <string.h>
#include <stdlib.h>

#include "../include/country.h"

#include "../include/database.h"

void addCard(List* list) {
    puts("Add card\n");

    puts("Please enter your country");
    Country* country = getCountryFromConsole();

    pushBack(list, createNode(country));
}

void editCard(List* list) {
    puts("Edit card\n");

    puts("Please enter card index");
    int index;
    scanf("%d", &index);

    Node* node = searchByIndex(list, index);
    puts("");

    if(!node) {
        puts("No card with this index\n");
        getchar();
        return;
    }

    printNode(node);

    puts("What do you want to edit?");
    puts("0 - name");
    puts("1 - capital");
    puts("2 - area");
    puts("3 - population");
    puts("4 - density");
    puts("5 - hdi");
    puts("6 - min height");
    puts("7 - max height");

    getchar();

    char buf[MAXLEN];
    fgets(buf, MAXLEN, stdin);

    if(strlen(buf) == 2 && '0' <= buf[0] && buf[0] <= '7') {
        if(buf[0] == '0') {
            printf("Name: ");
            scanf("%s", node->country->name);
        } else if(buf[1] == '1') {
            printf("Capital: ");
            scanf("%s", node->country->capital);
        } else if(buf[0] == '2') {
            printf("Area: ");
            scanf("%d", &node->country->area);
        } else if(buf[0] == '3') {
            printf("Population: ");
            scanf("%d", &node->country->population);
        } else if(buf[0] == '4') {
            printf("Density: ");
            scanf("%f", &node->country->density);
        } else if(buf[0] == '5') {
            printf("HDI: ");
            scanf("%f", &node->country->hdi);
        } else if(buf[0] == '6') {
            printf("Min height: ");
            scanf("%d", &node->country->elevation[0]);
        } else if(buf[0] == '7') {
            printf("Max height: ");
            scanf("%d", &node->country->elevation[1]);
        }
    }
}

void deleteCard(List* list) {
    puts("Delete card\n");

    puts("Please enter index of country to be deleted");
    int index;
    scanf("%d", &index);

    Node* node = searchByIndex(list, index);
    puts("");

    if(!node) {
        puts("No card with this index\n");
        getchar();
        return;
    }

    removeNode(list, node);
}

void searchCard(List* list) {
    puts("Search card\n");

    puts("Please enter field to be searched");
    puts("0 - name");
    puts("1 - capital");
    puts("2 - area");
    puts("3 - population");
    puts("4 - density");
    puts("5 - hdi");
    puts("6 - min height");
    puts("7 - max height");

    char buf[MAXLEN];
    fgets(buf, MAXLEN, stdin);

    List* res = NULL;

    if(strlen(buf) == 2 && '0' <= buf[0] && buf[0] <= '7') {
        if(buf[0] == '0') {
            puts("Enter name");
            char name[MAXLEN];
            scanf("%s", name);
            res = searchByName(list, name);
        } else if(buf[0] == '1') {
            puts("Enter capital");
            char capital[MAXLEN];
            scanf("%s", capital);
            res = searchByCapital(list, capital);
        } else if(buf[0] == '2') {
            puts("Enter area");
            int area;
            scanf("%d", &area);
            res = searchByArea(list, area);
        } else if(buf[0] == '3') {
            puts("Enter population");
            int population;
            scanf("%d", &population);
            res = searchByPopulation(list, population);
        } else if(buf[0] == '4') {
            puts("Enter density");
            float density;
            scanf("%f", &density);
            res = searchByDensity(list, density);
        } else if(buf[0] == '5') {
            puts("Enter hdi");
            float hdi;
            scanf("%f", &hdi);
            res = searchByHdi(list, hdi);
        } else if(buf[0] == '6') {
            puts("Enter min height");
            int minHeight;
            scanf("%d", &minHeight);
            res = searchByMinHeight(list, minHeight);
        } else if(buf[0] == '7') {
            puts("Enter max height");
            int maxHeight;
            scanf("%d", &maxHeight);
            res = searchByMaxHeight(list, maxHeight);
        }
    }

    if(isEmpty(res)) {
        puts("No card with this index\n");
        getchar();
        return;
    }

    printList(res);
    clearList(res);

    getchar();
}

void sortCards(List* list) {
    puts("Sort cards\n");

    puts("Please enter field to be sorted");
    puts("0 - name");
    puts("1 - capital");
    puts("2 - area");
    puts("3 - population");
    puts("4 - density");
    puts("5 - hdi");
    puts("6 - min height");
    puts("7 - max height");

    char buf[MAXLEN];
    fgets(buf, MAXLEN, stdin);

    if(strlen(buf) == 2 && '0' <= buf[0] && buf[0] <= '7') {
        if(buf[0] == '0') {
            sort(list, sortByName);
        } else if(buf[0] == '1') {
            sort(list, sortByCapital);
        } else if(buf[0] == '2') {
            sort(list, sortByArea);
        } else if(buf[0] == '3') {
            sort(list, sortByPopulation);
        } else if(buf[0] == '4') {
            sort(list, sortByDensity);
        } else if(buf[0] == '5') {
            sort(list, sortByHdi);
        } else if(buf[0] == '6') {
            sort(list, sortByMinHeight);
        } else if(buf[0] == '7') {
            sort(list, sortByMaxHeight);
        }
    }
}

void printCards(List* list) {
    puts("Print cards\n");

    printList(list);
}

void updateDatabase(FILE* db, List* list) {
    db = fopen("db.csv", "w");

    for(Node* t = list->first; t; t = t->next) {
        char* str = countryToString(t->country);
        fwrite(str, sizeof(char), strlen(str), db);
        fflush(db);
    }
}