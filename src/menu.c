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

void (*options[OPTIONS])();

void initMenu(void) {
    options[0] = printReference;
    options[1] = addCard;
    options[2] = editCard;
    options[3] = deleteCard;
    options[4] = searchCard;
    options[5] = sortCards;
    options[6] = printCards;
}

void run(FILE* db, List* list) {
    initMenu();

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
                options[buf[0] - '0'](list);
                updateDatabase(db, list);
                puts("Press any key to continue...");
                getchar();
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
}