#ifndef _HASH

#define _HASH 

#include "ll.h"

typedef struct Hashtable Hashtable;
#define numLLs 1000

struct Hashtable {
    LL * linked_lists[numLLs];
};

Hashtable * hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int * hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
