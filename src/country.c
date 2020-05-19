#include "../include/country.h"

#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_IN_LINE 8

Country* getCountryFromConsole(void) {
    Country *country = malloc(sizeof(*country));
    if(!country) return NULL;

    char buf[MAXLEN];

    printf("Name: ");
    if(!fgets(buf, MAXLEN, stdin)) return NULL;
    buf[strlen(buf) - 1] = '\0';
    strcpy(country->name, buf); 

    printf("Capital: ");
    if(!fgets(buf, MAXLEN, stdin)) return NULL;
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

Country* getCountryFromString(char** str) {
    Country *country = malloc(sizeof(*country));
    if(!country) return NULL;

    strcpy(country->name, str[0]);
    strcpy(country->capital, str[1]);
    country->area = atoi(str[2]);
    country->population = atoi(str[3]);
    country->density = atof(str[4]);
    country->hdi = atof(str[5]);
    country->elevation[0] = atoi(str[6]);
    country->elevation[1] = atoi(str[7]);

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