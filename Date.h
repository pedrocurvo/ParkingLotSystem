#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <stdlib.h>

// Structure representing a date
typedef struct Date {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    float cost;
    char* license_plate;
} Date;

/**
 * Calculates the number of days in a given month of a specific year.
 *
 * @param month The month for which to calculate the number of days.
 * @param year The year for which to calculate the number of days.
 * @return The number of days in the specified month of the specified year.
 */
int days_in_month(int month, int year);

/**
 * Calculates the number of minutes between two dates.
 *
 * @param date1 The first date.
 * @param date2 The second date.
 * @return The number of minutes between the two dates.
 */
int minutes_between_dates(Date date1, Date date2);

/**
 * Prints the given date in the format: DD-MM-YYYY.
 *
 * @param date The date to be printed.
 */
void printDate(Date date);

/**
 * Prints the time of the given date in the format: HH:MM.
 *
 * @param date The date object for which the time will be printed.
 */
void printTime(Date date);

/**
 * Checks if one date is after another date.
 *
 * @param date1 The first date.
 * @param date2 The second date.
 * @return 1 if date1 is after date2, 0 otherwise.
 */
int isAfter(Date date1, Date date2);

/**
 * Checks if a date is valid.
 *
 * @param date The date to be checked.
 * @return 1 if the date is valid, 0 otherwise.
 */
int isValid(Date date);

/**
 * Creates a new Date object.
 *
 * @param day The day of the date.
 * @param month The month of the date.
 * @param year The year of the date.
 * @param hour The hour of the date.
 * @param minute The minute of the date.
 * @return A pointer to the newly created Date object.
 */
Date* createDate(int day, int month, int year, int hour, int minute);

/**
 * Destroys a Date object.
 *
 * @param date The Date object to be destroyed.
 */
void destroyDate(Date* date);

#endif /* DATE_H */
