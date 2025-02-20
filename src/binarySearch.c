#include "../include/binarySearch.h"

#include <string.h>

// Function to perform a binary search on an array of Item structures.
// The array is assumed to be sorted by 'key' values in ascending order.
Item *binarySearch(Item *itemArray, size_t arraySize, const char *keyToFind) {
    size_t low = 0, high = arraySize;  // Define the search range (half-open interval [low, high))

    while (low < high) {                // Continue searching as long as the range is valid
        size_t mid = (low + high) / 2;  // Calculate the middle index

        // If the key at mid is NULL, it means we should ignore this part
        // and move the high bound down to exclude it.
        if (itemArray[mid].key == NULL) {
            high = mid;
            continue;
        }

        int cmp = strcmp(itemArray[mid].key, keyToFind);  // Compare the key at mid with the target key

        if (cmp == 0)
            return &itemArray[mid];  // Key found, return a pointer to the item
        else if (cmp < 0)
            low = mid + 1;  // If key at mid is smaller, search the right half
        else
            high = mid;  // If key at mid is larger, search the left half
    }

    return NULL;  // If no match is found, return NULL
}
