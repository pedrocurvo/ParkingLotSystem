#ifndef PARK_H
#define PARK_H

#include <stdlib.h>
#include "Records.h" // Include Records.h for ParkRecord structure
#include "Date.h"

typedef struct Park{
    char* name;
    int capacity;
    int available_spots;
    float price_15;
    float price_15_1h;
    float price_1h;

    HashMap *records_map;

    int id;

    Date *lastDate;  // Pointer to Date for lastDateIn
} Park;


/**
 * Creates a new Park object with the specified parameters.
 *
 * @param name The name of the park.
 * @param capacity The maximum capacity of the park.
 * @param price_15 The price for 15 minutes of parking.
 * @param price_15_1h The price for the first hour of parking after the initial 15 minutes.
 * @param price_1h The price for each additional hour of parking after the first hour.
 * @param id The unique identifier of the park.
 * @return A pointer to the newly created Park object.
 */
Park* create_park(const char *name, int capacity, float price_15,
                    float price_15_1h, float price_1h, int id);


/**
 * Prints the details of a park.
 *
 * @param park A pointer to the Park structure to be printed.
 */
void print_park(Park* park);


/**
 * @brief Destroys all records in the park.
 *
 * This function is responsible for destroying all records in the park, freeing
 * up the memory used by each record.
 *
 * @param park A pointer to the Park structure.
 */
void destroy_records_in_park(Park *park);


/**
 * @brief Destroys all records associated with a given license plate in the park.
 *
 * This function removes all records in the park that are associated with the
 * specified license plate.
 *
 * @param park The park object.
 * @param license_plate The license plate to search for and destroy records.
 */
void destroy_records_for_license_plate(Park *park, const char *license_plate);


/**
 * Calculates the cost of parking at the specified park for the given in and
 * out dates.
 *
 * @param park      The park for which to calculate the cost.
 * @param in_date   The date and time the vehicle entered the park.
 * @param out_date  The date and time the vehicle exited the park.
 *
 * @return The cost of parking at the park for the specified duration.
 */
float calculate_cost(Park* park, Date* in_date, Date* out_date);


/**
 * @brief Destroys a Park object.
 *
 * This function frees the memory allocated for a Park object and all its
 * associated resources.
 *
 * @param park A pointer to the Park object to be destroyed.
 */
void destroy_park(Park *park);


/**
 * Retrieves the cost records for a specific date in the park.
 *
 * This function retrieves the cost records for a specific date in the park.
 * The cost records include information about the expenses and revenues for
 * that date.
 *
 * @param park The park for which to retrieve the cost records.
 * @param date The date for which to retrieve the cost records.
 */
void get_cost_records_for_date(Park* park, Date* date);


/**
 * Calculates the cost of records per park.
 *
 * This function takes a pointer to a Park structure and calculates the cost of
 * records per park.
 *
 * @param park A pointer to a Park structure.
 * @return The cost of records per park as a float value.
 */
void get_cost_records_per_park(Park* park);

#endif /* PARK_H */
