#pragma once

#include <stdio.h>
#include "doubly_linked_list.h"

void addCard(List* list);
void editCard(List* list);
void deleteCard(List* list);
void searchCard(List* list);
void sortCards(List* list);
void printCards(List* list);
void updateDatabase(FILE* db, List* list);