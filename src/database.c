#include <string.h>
#include <stdlib.h>

#include "../include/country.h"

#include "../include/database.h"

#ifdef linux
#define CLS system("clear")
#else
#define CLS system("cls")
#endif

void addCard(List* list) {
    int error;
    Country* country;

    do {
        puts("Add card\n");

        puts("Please enter your country");
        country = getCountryFromConsole();

        if(error = !country) {
            puts("\nInput is incorrect! Please try again");
            puts("Press any key to continue...");
            getchar();
            CLS;
        }
    } while(error);

    pushBack(list, createNode(country));
}

void editCard(List* list) {
    int error;
    int index;
    char buf[MAXLEN];

    do {
        puts("Edit card\n");

        puts("Please enter card index");

        fgets(buf, MAXLEN, stdin);
        index = atoi(buf);
        
        if(error = !index && buf[0] != '0') {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");
            getchar();
            CLS;
        }
    } while(error);

    Node* node = searchByIndex(list, index);
    puts("");

    if(!node) {
        puts("No card with this index\n");
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

    do {
        fgets(buf, MAXLEN, stdin);

        if(error = strlen(buf) != 2 || buf[0] < '0' || buf[0] > '7') {
            puts("Input is incorrect! Please try again\n");
            puts("What do you want to edit?");
        }
    } while(error);

    do {
        if(buf[0] == '0') {
            printf("Name: ");

            if(error = !fgets(buf, MAXLEN, stdin)) {
                puts("Input is incorrect! Please try again\n");
            } else {
                buf[strlen(buf) - 1] = '\0';
                strcpy(node->country->name, buf);
            }
        } else if(buf[0] == '1') {
            printf("Capital: ");

            if(error = !fgets(buf, MAXLEN, stdin)) {
                puts("Input is incorrect! Please try again\n");
            } else {
                buf[strlen(buf) - 1] = '\0';
                strcpy(node->country->capital, buf);
            }
        } else if(buf[0] == '2') {
            printf("Area: ");
            fgets(buf, MAXLEN, stdin);
            int area = atoi(buf);

            if(error = !area && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                node->country->area = area;
            }
        } else if(buf[0] == '3') {
            printf("Population: ");
            fgets(buf, MAXLEN, stdin);
            int population = atoi(buf);

            if(error = !population && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                node->country->population = population;
            }
        } else if(buf[0] == '4') {
            printf("Density: ");
            fgets(buf, MAXLEN, stdin);
            float density = atof(buf);

            if(error = !density && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                node->country->density = density;
            }
        } else if(buf[0] == '5') {
            printf("HDI: ");
            fgets(buf, MAXLEN, stdin);
            float hdi = atof(buf);

            if(error = !hdi && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                node->country->hdi = hdi;
            }
        } else if(buf[0] == '6') {
            printf("Min height: ");
            fgets(buf, MAXLEN, stdin);
            int minHeight = atoi(buf);
            
            if(error = !minHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                node->country->elevation[0] = minHeight;
            }
        } else if(buf[0] == '7') {
            printf("Max height: ");
            fgets(buf, MAXLEN, stdin);
            int maxHeight = atoi(buf);

            if(error = !maxHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                node->country->elevation[1] = maxHeight;
            }
        }
    } while(error);
}

void deleteCard(List* list) {
    char buf[MAXLEN];
    int index;
    int error;

    do {
        puts("Delete card\n");
        puts("Please enter card index");

        fgets(buf, MAXLEN, stdin);
        index = atoi(buf);
        
        if(error = !index && buf[0] != '0') {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");
            getchar();
            CLS;
        }
    } while(error);

    Node* node = searchByIndex(list, index);

    if(!node) {
        puts("\nNo card with this index");
    } else {
        removeNode(list, node);
    }
}

void searchCard(List* list) {
    int error;
    char buf[MAXLEN];

    do {
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

        fgets(buf, MAXLEN, stdin);
        
        if(error = strlen(buf) != 2 || buf[0] < '0' || buf[0] > '7') {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");
            getchar();
            CLS;
        }
    } while(error);

    List* res = NULL;

    do {
        if(buf[0] == '0') {
            printf("Name: ");

            if(error = !fgets(buf, MAXLEN, stdin)) {
                puts("Input is incorrect! Please try again\n");
            } else {
                buf[strlen(buf) - 1] = '\0';
                res = searchByName(list, buf);
            }
        } else if(buf[0] == '1') {
            printf("Capital: ");

            if(error = !fgets(buf, MAXLEN, stdin)) {
                puts("Input is incorrect! Please try again\n");
            } else {
                buf[strlen(buf) - 1] = '\0';
                res = searchByCapital(list, buf);
            }
        } else if(buf[0] == '2') {
            printf("Area: ");
            fgets(buf, MAXLEN, stdin);
            int area = atoi(buf);

            if(error = !area && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByArea(list, area);
            }
        } else if(buf[0] == '3') {
            printf("Population: ");
            fgets(buf, MAXLEN, stdin);
            int population = atoi(buf);

            if(error = !population && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByPopulation(list, population);
            }
        } else if(buf[0] == '4') {
            printf("Density: ");
            fgets(buf, MAXLEN, stdin);
            float density = atof(buf);

            if(error = !density && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByDensity(list, density);
            }
        } else if(buf[0] == '5') {
            printf("HDI: ");
            fgets(buf, MAXLEN, stdin);
            float hdi = atof(buf);

            if(error = !hdi && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByHdi(list, hdi);
            }
        } else if(buf[0] == '6') {
            printf("Min height: ");
            fgets(buf, MAXLEN, stdin);
            int minHeight = atoi(buf);
            
            if(error = !minHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByMinHeight(list, minHeight);
            }
        } else if(buf[0] == '7') {
            printf("Max height: ");
            fgets(buf, MAXLEN, stdin);
            int maxHeight = atoi(buf);

            if(error = !maxHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByMinHeight(list, maxHeight);
            }
        }
    } while(error);

    if(isEmpty(res)) {
        puts("\nNo card");
    } else {
        printList(res);
        clearList(res);
    }
}

void sortCards(List* list) {
    int error;
    char buf[MAXLEN];

    do {
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

        fgets(buf, MAXLEN, stdin);
        
        if(error = strlen(buf) != 2 || buf[0] < '0' || buf[0] > '7') {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");
            getchar();
            CLS;
        }
    } while(error);

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