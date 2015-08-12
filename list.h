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

ListEntry* ListCreate();
ListEntry * ListRewind(ListEntry *target);
ListEntry * ListDelete(ListEntry *target);
ListEntry * ListAddBefore(ListEntry *target, void *data);
ListEntry * ListAddAfter(ListEntry *target, void *data);
void ListDestroy(ListEntry *target);

#endif /* LIST_H_ */
