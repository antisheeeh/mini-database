#include <string.h>
#include "stdlib.h"
#include "stdio.h"

#include "../include/input.h"

char** splitLine(char line[MAX_LENGTH]) {
    char** words = malloc(sizeof(*words) * WORDS_IN_LINE);
    if(!words) return NULL;

    char* word = strtok(line, ";");

    for(int i = 0; word; ++i) {
        if(i == WORDS_IN_LINE - 1) {
            word[strlen(word) - 1] = '\0';
        } else {
            word[strlen(word)] = '\0';
        }

        words[i] = malloc(sizeof(*words[i]) * MAXLEN);
        if(!words[i]) return NULL;
        
        strcpy(words[i], word);

        word = strtok(NULL, ";");
    }
    
    return words;
}

void printHeader(void) {
    printf("\n");
    printf("ID     | Name             | Capital          | Area         | Population   | Density      | HDI          | Min height   | Max height    ");
    printf("\n");
    printSepLine();
}

void printSepLine(void) {
    printf("-------+------------------+------------------+--------------+--------------+--------------+--------------+--------------+---------------");
    printf("\n");
}