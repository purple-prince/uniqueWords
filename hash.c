#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ll.h"
#include "item.h"
#include "badhash.h"
#include "item.h"


// bool cmp(item *i1, item *i2) {
//     return strcmp(i1->key, i2->key) == 0;
// }

Hashtable * hash_create(void) {
    Hashtable * table = (Hashtable *)malloc(sizeof(Hashtable));

    for(int i = 0; i < numLLs; i++) {
        table->linked_lists[i] = list_create();
    }
    
    return table;
}


bool hash_put(Hashtable *table, char *key, int val) {
    unsigned long index = hash(key) % numLLs;

    item searchItem;
    strcpy(searchItem.key, key);
    item *foundItem = list_find(table->linked_lists[index], cmp, &searchItem);

    if (foundItem != NULL) {
        // If found, update the value
        foundItem->id = val;
        return true;
    } else {
        // If not found, create a new item and add it to the list
        item *newItem = malloc(sizeof(item));
        strcpy(newItem->key, key);
        newItem->id = val;
        return list_add(table->linked_lists[index], newItem);
    }
}

int * hash_get(Hashtable *table, char *key) {
    unsigned long index = hash(key) % numLLs;

    item searchItem;
    strcpy(searchItem.key, key);
    item *foundItem = list_find(table->linked_lists[index], cmp, &searchItem);

    if (foundItem != NULL) {
        return &foundItem->id;
    } else {
        return NULL;
    }
}



void hash_destroy(Hashtable **table) {
    if (table == NULL || *table == NULL) return;

    for (int i = 0; i < numLLs; i++) {
        if ((*table)->linked_lists[i] != NULL) {
            list_destroy(&((*table)->linked_lists[i]));
        }
    }

    free(*table);
    *table = NULL;
}
