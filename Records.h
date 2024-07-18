#ifndef RECORDS_H
#define RECORDS_H

#include "Date.h"

#include <stdlib.h>
#include <string.h>

// Define the maximum size of the hash map
#define MAX_SIZE 500

// Structure to represent a park record
typedef struct {
    char license_plate[11]; // Vehicle license plate
    Date *in_date; // Date of entry
    Date *out_date; // Date of exit
    float cost; // Cost for parking
} ParkRecord;

// Structure to represent a node in the linked list of records
typedef struct RecordNode {
    ParkRecord record;
    struct RecordNode *next;
} RecordNode;

// Structure to represent a node in the hash table
typedef struct HashNode {
    char vehicle_license_plate[11]; // Key: Vehicle license plate
    RecordNode *records; // Linked list of records for this vehicle
    struct HashNode *next; // Pointer to the next node (for handling collisions)
} HashNode;

// Structure to represent the hash table
typedef struct {
    int size; // Size of the hash table
    HashNode **buckets; // Array of pointers to hash nodes (the hash table itself)
} HashMap;

// Function to calculate the hash value for a given key
unsigned int hash(const char *key, int size);

// Function to create a hash map
HashMap *create_hash_map();

// Function to add a record to the hash map
void add_record(HashMap *map, const char *key, ParkRecord* record);

// Function to get records for a given key from the hash map
RecordNode *get_records(HashMap *map, const char *key);

// Function to create a ParkRecord instance
ParkRecord* createParkRecord(const char* license_plate, Date* in_date);

#endif /* RECORDS_H */
