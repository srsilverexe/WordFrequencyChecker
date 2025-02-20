#include "../include/item.h"
#include <string.h>

// Function to compare two items based on their 'key' values.
// It ensures NULL keys are handled correctly.
int compareItemsByKey(const void *a, const void *b) {
    const Item *itemA = (const Item *)a;
    const Item *itemB = (const Item *)b;

    // If both keys are NULL, they are considered equal
    if (itemA->key == NULL && itemB->key == NULL)
        return 0;
    // If only itemA's key is NULL, it is considered greater
    if (itemA->key == NULL)
        return 1;
    // If only itemB's key is NULL, it is considered greater
    if (itemB->key == NULL)
        return -1;

    // Compare the keys using strcmp (lexicographical order)
    return strcmp(itemA->key, itemB->key);
}

// Function to compare two items based on their 'value'.
int compareItemsByValue(const void *a, const void *b) {
    const Item *itemA = (const Item *)a;
    const Item *itemB = (const Item *)b;

    if (itemA->value > itemB->value) return -1;
    if (itemA->value < itemB->value) return  1; 

    return 0;
}
