#include <stdlib.h>
#include "list.h"

ListEntry* list_create() {
    return calloc(1, sizeof(ListEntry));
}

ListEntry * list_rewind(ListEntry *target) {
    while (target->prev != NULL)
        target = target->prev;

    return target;
}

ListEntry * list_delete(ListEntry *target) {
    ListEntry * result;
    
    if(target == NULL)
        return NULL;

    result = target->next;

    if(target->prev != NULL) {
        target->prev->next = (ListEntry *)target->next;
    }

    if(target->data != NULL) {
        free(target->data);
        target->data = NULL;
    }

    free(target);
    return result;
}

ListEntry * list_add_after(ListEntry *target, void *data) {
    if(target == NULL)
        return NULL;

    ListEntry *new_record = calloc(1, sizeof(ListEntry));

    if(new_record == NULL)
        return NULL;

    new_record->data = data;
    new_record->prev = target;
    new_record->next = target->next;
    if(target->next != NULL)
        target->next->prev = new_record;

    target->next = new_record;
    return new_record;
}

ListEntry * list_add_before(ListEntry *target, void *data) {
    if(target == NULL)
        return NULL;

    ListEntry *new_record = calloc(1, sizeof(ListEntry));

    if(new_record == NULL)
        return NULL;

    new_record->data = data;
    new_record->next = target;
    new_record->prev = target->prev;
    if(target->prev != NULL)
        target->prev->next = new_record;

    target->prev = new_record;
    return new_record;
}

void list_destroy(ListEntry *target) {
    if(target == NULL)
        return;

    target = list_rewind(target);

    while(target != NULL) {
        target = list_delete(target);
    }
}
