#include <string.h>
#include "stdlib.h"
#include "stdio.h"

#include "../include/input.h"

char** splitLine(char line[MAX_LENGTH]) {
    char** words = malloc(sizeof(char*) * WORDS_IN_LINE);
    if(!words) return NULL;

    char* word = strtok(line, ";");

    int i;

    for(i = 0; word; ++i) {
        word[strlen(word)] = '\0';

        words[i] = malloc(sizeof(char) * MAXLEN);
        if(!words[i]) return NULL;
        
        strcpy(words[i], word);

        word = strtok(NULL, ";");
    }

    words[i] = '\0';
    
    return words;
}