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
    int choice;
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
        puts("8 - area range");
        puts("9 - population range");
        puts("10 - density range");
        puts("11 - hdi range");
        puts("12 - min height range");
        puts("13 - max height range");

        fgets(buf, MAXLEN, stdin);

        choice = atoi(buf);
        
        if(error = choice < 0 || choice > 13 || (choice == 0 && buf[0] != '0')) {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");
            getchar();
            CLS;
        }
    } while(error);

    List* res = NULL;

    do {
        if(choice == 0) {
            printf("Name: ");

            if(error = !fgets(buf, MAXLEN, stdin)) {
                puts("Input is incorrect! Please try again\n");
            } else {
                buf[strlen(buf) - 1] = '\0';
                res = searchByName(list, buf);
            }
        } else if(choice == 1) {
            printf("Capital: ");

            if(error = !fgets(buf, MAXLEN, stdin)) {
                puts("Input is incorrect! Please try again\n");
            } else {
                buf[strlen(buf) - 1] = '\0';
                res = searchByCapital(list, buf);
            }
        } else if(choice == 2) {
            printf("Area: ");
            fgets(buf, MAXLEN, stdin);
            int area = atoi(buf);

            if(error = !area && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByArea(list, area);
            }
        } else if(choice == 3) {
            printf("Population: ");
            fgets(buf, MAXLEN, stdin);
            int population = atoi(buf);

            if(error = !population && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByPopulation(list, population);
            }
        } else if(choice == 4) {
            printf("Density: ");
            fgets(buf, MAXLEN, stdin);
            float density = atof(buf);

            if(error = !density && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByDensity(list, density);
            }
        } else if(choice == 5) {
            printf("HDI: ");
            fgets(buf, MAXLEN, stdin);
            float hdi = atof(buf);

            if(error = !hdi && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByHdi(list, hdi);
            }
        } else if(choice == 6) {
            printf("Min height: ");
            fgets(buf, MAXLEN, stdin);
            int minHeight = atoi(buf);
            
            if(error = !minHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByMinHeight(list, minHeight);
            }
        } else if(choice == 7) {
            printf("Max height: ");
            fgets(buf, MAXLEN, stdin);
            int maxHeight = atoi(buf);

            if(error = !maxHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
            } else {
                res = searchByMinHeight(list, maxHeight);
            }
        } else if(choice == 8) {
            printf("Min area: ");
            fgets(buf, MAXLEN, stdin);
            int minArea = atoi(buf);

            if(error = !minArea && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            printf("Max area: ");
            fgets(buf, MAXLEN, stdin);
            int maxArea = atoi(buf);

            if(error = !maxArea && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            res = searchByAreaRange(list, minArea, maxArea);
        } else if(choice == 9) {
            printf("Min population: ");
            fgets(buf, MAXLEN, stdin);
            int minPopulation = atoi(buf);

            if(error = !minPopulation && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            printf("Max population: ");
            fgets(buf, MAXLEN, stdin);
            int maxPopulation = atoi(buf);

            if(error = !maxPopulation && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            res = searchByPopulationRange(list, minPopulation, maxPopulation);
        } else if(choice == 10) {
            printf("Min density: ");
            fgets(buf, MAXLEN, stdin);
            float minDensity = atoi(buf);

            if(error = !minDensity && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            printf("Max density: ");
            fgets(buf, MAXLEN, stdin);
            float maxDensity = atoi(buf);

            if(error = !maxDensity && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            res = searchByDensityRange(list, minDensity, maxDensity);
        } else if(choice == 11) {
            printf("Min hdi: ");
            fgets(buf, MAXLEN, stdin);
            float minHdi = atof(buf);

            if(error = !minHdi && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            printf("Max hdi: ");
            fgets(buf, MAXLEN, stdin);
            float maxHdi = atof(buf);

            if(error = !maxHdi && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            res = searchByHdiRange(list, minHdi, maxHdi);
        } else if(choice == 12) {
            printf("Min min height: ");
            fgets(buf, MAXLEN, stdin);
            int minHeight = atoi(buf);

            if(error = !minHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            printf("Max min height: ");
            fgets(buf, MAXLEN, stdin);
            int maxHeight = atoi(buf);

            if(error = !maxHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            res = searchByMinHeightRange(list, minHeight, maxHeight);
        } else if(choice == 13) {
            printf("Min max height: ");
            fgets(buf, MAXLEN, stdin);
            int minHeight = atoi(buf);

            if(error = !minHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            printf("Max max height: ");
            fgets(buf, MAXLEN, stdin);
            int maxHeight = atoi(buf);

            if(error = !maxHeight && buf[0] != '0') {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            res = searchByMaxHeightRange(list, minHeight, maxHeight);
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

    int choice = buf[0] - '0';

    puts("\nPlease enter sort mode");
    puts("0 - non-decreasing order");
    puts("1 - non-increasing order");

    do {
        fgets(buf, MAXLEN, stdin);

        if(error = strlen(buf) != 2 || buf[0] < '0' || buf[0] > '1') {
            puts("Input is incorrect! Please try again\n");
        }
    } while(error);

    int mode;

    if(buf[0] == '0') {
        mode = 1;
    } else if(buf[0] == '1') {
        mode = -1;
    }

    if(choice == 0) {
        sort(list, sortByName, mode);
    } else if(choice == 1) {
        sort(list, sortByCapital, mode);
    } else if(choice == 2) {
        sort(list, sortByArea, mode);
    } else if(choice == 3) {
        sort(list, sortByPopulation, mode);
    } else if(choice == 4) {
        sort(list, sortByDensity, mode);
    } else if(choice == 5) {
        sort(list, sortByHdi, mode);
    } else if(choice == 6) {
        sort(list, sortByMinHeight, mode);
    } else if(choice == 7) {
        sort(list, sortByMaxHeight, mode);
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