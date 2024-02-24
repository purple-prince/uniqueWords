#include "ll.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

LL * list_create()
{
	LL *l = (LL *)malloc(sizeof(LL));
	if (l == NULL) {
		return NULL;
	}
	l->head = NULL;
	return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *)malloc(sizeof(Node));

    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;

    if (l->head == NULL) {
        l->head = l->tail = n; // mark: makesthe head and tail the same node bc list empty
    } else {
        l->tail->next = n;
        l->tail = n;
    }
    return true;
}


item * list_find(LL *l, bool (*cmp)(item *,item *), item *i)
{
	Node *n = l->head;
	

	while (n != NULL) { //  being called
		if (cmp(&n->data, i)) {
			return &n->data; //  being called
		}
		n = n->next;
	}

	return NULL;
}


void list_remove(LL *list, bool (*cmp)(item *, item *), item *target) {
    if (list == NULL || list->head == NULL) return;

    Node *current = list->head;
    //Node *prev = NULL;

    while (current != NULL) {
        if (cmp(&(current->data), target)) {
            //if (prev == NULL) {
                list->head = current->next;
            //} else {
                //prev->next = current->next;
            //}
            free(current);
            return;
        }
        //prev = current;
        current = current->next;
    }
}

void list_destroy(LL **listPtr) {
    if (listPtr == NULL || *listPtr == NULL) return;

    Node *current = (*listPtr)->head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(*listPtr);
    *listPtr = NULL;
}