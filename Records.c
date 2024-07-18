/**
 * File containing the implementation of the functions related to the Record Structure.
 * @file Records.c
 * @author ist1102716
*/
#include "Records.h"
#include "Parks.h"
#include "Park.h"
#include "Invariants.h"
#include <string.h>
#include <stdlib.h>

unsigned int hash(const char *key, int size) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % size;
}

// Create a new hash map
HashMap *create_hash_map() {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (map == NULL) {
        return NULL; // Memory allocation failed
    }
    map->size = MAX_SIZE;
    map->buckets = (HashNode **)malloc(MAX_SIZE * sizeof(HashNode *));
    if (map->buckets == NULL) {
        free(map);
        return NULL; // Memory allocation failed
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        map->buckets[i] = NULL;
    }
    return map;
}


// Function to add a record to the hash table
void add_record(HashMap *map, const char *key, ParkRecord* record) {
    int index = hash(key, map->size);
    HashNode *current = map->buckets[index];

    // Check if the vehicle already has records in this bucket
    while (current != NULL) {
        if (strcmp(current->vehicle_license_plate, key) == 0) {
            // Traverse to the end of the linked list
            RecordNode *last_record_node = current->records;
            while (last_record_node->next != NULL) {
                last_record_node = last_record_node->next;
            }

            // Add the new record at the end of the linked list
            RecordNode *new_record_node = (RecordNode *)malloc(sizeof(RecordNode));
            if (new_record_node == NULL) {
                return; // Memory allocation failed
            }
            new_record_node->record = *record; // Copy the ParkRecord data
            new_record_node->next = NULL;
            last_record_node->next = new_record_node;
            return;
        }
        current = current->next;
    }

    // If the vehicle does not have records in this bucket, create a new HashNode
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    if (new_node == NULL) {
        return; // Memory allocation failed
    }
    strcpy(new_node->vehicle_license_plate, key);
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;

    // Add the new record to the linked list of records for this vehicle
    RecordNode *new_record_node = (RecordNode *)malloc(sizeof(RecordNode));
    if (new_record_node == NULL) {
        return; // Memory allocation failed
    }
    new_record_node->record = *record; // Copy the ParkRecord data
    new_record_node->next = NULL;
    new_node->records = new_record_node;
}



// Function to retrieve records based on the vehicle license plate
RecordNode *get_records(HashMap *map, const char *key) {
    int index = hash(key, map->size);
    HashNode *current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->vehicle_license_plate, key) == 0) {
            return current->records; // Return pointer to the linked list of records
        }
        current = current->next;
    }
    return NULL; // Vehicle not found
}


ParkRecord* createParkRecord(const char* license_plate, Date* in_date) {
    // Allocate memory for a ParkRecord structure
    ParkRecord* record = (ParkRecord*)malloc(sizeof(ParkRecord));
    if (record == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Copy the license plate to the ParkRecord structure
    // Allocate memory for in_date
    strcpy(record->license_plate, license_plate);

    record->in_date = in_date;

    // Copy the entrance date to the ParkRecord structure
    // record->in_date = (Date*)malloc(sizeof(Date));
    // if (record->in_date == NULL) {
    //     free(record);
    //     return NULL;
    // }
    // memcpy(&(record->in_date), in_date, sizeof(Date));

    // Set other fields to default or meaningful values
    record->out_date = NULL;

    record->cost = -1.0;

    return record;
}







