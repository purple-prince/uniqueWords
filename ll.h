#ifndef _LL

#define _LL

#include <stdbool.h>
#include "item.h"

typedef struct Node Node;

struct Node {
    item data;
    struct Node *next;
    //struct Node *prev;
};

typedef struct LL LL;
struct LL {
	Node *head;
	Node *tail;
};

LL * list_create(void);
bool list_add(LL *, item *);
item * list_find(LL *, bool (*)(item *,item *), item *);

void list_destroy(LL **);
void list_remove(LL *, bool (*)(item *,item *), item *);

#endif


