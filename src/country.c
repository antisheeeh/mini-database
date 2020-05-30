#include "../include/country.h"

#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_IN_LINE 8

int compaire(Country* country1, Country* country2, int mode) {
    if(mode == 0) {
        return strcmp(country1->name, country2->name);
    } else if(mode == 1) {
        return strcmp(country1->capital, country2->capital);
    } else if(mode == 2) {
        return country1->area - country2->area;
    } else if(mode == 3) {
        return country1->population - country2->population;
    } else if(mode == 4) {
        return country1->density - country2->density;
    } else if(mode == 5) {
        return country1->hdi - country2->hdi;
    } else if(mode == 6) {
        return country1->elevation[0] - country2->elevation[0];
    } else if(mode == 7) {
        return country1->elevation[1] - country2->elevation[1];
    }
}
 
Country* getCountryFromConsole(void) {
    Country *country = malloc(sizeof(*country));
    if(!country) return NULL;

    char buf[MAXLEN];

    printf("Name: ");
    if(!fgets(buf, MAXLEN, stdin) || strlen(buf) == 1) return NULL;
    buf[strlen(buf) - 1] = '\0';
    strcpy(country->name, buf); 

    printf("Capital: ");
    if(!fgets(buf, MAXLEN, stdin) || strlen(buf) == 1) return NULL;
    buf[strlen(buf) - 1] = '\0';
    strcpy(country->capital, buf);

    printf("Area: ");
    fgets(buf, MAXLEN, stdin);
    country->area = atoi(buf);
    if(!country->area && buf[0] != '0') return NULL;;

    printf("Population: ");
    fgets(buf, MAXLEN, stdin);
    country->population = atoi(buf);
    if(!country->population && buf[0] != '0') return NULL;

    printf("Density: ");
    fgets(buf, MAXLEN, stdin);
    country->density = atof(buf);
    if(!country->density && buf[0] != '0') return NULL;

    printf("HDI: ");
    fgets(buf, MAXLEN, stdin);
    country->hdi = atof(buf);
    if(!country->hdi && buf[0] != '0') return NULL;

    printf("Min height: ");
    fgets(buf, MAXLEN, stdin);
    country->elevation[0] = atoi(buf);
    if(!country->elevation[0] && buf[0] != '0') return NULL;;

    printf("Max height: ");
    fgets(buf, MAXLEN, stdin);
    country->elevation[1] = atoi(buf);
    if(!country->elevation[1] && buf[0] != '0') return NULL;

    return country;
}

Country* getCountryFromString(char s[MAX_LENGTH], int mode) {
    if(!s) return NULL;
    s[strlen(s)] = '\0';

    Country *country = malloc(sizeof(*country));
    if(!country) return NULL;

    if(0 <= mode && mode <= 7) {
        strcpy(country->name, "0");
        strcpy(country->capital, "0");
        country->area = 0;
        country->population = 0;
        country->density = 0;
        country->hdi = 0;
        country->elevation[0] = 0;
        country->elevation[1] = 0;

        if(mode == 0) {
            strcpy(country->name, s);
        } else if(mode == 1) {
            strcpy(country->capital, s);
        } else if(mode == 2) {
            country->area = atoi(s);
        } else if(mode == 3) {
            country->population = atoi(s);
        } else if(mode == 4) {
            country->density = atof(s);
        } else if(mode == 5) {
            country->hdi = atof(s);
        } else if(mode == 6) {
            country->elevation[0] = atoi(s);
        } else if(mode == 7) {
            country->elevation[1] = atoi(s);
        }
    } else if(mode == NORMAL) {
        char str[WORDS_IN_LINE][MAXLEN];
        splitLine(str, s);

        strcpy(country->name, str[0]);
        strcpy(country->capital, str[1]);
        country->area = atoi(str[2]);
        country->population = atoi(str[3]);
        country->density = atof(str[4]);
        country->hdi = atof(str[5]);
        country->elevation[0] = atoi(str[6]);
        country->elevation[1] = atoi(str[7]);
    }

    return country;
}

char* countryToString(Country* country) {
    int len = 0;
    len = snprintf(NULL, len, "%s;%s;%d;%d;%f;%f;%d;%d", country->name, country->capital, country->area, 
    country->population, country->density, country->hdi, country->elevation[0], country->elevation[1]);

    char* str = malloc(len + 2);
    
    snprintf(str, len + 2, "%s;%s;%d;%d;%f;%f;%d;%d\n", country->name, country->capital, country->area, 
    country->population, country->density, country->hdi, country->elevation[0], country->elevation[1]);

    return str;
}

void printCountryInTable(Country *country) {
    if(!country) return;
    
    printf("%-16s | ", country->name);
    printf("%-16s | ", country->capital);
    printf("%-12d | ", country->area);
    printf("%-12d | ", country->population);
    printf("%-12.3f | ", country->density);
    printf("%-12.3f | ", country->hdi);
    printf("%-12d | ", country->elevation[0]);
    printf("%-12d", country->elevation[1]);
    printf("\n");
}

void printCountry(Country* country) {
    if(!country) return;

    printf("Name: %s ", country->name);
    printf("Capital: %s ", country->capital);
    printf("Area: %d ", country->area);
    printf("Population: %d ", country->population);
    printf("Density: %f ", country->density);
    printf("HDI: %f ", country->hdi);
    printf("Min height: %d ", country->elevation[0]);
    printf("Max height: %d", country->elevation[1]);
    printf("\n\n");
}