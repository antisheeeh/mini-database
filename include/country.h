#pragma once

#define MAXLEN 64
#define MAX_LENGTH 256

#define NORMAL -1

typedef struct {
    char name[MAXLEN];
    char capital[MAXLEN];
    int area;
    int population;
    float density;
    float hdi;
    int elevation[2];
} Country;

int compaire(Country* country1, Country* country2, int mode);
Country* getCountryFromConsole(void);
Country* getCountryFromString(char s[MAX_LENGTH], int mode);
char* countryToString(Country* country);
void printCountryInTable(Country* country);
void printCountry(Country* country);