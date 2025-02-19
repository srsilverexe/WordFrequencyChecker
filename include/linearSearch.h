#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H

#include <stddef.h>

#include "item.h"

Item *linearSearch(Item *itemArray, size_t arraySize, const char *keyToFind);

#endif  // LINEAR_SEARCH_H
