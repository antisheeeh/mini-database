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
        puts("Add card");

        printList(list);

        puts("\nPlease enter your country");
        country = getCountryFromConsole();

        if(error = !country) {
            puts("\nInput is incorrect! Please try again");
            puts("Press any key to continue...");

            char buf[MAXLEN];
            fgets(buf, MAXLEN, stdin);

            CLS;
        }
    } while(error);

    pushBack(list, country);
}

void editCard(List* list) {
    int error;
    int index;
    char buf[MAXLEN];

    do {
        puts("Edit card");

        printList(list);

        puts("\nPlease enter card index");

        fgets(buf, MAXLEN, stdin);
        index = atoi(buf);
        
        if(error = !index && buf[0] != '0') {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");

            char buf[MAXLEN];
            fgets(buf, MAXLEN, stdin);

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

    int mode = buf[0] - '0';

    do {
        if(mode == 0) {
            printf("Name: ");

            error = !fgets(buf, MAXLEN, stdin);
            if(!error) {
                buf[strlen(buf) - 1] = '\0';
                strcpy(node->country->name, buf);
            }
        } else if(mode == 1) {
            printf("Capital: ");
            
            error = !fgets(buf, MAXLEN, stdin);
            if(!error) {
                buf[strlen(buf) - 1] = '\0';
                strcpy(node->country->capital, buf);
            }
        } else if(mode == 2) {
            printf("Area: ");
            fgets(buf, MAXLEN, stdin);
            int area = atoi(buf);

            error = !area && area > 0 && buf[0] != '0';
            if(!error) {
                node->country->area = area;
            }
        } else if(mode == 3) {
            printf("Population: ");
            fgets(buf, MAXLEN, stdin);
            int population = atoi(buf);

            error = !population && population > 0 && buf[0] != '0';
            if(!error) {
                node->country->population = population;
            }
        } else if(mode == 4) {
            printf("Density: ");
            fgets(buf, MAXLEN, stdin);
            float density = atof(buf);

            error = !density && density >= 0 && buf[0] != '0';
            if(!error) {
                node->country->density = density;
            }
        } else if(mode == 5) {
            printf("HDI: ");
            fgets(buf, MAXLEN, stdin);
            float hdi = atof(buf);

            error = !hdi && hdi >= 0 && hdi <= 1 &&buf[0] != '0';
            if(!error) {
                node->country->hdi = hdi;
            }
        } else if(mode == 6) {
            printf("Min height: ");
            fgets(buf, MAXLEN, stdin);
            int minHeight = atoi(buf);
            
            error = !minHeight && buf[0] != '0';
            if(!error) {
                node->country->elevation[0] = minHeight;
            }
        } else if(mode == 7) {
            printf("Max height: ");
            fgets(buf, MAXLEN, stdin);
            int maxHeight = atoi(buf);

            error = !maxHeight && buf[0] != '0';
            if(!error) {
                node->country->elevation[1] = maxHeight;
            }
        }

        if(error) {
            puts("Input is incorrect! Please try again\n");
        }
    } while(error);
}

void deleteCard(List* list) {
    char buf[MAXLEN];
    int index;
    int error;

    do {
        puts("Delete card");
        
        printList(list);

        puts("\nPlease enter card index");

        fgets(buf, MAXLEN, stdin);
        index = atoi(buf);
        
        if(error = !index && buf[0] != '0') {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");

            char buf[MAXLEN];
            fgets(buf, MAXLEN, stdin);

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
    int mode;
    char buf[MAXLEN];

    do {
        puts("Search card");

        printList(list);

        puts("\nPlease enter field to be searched");
        puts("0 - name");
        puts("1 - capital");
        puts("2 - area");
        puts("3 - population");
        puts("4 - density");
        puts("5 - hdi");
        puts("6 - min height");
        puts("7 - max height");
        puts("8 - first letters of name and area range");
        puts("9 - first letters of name and population range");
        puts("10 - first letters of name and density range");
        puts("11 - first letters of name and hdi range");
        puts("12 - first letters of name and min height range");
        puts("13 - first letters of name and max height range");

        fgets(buf, MAXLEN, stdin);

        mode = atoi(buf);
        
        if(error = mode < 0 || mode > 13 || (mode == 0 && buf[0] != '0')) {
            puts("Input is incorrect! Please try again\n");
            puts("Press any key to continue...");

            char buf[MAXLEN];
            fgets(buf, MAXLEN, stdin);

            CLS;
        }
    } while(error);

    char name[MAXLEN], min[MAXLEN], max[MAXLEN];

    do {
        if(mode == 0) {
            printf("Name: ");
            error = !fgets(buf, MAXLEN, stdin) || strlen(buf) == 1;

            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 1) {
            printf("Capital: ");
            error = !fgets(buf, MAXLEN, stdin) || strlen(buf) == 1;
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 2) {
            printf("Area: ");
            fgets(buf, MAXLEN, stdin);
            error = !atoi(buf) && atoi(buf) > 0 && buf[0] != '0';
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 3) {
            printf("Population: ");
            fgets(buf, MAXLEN, stdin);
            error = !atoi(buf) && atoi(buf) > 0 && buf[0] != '0';
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 4) {
            printf("Density: ");
            fgets(buf, MAXLEN, stdin);
            error = !atof(buf) && atoi(buf) >= 0 && buf[0] != '0';
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 5) {
            printf("HDI: ");
            fgets(buf, MAXLEN, stdin);
            error = !atof(buf) && atoi(buf) >= 0 && atoi(buf) <= 1 && buf[0] != '0';
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 6) {
            printf("Min height: ");
            fgets(buf, MAXLEN, stdin);
            error = !atoi(buf) && buf[0] != '0';
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(mode == 7) {
            printf("Max height: ");
            fgets(buf, MAXLEN, stdin);
            error = !atoi(buf) && buf[0] != '0';
            
            if(error) {
                puts("Input is incorrect! Please try again\n");
            }
        } else if(8 <= mode && mode <= 13) {
            puts("Please enter first letters of countries to be searched");

            if(error = !fgets(name, MAXLEN, stdin) || strlen(name) == 1) {
                puts("Input is incorrect! Please try again\n");
                continue;
            }

            if(mode == 8) {
                printf("Min area: ");
                fgets(min, MAXLEN, stdin);

                if(error = !atoi(min) && atoi(min) > 0 && min[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                    continue;
                }

                printf("Max area: ");
                fgets(max, MAXLEN, stdin);

                if(error = !atoi(max) && atoi(max) > 0 && max[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                }
            } else if(mode == 9) {
                printf("Min population: ");
                fgets(min, MAXLEN, stdin);

                if(error = !atoi(min) && atoi(min) > 0 &&  min[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                    continue;
                }

                printf("Max population: ");
                fgets(max, MAXLEN, stdin);

                if(error = !atoi(max) && atoi(max) > 0 && max[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                }
            } else if(mode == 10) {
                printf("Min density: ");
                fgets(min, MAXLEN, stdin);

                if(error = !atof(min) && atof(min) >= 0 && min[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                    continue;
                }

                printf("Max density: ");
                fgets(max, MAXLEN, stdin);

                if(error = !atof(max) && atof(max) >= 0 && max[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                }
            } else if(mode == 11) {
                printf("Min hdi: ");
                fgets(min, MAXLEN, stdin);

                if(error = !atof(min) && atof(min) >= 0 && atof(min) <= 1 && min[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                    continue;
                }

                printf("Max hdi: ");
                fgets(max, MAXLEN, stdin);

                if(error = !atof(max) && atof(max) >= 0 && atof(max) <= 1 && max[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                }
            } else if(mode == 12) {
                printf("Min min height: ");
                fgets(min, MAXLEN, stdin);

                if(error = !atoi(min) && min[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                    continue;
                }

                printf("Max min height: ");
                fgets(max, MAXLEN, stdin);

                if(error = !atoi(max) && max[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                }
            } else if(mode == 13) {
                printf("Min max height: ");
                fgets(min, MAXLEN, stdin);

                if(error = !atoi(min) && min[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                    continue;
                }

                printf("Max max height: ");
                fgets(max, MAXLEN, stdin);

                if(error = !atoi(max) && max[0] != '0') {
                    puts("Input is incorrect! Please try again\n");
                }
            }
        }
    } while(error);

    List* res;

    if(0 <= mode && mode <= 7) {
        buf[strlen(buf) - 1] = '\0';

        res = search(list, buf, mode);
    } else if(8 <= mode && mode <= 13) {
        name[strlen(name) - 1] = '\0';
        min[strlen(min) - 1] = '\0';
        max[strlen(max) - 1] = '\0';

        res = searchByRange(list, name, min, max, mode - 6);
    }

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
        puts("Sort cards");

        printList(list);

        puts("\nPlease enter field to be sorted");
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

            char buf[MAXLEN];
            fgets(buf, MAXLEN, stdin);
            
            CLS;
        }
    } while(error);

    int mode = buf[0] - '0';

    puts("\nPlease enter sort mode");
    puts("0 - non-decreasing order");
    puts("1 - non-increasing order");

    do {
        fgets(buf, MAXLEN, stdin);

        if(error = strlen(buf) != 2 || buf[0] < '0' || buf[0] > '1') {
            puts("Input is incorrect! Please try again\n");
            puts("Please enter sort mode");
        }
    } while(error);

    int order;

    if(buf[0] == '0') {
        order = 1;
    } else if(buf[0] == '1') {
        order = -1;
    }

    sort(list, mode, order);
}

void printCards(List* list) {
    puts("Print cards");

    printList(list);
}

void updateDatabase(FILE* db, List* list) {
    db = fopen("db.csv", "w");

    for(Node* t = list->first; t; t = t->next) {
        char* str = countryToString(t->country);
        fwrite(str, sizeof(char), strlen(str), db);
        fflush(db);

        free(str);
        str = NULL;
    }
}