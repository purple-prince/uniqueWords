#include "item.h"
#include <string.h>
#include <stdio.h>

bool cmp(item *i1, item *i2) {
    return strcmp(i1->key, i2->key) == 0;
}