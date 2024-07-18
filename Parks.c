/**
 * File containing the implementation of the functions related to the Parks Structure.
 * @file Parks.c
 * @author ist1102716
*/
#include "Parks.h"
#include "Park.h"
#include <stdlib.h>
#include <string.h>

Parks *create_parks() {
    Parks *parking_lots = (Parks *)malloc(sizeof(Parks));
    if (parking_lots == NULL) {
        return NULL; // Memory allocation failed
    }
    parking_lots->size = 0;
    parking_lots->capacity = MAX_LOTS;
    parking_lots->parks_id = 0;
    parking_lots->parks = (Park **)calloc(MAX_LOTS, sizeof(Park *));
    if (parking_lots->parks == NULL) {
        free(parking_lots);
        return NULL; // Memory allocation failed
    }
    for (int i = 0; i < MAX_LOTS; i++) {
        parking_lots->parks[i] = NULL;
    }
    return parking_lots;
}

void add_park(Parks* parks, Park* park){
    if (parks->size >= parks->capacity) {
        return; // Maximum lots reached
    }

    for (int i = 0; i < parks->capacity; i++) {
        if (parks->parks[i] == NULL) {
            parks->parks[i] = park;
            parks->size++;
            return;
        }
    }
}

void remove_park(Parks* parks, const char* park_name) {
    for (int i = 0; i < parks->size; i++) {
        if (strcmp(parks->parks[i]->name, park_name) == 0) {
            destroy_park(parks->parks[i]);
            free(parks->parks[i]);
            parks->parks[i] = parks->parks[parks->size - 1];
            parks->parks[parks->size - 1] = NULL;
            parks->size--;
            break;
        }
    }
}

Park* get_park(Parks* parks, char* name){
    for (int i = 0; i < parks->capacity; i++) {
        if (parks->parks[i] != NULL && strcmp(parks->parks[i]->name, name) == 0) {
            return parks->parks[i];
        }
    }
    return NULL;
}

void print_parks(Parks* parks){
    for (int i = 0; i < parks->capacity; i++) {
        if (parks->parks[i] != NULL) {
            print_park(parks->parks[i]);
        }
    }
}

void free_parks(Parks* parks) {
    if (parks == NULL) {
        return;
    }
    for (int i = 0; i < parks->size; i++) {
        if (parks->parks[i] != NULL) {
            destroy_park(parks->parks[i]);
        }
    }
    free(parks->parks);
    free(parks);
}

// Helper function to compare two park names
int compare_names(const char *a, const char *b) {
    return strcmp(a, b);
}

// Function to return a list of park names ordered alphabetically
char** get_park_names_ordered(Parks* parks, int* count) {
    char** names = (char**)malloc(parks->size * sizeof(char*));
    if (names == NULL) {
        *count = 0;
        return NULL; // Memory allocation failed
    }

    *count = 0;
    for (int i = 0; i < parks->capacity; i++) {
        if (parks->parks[i] != NULL) {
            // Allocate memory for the name and copy it
            names[*count] = strdup(parks->parks[i]->name);
            if (names[*count] == NULL) {
                // Memory allocation failed, clean up and return
                for (int j = 0; j < *count; j++) {
                    free(names[j]);
                }
                free(names);
                *count = 0;
                return NULL;
            }
            (*count)++;
        }
    }

    // Sort the names alphabetically using bubble sort
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (compare_names(names[j], names[j + 1]) > 0) {
                char* temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }

    return names;
}

// Function to free memory allocated for the list of park names
void free_park_names(char** names, int count) {
    if (names != NULL) {
        for (int i = 0; i < count; i++) {
            free(names[i]);
        }
        free(names);
    }
}

// Function to return a list of parks ordered by ID
Park** get_parks_ordered_by_id(Parks* parks, int* count) {
    // Allocate memory for an array of park pointers
    Park** ordered_parks = (Park**)malloc(parks->size * sizeof(Park*));
    if (ordered_parks == NULL) {
        *count = 0;
        return NULL; // Memory allocation failed
    }

    // Initialize ordered_parks array to NULL
    for (int i = 0; i < parks->size; i++) {
        ordered_parks[i] = NULL;
    }

    // Fill the array with park pointers
    *count = 0;
    for (int i = 0; i < parks->capacity; i++) {
        if (parks->parks[i] != NULL && parks->parks[i]->name != NULL) {
            ordered_parks[*count] = parks->parks[i];
            (*count)++;
        }
    }

    // Sort the parks by ID using bubble sort
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (ordered_parks[j]->id > ordered_parks[j + 1]->id) {
                Park* temp = ordered_parks[j];
                ordered_parks[j] = ordered_parks[j + 1];
                ordered_parks[j + 1] = temp;
            }
        }
    }

    return ordered_parks;
}

// Function to free memory allocated for the list of parks
void free_ordered_parks(Park** parks) {
    free(parks);
}

void print_park_names_ordered_by_id(Park** ordered_parks, int count) {
    for (int i = 0; i < count; i++) {
        print_park(ordered_parks[i]);
    }
}
