#pragma once

#include <stdio.h>
#include "doubly_linked_list.h"

#define OPTIONS 7

void run(FILE* db, List* list);
void printMenu(void);
void printReference(void);
int isValidInput(char buf[MAXLEN]);