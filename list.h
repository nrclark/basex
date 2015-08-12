/*
 * list.h
 *
 *  Created on: Aug 11, 2015
 *      Author: nrclark
 */

#ifndef LIST_H_
#define LIST_H_

typedef struct ListEntry {
    void *data;
    struct ListEntry *next;
    struct ListEntry *prev;
} ListEntry;

ListEntry* list_create();
ListEntry * list_rewind(ListEntry *target);
ListEntry * list_delete(ListEntry *target);
ListEntry * list_add_before(ListEntry *target, void *data);
ListEntry * list_add_after(ListEntry *target, void *data);
void list_destroy(ListEntry *target);

#endif /* LIST_H_ */
