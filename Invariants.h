#ifndef INVARIANTS_H
#define INVARIANTS_H

#include "Parks.h"
#include "Park.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/**
 * Checks if a park with the given name already exists in the array of parks.
 *
 * @param parks The array of parks to search in.
 * @param name The name of the park to check for existence.
 * @return 1 if a park with the given name already exists, 0 otherwise.
 */
int ParkAlreadyExists(Parks* parks, char* name);


/**
 * Checks if the given capacity is valid.
 *
 * @param capacity The capacity to be checked.
 * @return 1 if the capacity is valid, 0 otherwise.
 */
int isCapacityValid(int capacity);


/**
 * Checks if the cost values for different time intervals are valid.
 *
 * This function takes in three cost values: `cost_15min`, `cost_15_1h`, 
 * and `cost_day`.
 * It checks if these cost values are valid according to some criteria.
 *
 * @param cost_15min The cost for a 15-minute interval.
 * @param cost_15_1h The cost for a 15-minute to 1-hour interval.
 * @param cost_day The cost for a full day interval.
 *
 * @return 1 if the cost values are valid, 0 otherwise.
 */
int isCostValid(float cost_15min, float cost_15_1h, float cost_day);


/**
 * Checks if the given Parks object is maxed.
 *
 * @param parks A pointer to the Parks object to check.
 * @return 1 if the Parks object is maxed, 0 otherwise.
 */
int isParksMaxed(Parks* parks);


/**
 * Checks if a given license plate is valid.
 *
 * @param plate The license plate to be checked.
 * @return 1 if the license plate is valid, 0 otherwise.
 */
int isValidLicensePlate(const char *plate);


/**
 * Checks if the park is full.
 *
 * This function takes a pointer to a Park structure and checks if the park is 
 * full.
 * A park is considered full if there are no available parking spaces.
 *
 * @param park A pointer to the Park structure.
 * @return 1 if the park is full, 0 otherwise.
 */
int isParkFull(Park* park);


/**
 * Checks if a given date is valid.
 *
 * @param date The date to be checked.
 * @return 1 if the date is valid, 0 otherwise.
 */
int isValidDate(const char *date);


/**
 * Checks if the given time string is valid.
 *
 * @param time The time string to be validated.
 * @return 1 if the time is valid, 0 otherwise.
 */
int isValidTime(const char *time);

#endif /* INVARIANTS_H */
