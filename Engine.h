#ifndef ENGINE_H
#define ENGINE_H
#include "Invariants.h"
#include "Parks.h"

/**
 * Prints all the parks in the given Parks structure.
 *
 * @param parks A pointer to the Parks structure containing the parks to be
 * printed.
 */
void print_all_parks(Parks *parks);

/**
 * Adds a park command to the Parks data structure.
 *
 * This function adds a park command to the Parks data structure, based on the
 * provided arguments.
 *
 * @param parks The Parks data structure to add the park command to.
 * @param args An array of strings representing the arguments for the park
 * command.
 * @param argc The number of arguments in the args array.
 */
void add_park_command(Parks *parks, char *args[], int argc);

/**
 * Enters a vehicle into the parking system.
 *
 * @param parks The pointer to the Parks struct representing the parking
 * system.
 * @param args An array of strings representing the arguments for entering the
 * parking.
 */
void enter_parking(Parks *parks, char *args[]);

/**
 * @brief Exits a parking spot.
 *
 * This function allows a vehicle to exit a parking spot in the given `parks`
 * array.
 * The function takes an array of `Parks` structures and a string array `args`
 * as parameters.
 *
 * @param parks The array of `Parks` structures representing the parking spots.
 * @param args The string array containing any additional arguments.
 */
void exit_parking(Parks *parks, char *args[]);

/**
 * Prints the vehicle history for a given park.
 *
 * @param parks The pointer to the Parks struct.
 * @param args The array of arguments.
 */
void print_vehicle_history(Parks *parks, char *args[]);

/**
 * Removes a park from the list of parks.
 *
 * @param parks The pointer to the Parks struct.
 * @param args The array of arguments passed to the command.
 */
void remove_park_command(Parks *parks, char *args[]);

/**
 * Calculates the cost of a command for the given parks.
 *
 * @param parks The pointer to the Parks struct.
 * @param args The array of command arguments.
 * @param argc The number of command arguments.
 */
void calculate_cost_command(Parks *parks, char *args[], int argc);

#endif /* ENGINE_H */
