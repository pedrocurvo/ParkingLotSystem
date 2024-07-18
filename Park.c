/**
 * File containing the implementation of the functions related to the Park Structure.
 * @file Park.c
 * @author ist1102716
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Park.h"
#include "Records.h" // Include Records.h for ParkRecord structure and hash functions
#include "Date.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

#define ceil(x) ((int)(x + 0.999999999))

Park *create_park(const char *name, int capacity, float price_15,
                    float price_15_1h, float price_1h, int id) {
    Park *park = (Park *)malloc(sizeof(Park));
    if (park == NULL) {
        return NULL; // Memory allocation failed
    }
    park->name = (char *)malloc(strlen(name) + 1);
    if (park->name == NULL) {
        free(park);
        return NULL; // Memory allocation failed
    }
    strcpy(park->name, name);
    park->capacity = capacity;
    park->available_spots = capacity;
    park->price_15 = price_15;
    park->price_15_1h = price_15_1h;
    park->price_1h = price_1h;
    park->id = id;
    park->records_map = create_hash_map();
    park->lastDate = NULL;
    if(park->records_map == NULL){
        free(park->name);
        free(park);
        return NULL;
    }
    return park;
}

void print_park(Park *park) {
    printf("%s ", park->name);
    printf("%d ", park->capacity);
    printf("%d\n", park->available_spots);
}

void destroy_records_in_park(Park *park) {
    if (park == NULL || park->records_map == NULL) {
        return;
    }

    for (int i = 0; i < park->records_map->size; i++) {
        HashNode *current = park->records_map->buckets[i];
        while (current != NULL) {
            RecordNode *record_current = current->records;
            while (record_current != NULL) {
                RecordNode *temp = record_current;
                record_current = record_current->next;
                free(temp);  // Free each RecordNode individually
            }
            // Move to the next HashNode without freeing it
            HashNode *temp = current;
            current = current->next;
            free(temp);  // Free the HashNode once all records are freed
        }
    }
    free(park->records_map->buckets);
    free(park->records_map);
}

void destroy_records_for_license_plate(Park *park, const char *license_plate) {
    if (park == NULL || park->records_map == NULL) {
        return;
    }

    int index = hash(license_plate, park->records_map->size);
    HashNode *current = park->records_map->buckets[index];
    HashNode *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->vehicle_license_plate, license_plate) == 0) {
            // Found the hash node for the given license plate
            // Free the linked list of records associated with this license 
            // plate
            RecordNode *record_current = current->records;
            while (record_current != NULL) {
                RecordNode *temp = record_current;
                record_current = record_current->next;
                free(temp);
            }
            current->records = NULL; // Reset records pointer
            // Remove the hash node if there are no more records associated 
            // with this license plate
            if (prev == NULL) {
                park->records_map->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int isLeapYear(int year){
    if(year % 4 == 0){
        if(year % 100 == 0){
            if(year % 400 == 0){
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
};

float calculate_cost(Park* park, Date* in_date, Date* out_date){

    int total_minutes = minutes_between_dates(*out_date, *in_date);

    float X = park->price_15;
    float Y = park->price_15_1h;
    float Z = park->price_1h;

    // Total number of minutes in a day
    int total_minutes_in_day = 24 * 60;

    // Calculate the number of days
    int days = total_minutes / total_minutes_in_day;

    // Calculate the remaining minutes
    int remaining_minutes = total_minutes % total_minutes_in_day;

    // Calculate the number of 15 minute intervals
    float intervals = ceil(remaining_minutes / 15.);

    // Calculate the cost for the remaining minutes
    double cost = 0;
    if (intervals <= 4) {
        cost = X * intervals;
    } else {
        cost = X * 4 + Y * (intervals - 4);
    }
    cost = min(cost, Z); // Cap the cost to Z

    // Calculate the total cost
    double total_cost = days * Z + cost;

    //Check if the start and end years have a leap year between them
    int count = 0;

    // If start and end year are same, check if it's a leap year
    if (in_date->year == out_date->year && isLeapYear(in_date->year)) {
        if (in_date->month <= 2 && out_date->month > 2) {
            count++;
        }
    } else {
        // First lets check the start year
        if (isLeapYear(in_date->year)) {
            if (in_date->month <= 2) {
                count++;
            }
        }
        // Now check the end year
        if (isLeapYear(out_date->year)) {
            if (out_date->month > 2) {
                count++;
            }
        }
        // Now check the years in between
        for(int i = in_date->year + 1; i < out_date->year; i++) {
            if (isLeapYear(i)) {
                count++;
            }
        }
    }
    return total_cost - count * Z;
}

void destroy_park(Park *park) {
    if (park == NULL) {
        return;
    }
    free(park->name);
    destroyDate(park->lastDate);

    destroy_records_in_park(park);
}

// Function to compare dates
int compare_dates(const void *a, const void *b) {
    const Date *date1 = (const Date *)a;
    const Date *date2 = (const Date *)b;

    // Compare years
    if (date1->year != date2->year)
        return date1->year - date2->year;

    // Compare months
    if (date1->month != date2->month)
        return date1->month - date2->month;

    // Compare days
    if (date1->day != date2->day)
        return date1->day - date2->day;

    // Compare hours
    if (date1->hour != date2->hour)
        return date1->hour - date2->hour;

    // Compare minutes
    return date1->minute - date2->minute;
}

// Bubble sort implementation for sorting dates
void bubble_sort_dates(Date *dates, int num_dates) {
    int i, j;
    for (i = 0; i < num_dates - 1; i++) {
        for (j = 0; j < num_dates - i - 1; j++) {
            // Compare two consecutive dates
            if (compare_dates(&dates[j], &dates[j + 1]) > 0) {
                // Swap the dates if they are in the wrong order
                Date temp = dates[j];
                dates[j] = dates[j + 1];
                dates[j + 1] = temp;
            }
        }
    }
}

void get_cost_records_per_park(Park* park) {
    // Allocate memory for the dates array
    int num_dates = 0; // Actual number of different dates
    Date *dates = (Date *)malloc(sizeof(Date) * park->records_map->size);

    // Initialize the dates array
    for (int i = 0; i < park->records_map->size; i++) {
        dates[i].day = 0;
        dates[i].month = 0;
        dates[i].year = 0;
        dates[i].cost = 0.0;
    }

    // Iterate through the records and update the dates array
    for (int i = 0; i < park->records_map->size; i++) {
        HashNode *current = park->records_map->buckets[i];
        while (current != NULL) {
            RecordNode *record_current = current->records;
            while (record_current != NULL) {
                if (record_current->record.out_date != NULL) {
                    int found = 0;
                    for (int j = 0; j < num_dates; j++) {
                        if (dates[j].day == record_current->record.out_date->day &&
                            dates[j].month == record_current->record.out_date->month &&
                            dates[j].year == record_current->record.out_date->year) {
                            dates[j].cost += record_current->record.cost;
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        dates[num_dates].day = record_current->record.out_date->day;
                        dates[num_dates].month = record_current->record.out_date->month;
                        dates[num_dates].year = record_current->record.out_date->year;
                        dates[num_dates].cost += record_current->record.cost;
                        num_dates++;
                    }
                }
                record_current = record_current->next;
            }
            current = current->next;
        }
    }

    // Sort dates array based on date values
    bubble_sort_dates(dates, num_dates);

    // Print the Dates and the total cost
    for (int i = 0; i < num_dates; i++) {
        printf("%02d-%02d-%d %.2f\n", dates[i].day, dates[i].month,
        dates[i].year, dates[i].cost);
    }

    // Free allocated memory
    free(dates);
}

void get_cost_records_for_date(Park* park, Date* date) {
    // Allocate memory for the dates array
    int num_dates = 0; // Actual number of different dates
    Date* dates = (Date*)malloc(sizeof(Date) * park->records_map->size);
    if (dates == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Initialize the dates array
    for (int i = 0; i < park->records_map->size; i++) {
        dates[i].day = 0;
        dates[i].month = 0;
        dates[i].year = 0;
        dates[i].hour = 0;
        dates[i].minute = 0;
        dates[i].cost = 0.0;
        // Assuming license_plate is a string, allocate memory and copy it
        dates[i].license_plate = strdup("");
        if (dates[i].license_plate == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            // Free previously allocated memory
            for (int j = 0; j < num_dates; j++) {
                free(dates[j].license_plate);
            }
            free(dates);
            return;
        }
    }

    // Traverse the records map to find records for the given date
    for (int i = 0; i < park->records_map->size; i++) {
        HashNode* current = park->records_map->buckets[i];
        while (current != NULL) {
            RecordNode* record_current = current->records;
            while (record_current != NULL) {
                if (record_current->record.out_date != NULL &&
                    record_current->record.out_date->day == date->day &&
                    record_current->record.out_date->month == date->month &&
                    record_current->record.out_date->year == date->year) {
                    
                    // Update the date
                    dates[num_dates].day = record_current->record.out_date->day;
                    dates[num_dates].month = record_current->record.out_date->month;
                    dates[num_dates].year = record_current->record.out_date->year;
                    dates[num_dates].hour = record_current->record.out_date->hour;
                    dates[num_dates].minute = record_current->record.out_date->minute;
                    dates[num_dates].cost = record_current->record.cost;
                    // Copy license_plate
                    free(dates[num_dates].license_plate); // Free previously allocated memory
                    dates[num_dates].license_plate = strdup(record_current->record.license_plate);
                    if (dates[num_dates].license_plate == NULL) {
                        // Handle memory allocation failure
                        fprintf(stderr, "Memory allocation failed\n");
                        // Free allocated memory before returning
                        for (int j = 0; j < num_dates; j++) {
                            free(dates[j].license_plate);
                        }
                        free(dates);
                        return;
                    }
                    num_dates++;
                }
                record_current = record_current->next;
            }
            current = current->next;
        }
    }

    // Sort dates array based on date and time values
    bubble_sort_dates(dates, num_dates);

    // Print the License Plates, Dates, and the total cost
    for (int i = 0; i < num_dates; i++) {
        printf("%s ", dates[i].license_plate);
        // Print date and time
        printf("%02d:%02d ", dates[i].hour, dates[i].minute);
        printf("%.2f\n", dates[i].cost);
    }

    // Free allocated memory
    for (int i = 0; i < num_dates; i++) {
        free(dates[i].license_plate);
    }
    free(dates);
}
