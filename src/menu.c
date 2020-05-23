#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/database.h"

#ifdef linux
#define CLS system("clear")
#else
#define CLS system("cls")
#endif

#include "../include/menu.h"

void run(FILE* db, List* list) {
    int c, error = 0;

    char buf[MAXLEN];

    while(1) {
        printMenu();

        do {
            puts("Enter your choice");
            fgets(buf, MAXLEN, stdin);

            if(error = !isValidInput(buf)) {
                puts("Input is incorrect! Please try again\n");
            } else if(buf[0] == 'Q') {
                CLS;
                return;
            } else {
                CLS;

                int mode = buf[0] - '0';
                
                if(mode == 0) {
                    printReference();
                } else if(mode == 1) {
                    addCard(list);
                } else if(mode == 2) {
                    editCard(list);
                } else if(mode == 3) {
                    deleteCard(list);
                } else if(mode == 4) {
                    searchCard(list);
                } else if(mode == 5) {
                    sortCards(list);
                } else if(mode == 6) {
                    printCards(list);
                }

                updateDatabase(db, list);
                puts("\nPress any key to continue...");
                fgets(buf, MAXLEN, stdin);
            }
        } while(error);

        CLS;
    }
}

int isValidInput(char buf[MAXLEN]) {
    return strlen(buf) == 2 && (buf[0] == 'Q' || '0' <= buf[0] && buf[0] <= '6');
}

void printMenu(void) {
    puts("Main menu");
    puts("");
    puts("0 - Reference");
    puts("1 - Add card");
    puts("2 - Edit card");
    puts("3 - Delete card");
    puts("4 - Search card");
    puts("5 - Sort cards");
    puts("6 - Print cards");
    puts("Q - Exit");
    puts("");
}

void printReference(void) {
    puts("Reference\n");
    puts("This is a mini database developed in C");
    puts("Author - Kirill Konoplev\n");
    puts("All data is saved in the db.csv file in the directory with the executable file\n");
    puts("There are the following operations:");
    puts("*  Adding cards");
    puts("*  Editing cards");
    puts("*  Removing cards");
    puts("*  Output all cards");
    puts("*  Search cards by request");
    puts("*  Sort cards by request");
}