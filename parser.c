/**
 * File containing the implementation of a function to tokenize input strings into arguments.
 * @file parser.c
 * @author ist1102716
*/

#include "parser.h"
#include <stdio.h>

// Function to tokenize input string into arguments
int tokenize_input(char *input, char *args[], int max_args) {
    int count = 0;
    char *arg_start = NULL;
    char *quote_start = NULL; // Pointer to the starting quote
    int inside_quote = 0; // Flag to indicate if currently inside a quote
    
    // Iterate through each character in the input string
    for (char *p = input; *p != '\0' && count < max_args - 1; p++) {
        if (*p == '"' && !inside_quote) {
            // Start of a quoted string
            inside_quote = 1;
            quote_start = p + 1; // Move quote_start to the character after the
                                // leading quote
            arg_start = quote_start; // Set arg_start to the same position as
                                    // quote_start
        } else if (*p == '"' && inside_quote) {
            // End of a quoted string
            if (*(p + 1) == ' ' || *(p + 1) == '\0') {
                // If the next character is a space or end of string,
                // close the quote
                *p = '\0'; // Replace the closing quote with null terminator
                args[count++] = arg_start;
                inside_quote = 0;
                arg_start = NULL; // Reset arg_start
            } else {
                // If the next character is not a space, continue the quoted
                // string
                continue;
            }
        } else if (*p == ' ' && !inside_quote) {
            // End of an unquoted string
            *p = '\0'; // Replace the space with null terminator
            if (arg_start != NULL) {
                args[count++] = arg_start;
            }
            arg_start = NULL; // Reset arg_start
        } else if (*p != ' ' && arg_start == NULL) {
            // Start of an unquoted string
            arg_start = p; // Set arg_start to the current character
        }
    }

    // Add the last argument if any
    if (arg_start != NULL) {
        args[count++] = arg_start;
    }

    args[count] = NULL; // Null-terminate the argument list
    return count;
}





