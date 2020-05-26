#include <string.h>
#include "stdlib.h"
#include "stdio.h"

#include "../include/input.h"

void splitLine(char words[WORDS_IN_LINE][MAXLEN], char line[MAX_LENGTH]) {
    char* word = strtok(line, ";");

    for(int i = 0; word; ++i) {
        word[strlen(word)] = '\0';
        strcpy(words[i], word);

        word = strtok(NULL, ";");
    }
}