/**
 * File containing the implementation of the main functions related to the parking system, i.e.,
 * those that process the input commands.
 * @file Engine.c
 * @author ist1102716
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Engine.h"
#include "Park.h"
#include "Records.h"

void print_all_parks(Parks *parks) {
    int count;
    Park** ordered_parks = get_parks_ordered_by_id(parks, &count);
    if (ordered_parks != NULL) {
        print_park_names_ordered_by_id(ordered_parks, count);
        free_ordered_parks(ordered_parks); // Free memory
    } else {
        printf("Memory allocation failed.\n");
    }
}

void add_park_command(Parks *parks, char *args[], int argc) {
    if (argc > 1) {
        // Check if the park already exists
        if (ParkAlreadyExists(parks, args[1])) {
            printf("%s: parking already exists.\n", args[1]);
            return;
        }

        // Validate capacity
        int capacity = atoi(args[2]);
        if (!isCapacityValid(capacity)) {
            printf("%s: invalid capacity.\n", args[2]);
            return;
        }

        // Validate cost
        float price_15 = atof(args[3]);
        float price_15_1h = atof(args[4]);
        float price_1h = atof(args[5]);
        if (!isCostValid(price_15, price_15_1h, price_1h)) {
            printf("invalid cost.\n");
            return;
        }

        // Check if maximum number of parks is reached
        if (isParksMaxed(parks)) {
            printf("too many parks.\n");
            return;
        }

        // Create and add the park
        int id = parks->parks_id;
        Park *park = create_park(args[1], capacity, price_15, price_15_1h,
                                price_1h, id);
        if (park == NULL) {
            printf("Failed to create park.\n");
            return;
        }
        parks->parks_id++;
        add_park(parks, park);
    } else {
        print_all_parks(parks);
    }
}

void enter_parking(Parks *parks, char *args[]) {
    // First check if the park exists
    if(ParkAlreadyExists(parks, args[1]) == 0){
        printf("%s: no such parking.\n", args[1]);
        return;
    } 
    if(isValidLicensePlate(args[2]) == 0){
        printf("%s: invalid licence plate.\n", args[2]);
        return;
    }
    Park *park = get_park(parks, args[1]);
    if(isParkFull(park) == 1){
        printf("%s: parking is full.\n", args[1]);
        return;
    }
    if(isValidDate(args[3]) == 0 || isValidTime(args[4]) == 0){
        printf("invalid date.\n");
        return;
    }
    // Get the record for the license plate
    int isInside = 0;
    for(int i = 0; i < parks->capacity; i++){
        if(parks->parks[i] != NULL){
            RecordNode *recordNode = get_records(parks->parks[i]->records_map, 
                                                    args[2]);
            while (recordNode != NULL) {
                if(recordNode->record.cost == -1.0){
                    printf("%s: invalid vehicle entry.\n", args[2]);
                    isInside = 1;
                    break;
                }
                recordNode = recordNode->next;
            }
        }
    }
    if(isInside == 1){
        return;
    }

    int day, month, year;
    sscanf(args[3], "%d-%d-%d", &day, &month, &year);
    int hour, minute;
    sscanf(args[4], "%d:%d", &hour, &minute);
    Date *recordDate = createDate(day, month, year, hour, minute);
    Date *parkDate = createDate(day, month, year, hour, minute);

    if(park->lastDate == NULL){
        park->lastDate = parkDate;
    }else{
        if(isAfter(*parkDate, *park->lastDate) == 0){
            printf("invalid date.\n");
            return;
        }
        // Delete the last date and create a new one
        destroyDate(park->lastDate);
        park->lastDate = parkDate;
    }

    // Create a new record
    ParkRecord *record = createParkRecord(args[2], recordDate);

    // Add the record to the park
    add_record(park->records_map, args[2], record);

    // Update the available spots in the park
    park->available_spots--;

    // Print Name of the park and available spots
    printf("%s %d\n", park->name, park->available_spots);

    // Free the date
    free(record);
}

void exit_parking(Parks *parks, char *args[]) {
    // First check if the park exists
    if(ParkAlreadyExists(parks, args[1]) == 0){
        printf("%s: no such parking.\n", args[1]);
        return;
    } 
    if(isValidLicensePlate(args[2]) == 0){
        printf("%s: invalid licence plate.\n", args[2]);
        return;
    }
    Park *park = get_park(parks, args[1]);
    if(isValidDate(args[3]) == 0 || isValidTime(args[4]) == 0){
        printf("invalid date.\n");
        return;
    }
    // Get the record for the license plate
    int isInside = 0;

    RecordNode *recordNode = get_records(park->records_map, args[2]);
    while (recordNode != NULL) {
        if(recordNode->record.cost == -1.0){
            isInside = 1;
            break;
        }
        recordNode = recordNode->next;
    }

    if(isInside == 0){
        printf("%s: invalid vehicle exit.\n", args[2]);
        return;
    }

    int day, month, year;
    sscanf(args[3], "%d-%d-%d", &day, &month, &year);
    int hour, minute;
    sscanf(args[4], "%d:%d", &hour, &minute);
    Date *recordDate = createDate(day, month, year, hour, minute);
    Date *parkDate = createDate(day, month, year, hour, minute);

    if(park->lastDate == NULL){
        park->lastDate = parkDate;
    }else{
        if(isAfter(*parkDate, *park->lastDate) == 0){
            printf("invalid date.\n");
            return;
        }
        // Delete the last date and create a new one
        destroyDate(park->lastDate);
        park->lastDate = parkDate;
    }

    park->available_spots++;

    // Update the record with the exit date
    recordNode->record.out_date = recordDate;

    // Calculate the cost
    recordNode->record.cost = calculate_cost(park, recordNode->record.in_date,
    recordNode->record.out_date);

    // Print values
    printf("%s ", recordNode->record.license_plate);
    printDate(*recordNode->record.in_date);
    printf(" ");
    printTime(*recordNode->record.in_date);
    printf(" ");
    printDate(*recordNode->record.out_date);
    printf(" ");
    printTime(*recordNode->record.out_date);
    printf(" %.2f\n", recordNode->record.cost);
}

void print_vehicle_history(Parks *parks, char *args[]) {
// First check if the plate is valid
    if(isValidLicensePlate(args[1]) == 0){
        printf("%s: invalid licence plate.\n", args[1]);
        return;
    }
    // Check if the plate is in the records
    int isInside = 0;
    for(int i = 0; i < parks->capacity; i++){
        if(parks->parks[i] != NULL){
            RecordNode *recordNode = get_records(parks->parks[i]->records_map,
                                                    args[1]);
            while (recordNode != NULL) {
                isInside = 1;
                recordNode = recordNode->next;
            }
        }
    }
    if(isInside == 0){
        printf("%s: no entries found in any parking.\n", args[1]);
        return;
    }

    // Iterate through the parks
    // Get the list of park names ordered alphabetically
    int count;
    char** park_names = get_park_names_ordered(parks, &count);
    if (park_names != NULL) {
        // Iterate through the sorted list of park names
        for (int i = 0; i < count; i++) {
            char* park_name = park_names[i];
            // Find the park corresponding to the current name
            Park* park = get_park(parks, park_name);
            if (park != NULL) {
                // Print records for the current park
                RecordNode* recordNode = get_records(park->records_map,
                                                        args[1]);
                while (recordNode != NULL) {
                    printf("%s ", park->name);
                    printDate(*recordNode->record.in_date);
                    printf(" ");
                    printTime(*recordNode->record.in_date);
                    if (recordNode->record.cost != -1.0) {
                        printf(" ");
                        printDate(*recordNode->record.out_date);
                        printf(" ");
                        printTime(*recordNode->record.out_date);
                    }
                    printf("\n");
                    recordNode = recordNode->next;
                }
            }
        }
        free_park_names(park_names, count); // Don't forget to free the memory
    } else {
        printf("Memory allocation failed.\n");
    }
}

void remove_park_command(Parks *parks, char *args[]) {
    // First check if the park exists
    if(ParkAlreadyExists(parks, args[1]) == 0){
        printf("%s: no such parking.\n", args[1]);
        return;
    }

    // Get the park and destroy the records and the park
    remove_park(parks, args[1]);

                    int count;
    char** park_names = get_park_names_ordered(parks, &count);
    if (park_names != NULL) {
        // Iterate through the sorted list of park names
        for (int i = 0; i < count; i++) {
            char* park_name = park_names[i];
            // Find the park corresponding to the current name
            Park* park = get_park(parks, park_name);
            if (park != NULL) {
                printf("%s\n", park->name);
                }
            }
        }
        free_park_names(park_names, count); // Don't forget to free the memory
}

void calculate_cost_command(Parks *parks, char *args[], int argc) {
    if (argc > 2) {
        // First check if the park exists
        if(ParkAlreadyExists(parks, args[1]) == 0){
            printf("%s: no such parking.\n", args[1]);
            return;
        } 
        Park *park = get_park(parks, args[1]);
        if(isValidDate(args[2]) == 0){
            printf("invalid date.\n");
            return;
        }
        int day, month, year;
        sscanf(args[2], "%d-%d-%d", &day, &month, &year);
        int hour, minute;
        sscanf(args[4], "%d:%d", &hour, &minute);
        // Allocate memory for a Date structure
        Date *recordDate = createDate(day, month, year, hour, minute);


        get_cost_records_for_date(park, recordDate);
        // Free the date
        destroyDate(recordDate);
    } else {
        // First check if the park exists
        if(ParkAlreadyExists(parks, args[1]) == 0){
            printf("%s: no such parking.\n", args[1]);
            return;
        }
        Park *park = get_park(parks, args[1]);

        get_cost_records_per_park(park);
    }
}
