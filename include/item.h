#ifndef ITEM_H
#define ITEM_H

#include <stddef.h>

typedef struct {
    char *key;
    int   value;
} Item;

int compareItemsByKey(const void *a, const void *b);
int compareItemsByValue(const void *a, const void *b);

#endif  // ITEM_H
