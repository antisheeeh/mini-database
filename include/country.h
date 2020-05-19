#pragma once

#define MAXLEN 64

typedef struct {
    char name[MAXLEN];
    char capital[MAXLEN];
    int area;
    int population;
    float density;
    float hdi;
    int elevation[2];
} Country;

Country* getCountryFromConsole(void);
Country* getCountryFromString(char** str);
char* countryToString(Country* country);
void printCountryInTable(Country* country);
void printCountry(Country* country);