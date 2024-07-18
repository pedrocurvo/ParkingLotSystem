/* iaed24 - ist1102716 - project */
/**
 * Main file containing the main program for a parking system.
 * @file project.c
 * @author ist1102716
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "Parks.h"
#include "Park.h"
#include "Invariants.h"
#include "Records.h"
#include "Engine.h"

// Maximum input size for reading commands
#define MAX_INPUT_SIZE BUFSIZ
// Maximum number of arguments for a command
#define MAX_ARGS 10


int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];

    // Create a Parks object to store the parks
    Parks *parks = create_parks();

    while (1) {
        // Read a line of input from the terminal
        fgets(input, MAX_INPUT_SIZE, stdin);

        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        
        // Tokenize the input into arguments
        int argc = tokenize_input(input, args, MAX_ARGS);
        
        // Process the input command
        if (argc > 0) {
            if (strcmp(args[0], "q") == 0) {
                // Free the memory and exit
                free_parks(parks);
                exit(0);
            } else if (strcmp(args[0], "p") == 0) {
                add_park_command(parks, args, argc);
            } else if (strcmp(args[0], "e") == 0) {
                enter_parking(parks, args);
            } else if (strcmp(args[0], "s") == 0) {
                exit_parking(parks, args);
            } else if (strcmp(args[0], "v") == 0) {
                print_vehicle_history(parks, args);
            } else if (strcmp(args[0], "f") == 0) {
                calculate_cost_command(parks, args, argc);
            } else if (strcmp(args[0], "r") == 0) {
                remove_park_command(parks, args);
            } else {
                printf("Unknown command: %s\n", args[0]);
            }
        }
    }
    return 0;
}