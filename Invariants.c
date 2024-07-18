/**
 * File containing the implementation of the functions related to the Invariants, i.e.,
 * the functions that check the validity of the input data.
 * @file Invariants.c
 * @author ist1102716
*/
#include "Invariants.h"
#include "Parks.h"
#include "Park.h"
#include <stdlib.h>
#include <string.h>


int ParkAlreadyExists(Parks *parks, char *name) {
    for (int i = 0; i < parks->capacity; i++) {
        if (parks->parks[i] != NULL &&
            strcmp(parks->parks[i]->name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int isCostValid(float price_15, float price_15_1h, float price_1h) {
    if (price_15 <= 0 || price_15_1h <= 0 || price_1h <= 0 ||
        price_15_1h <= price_15 || price_1h <= price_15_1h) {
        return 0;
    }
    return 1;
}

int isCapacityValid(int capacity) {
    if (capacity <= 0) {
        return 0;
    }
    return 1;
}

int isParksMaxed(Parks *parks) {
    if (parks->size >= parks->capacity) {
        return 1;
    }
    return 0;
}

int isValidLicensePlate(const char *plate) {
    int numPairs = 0;
    int letterPairCount = 0;
    int digitPairCount = 0;
    int isLetter = 0;
    int isDigit = 0;

    // Iterate through the characters of the license plate
    for (int i = 0; i < 8; i++) {
        // Check if the character is a hyphen
        if (plate[i] == '-') {
            numPairs++;
            if (isLetter) {
                letterPairCount++;
            } else if (isDigit) {
                digitPairCount++;
            } else {
                return 0; // Invalid pair
            }
            isLetter = 0;
            isDigit = 0;
        } else if (isalpha(plate[i])) { // Check if the character is a letter
            if (isDigit) {
                return 0; // Invalid pair
            }
            isLetter = 1;
        } else if (isdigit(plate[i])) { // Check if the character is a digit
            if (isLetter) {
                return 0; // Invalid pair
            }
            isDigit = 1;
        } else {
            return 0; // Invalid character
        }
    }
    if (numPairs != 2) {
        return 0; // Invalid number of pairs
    } else if (letterPairCount == 1 && digitPairCount == 1) {
        return 1; // Valid license plate
    } else if (letterPairCount == 2 || digitPairCount == 2) {
        // Check if the last character belongs to the right type
        char lastChar = plate[7];
        if ((letterPairCount == 2 && isdigit(lastChar)) || (digitPairCount == 2
                && isalpha(lastChar))) {
            return 1; // Valid license plate
        } else {
            return 0; // Invalid number of letters or digits
        }
    }
    return 0; // Invalid number of letters or digits
}

int isParkFull(Park *park) {
    if (park->available_spots == 0) {
        return 1;
    }
    return 0;
}

int isValidDate(const char *date) {
    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3) {
        return 0; // Format doesn't match DD-MM-YYYY
    }
    if (month < 1 || month > 12) {
        return 0; // Invalid month
    }
    if (day < 1 || day > 31) {
        return 0; // Invalid day
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return 0; // April, June, September, November have 30 days
    }
    if (month == 2) {
        if(day == 29) {
            return 0;
        }
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) {
                return 0; // February in a leap year has 29 days
            }
        } else {
            if (day > 28) {
                return 0; // February has 28 days in a non-leap year
            }
        }
    }
    return 1;
}


int isValidTime(const char *time) {
    int hour, minute;
    if (sscanf(time, "%d:%d", &hour, &minute) != 2) {
        return 0; // Format doesn't match HH:MM
    }
    if (hour < 0 || hour > 23) {
        return 0; // Invalid hour
    }
    if (minute < 0 || minute > 59) {
        return 0; // Invalid minute
    }
    return 1;
}

