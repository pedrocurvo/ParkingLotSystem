#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Tokenizes the input string into separate arguments.
 *
 * @param input The input string to be tokenized.
 * @param args The array of strings to store the tokenized arguments.
 * @param max_args The maximum number of arguments that can be stored in the args
 * array.
 * @return The number of arguments tokenized.
 */
int tokenize_input(char *input, char *args[], int max_args);

#endif /* PARSER_H */
