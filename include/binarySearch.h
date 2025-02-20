#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stddef.h>

#include "item.h"

int compareItems(const void *a, const void *b);

Item *binarySearch(Item *itemArray, size_t arraySize, const char *keyToFind);

#endif  // BINARY_SEARCH_H
