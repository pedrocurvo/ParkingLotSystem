#ifndef PARKS_H
#define PARKS_H

#include "Park.h"

#define MAX_LOTS 20

/**
 * @struct Parks
 * @brief Represents a park.
 *
 * This struct is used to store information about a park.
 * It can be used to represent various attributes of a park.
 */
typedef struct Parks{
    Park** parks;
    int size;
    int capacity;

    int parks_id;
} Parks;


/**
 * Creates a new instance of the Parks struct.
 *
 * @return A pointer to the newly created Parks struct.
 */
Parks* create_parks();

/**
 * Adds a park to the parks collection.
 *
 * @param parks The pointer to the Parks struct.
 * @param park The pointer to the Park struct to be added.
 */
void add_park(Parks* parks, Park* park);

/**
 * Removes a park from the parks collection.
 *
 * @param parks The pointer to the Parks struct.
 * @param name The name of the park to be removed.
 */
void remove_park(Parks* parks, const char* name);

/**
 * Gets a park from the parks collection.
 *
 * @param parks The pointer to the Parks struct.
 * @param name The name of the park to be retrieved.
 * @return A pointer to the Park struct if found, NULL otherwise.
 */
Park* get_park(Parks* parks, char* name);

/**
 * Prints the details of all parks in the parks collection.
 *
 * @param parks The pointer to the Parks struct.
 */
void print_parks(Parks* parks);

/**
 * Frees the memory allocated for the Parks struct.
 *
 * @param parks The pointer to the Parks struct to be freed.
 */
void free_parks(Parks* parks);


/**
 * Compares two names.
 *
 * This function compares two names, `a` and `b`, and returns an integer value
 * indicating their relative order. The comparison is case-sensitive.
 *
 * @param a The first name to compare.
 * @param b The second name to compare.
 * @return An integer value less than, equal to, or greater than zero if `a` is
 *         found, respectively, to be less than, equal to, or greater than `b`.
 */
int compare_names(const char *a, const char *b);

/**
 * Frees the memory allocated for an array of park names.
 *
 * @param names The array of park names to be freed.
 * @param count The number of park names in the array.
 */
void free_park_names(char** names, int count);

/**
 * Gets an array of park names ordered by name.
 *
 * @param parks The pointer to the Parks struct.
 * @param count A pointer to an integer to store the number of park names.
 * @return An array of park names ordered by name.
 */
char** get_park_names_ordered(Parks* parks, int* count);

/**
 * Compares the ids of the parks for sort.
 *
 * @param names The array of park names to be printed.
 * @param count The number of park names in the array.
 */
int compare_ids(const void *a, const void *b);

/**
 * Gets an array of parks ordered by id.
 *
 * @param parks The pointer to the Parks struct.
 * @param count A pointer to an integer to store the number of parks.
 * @return An array of parks ordered by id.
 */
Park** get_parks_ordered_by_id(Parks* parks, int* count);

/**
 * Frees the memory allocated for an array of parks.
 *
 * @param parks The array of parks to be freed.
 */
void free_ordered_parks(Park** parks);

/**
 * Prints the names of the parks in the given array.
 *
 * @param ordered_parks The array of park names to be printed.
 * @param count The number of park names in the array.
 */
void print_park_names_ordered_by_id(Park** ordered_parks, int count);

#endif /* PARKS_H */
