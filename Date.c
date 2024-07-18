/**
 * File containing the implementation of the functions related to the Date Structure.
 * @file Date.c
 * @author ist1102716
*/
#include "Date.h"

// Function to calculate the number of days in a month
int days_in_month(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // Leap year check
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                return 29;
            else
                return 28;
        default:
            return 0; // Invalid month
    }
}

// Function to calculate the difference in minutes between two dates
int minutes_between_dates(Date date1, Date date2) {
    int minutes = 0;

    // Calculate total minutes for date1
    minutes += date1.minute;
    minutes += date1.hour * 60;
    minutes += (date1.day - 1) * 24 * 60; // Subtract one day for the current day
    for (int m = 1; m < date1.month; m++) {
        minutes += days_in_month(m, date1.year) * 24 * 60;
    }
    for (int y = 1; y < date1.year; y++) {
        int leap_year = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        minutes += (365 + leap_year) * 24 * 60;
    }

    // Subtract total minutes for date2
    minutes -= date2.minute;
    minutes -= (date2.hour * 60);
    minutes -= (date2.day - 1) * 24 * 60; // Subtract one day for the current day
    for (int m = 1; m < date2.month; m++) {
        minutes -= days_in_month(m, date2.year) * 24 * 60;
    }
    for (int y = 1; y < date2.year; y++) {
        int leap_year = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        minutes -= (365 + leap_year) * 24 * 60;
    }

    return abs(minutes);
}

// Function to print the date in the format: DD-MM-YYYY
void printDate(Date date) {
    printf("%02d-%02d-%04d", date.day, date.month, date.year);
}

// Function to print the time in the format: HH:MM
void printTime(Date date) {
    printf("%02d:%02d", date.hour, date.minute);
}

// Function to check if one date is after another date
int isAfter(Date date1, Date date2) {
    if (date1.year > date2.year)
        return 1;
    else if (date1.year < date2.year)
        return 0;
    else {
        if (date1.month > date2.month)
            return 1;
        else if (date1.month < date2.month)
            return 0;
        else {
            if (date1.day > date2.day)
                return 1;
            else if (date1.day < date2.day)
                return 0;
            else {
                if (date1.hour > date2.hour)
                    return 1;
                else if (date1.hour < date2.hour)
                    return 0;
                else {
                    if (date1.minute >= date2.minute)
                        return 1;
                    else
                        return 0;
                }
            }
        }
    }
}

// Function to check if a date is valid
int isValid(Date date) {
    // Check for valid year, month, day, hour, and minute
    if (date.year < 0 || date.month < 1 || date.month > 12 || date.day < 1 ||
        date.hour < 0 || date.hour > 23 || date.minute < 0 || date.minute > 59)
        return 0;

    // Check for valid days in month
    if (date.day > days_in_month(date.month, date.year))
        return 0;

    return 1;
}

// Function to create a new Date object
Date* createDate(int day, int month, int year, int hour, int minute) {
    // Allocate memory for a Date structure
    Date* date = (Date*)malloc(sizeof(Date));
    if (date == NULL) {
        // Memory allocation failed
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Assign values to the Date structure
    date->day = day;
    date->month = month;
    date->year = year;
    date->hour = hour;
    date->minute = minute;
    date->cost = 0;

    // Allocate memory for license_plate
    date->license_plate = NULL;

    // Return a pointer to the allocated Date structure
    return date;
}

// Function to deallocate memory for a Date object
void destroyDate(Date* date) {
    if (date != NULL) {
        // Free memory for license_plate if allocated
    if (date->license_plate != NULL) {
        free(date->license_plate);
    }
        free(date); // Deallocate the Date structure memory
    }
}
