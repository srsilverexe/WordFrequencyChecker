#include "../include/linearSearch.h"

#include <string.h>

// Function to perform a linear search on an array of Items
Item *linearSearch(Item *itemArray, size_t arraySize, const char *keyToFind) {
    // Check if the array or key is NULL to prevent errors
    if (itemArray == NULL || keyToFind == NULL)
        return NULL;

    // Iterate through the array to find the matching key
    for (size_t i = 0; i < arraySize; i++) {
        // Ensure the current item has a valid key before comparing
        if (itemArray[i].key != NULL) {
            // Compare the current key with the key to find
            if (strcmp(itemArray[i].key, keyToFind) == 0) {
                return &itemArray[i];  // Return the found item
            }
        }
    }

    return NULL;  // Return NULL if the key is not found
}
