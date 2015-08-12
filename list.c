#include <stdlib.h>
#include "list.h"

ListEntry* ListCreate(void *data) {
    ListEntry *result;
    result = calloc(1, sizeof(ListEntry));
    if(result != NULL) {
        result->data = data;
    }
    return result;
}

ListEntry * ListRewind(ListEntry *target) {
    if(target == NULL) {
        return NULL;
    }
    
    while (target->prev != NULL) {
        target = target->prev;
    }
    
    return target;
}

ListEntry * ListDelete(ListEntry *target) {
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

ListEntry * ListAddAfter(ListEntry *target, void *data) {
    ListEntry *new_record = calloc(1, sizeof(ListEntry));

    if(new_record == NULL)
        return NULL;

    new_record->data = data;
    
    if(target == NULL)
        return new_record;
    
    new_record->prev = target;
    new_record->next = target->next;
    if(target->next != NULL)
        target->next->prev = new_record;

    target->next = new_record;
    return new_record;
}

ListEntry * ListAddBefore(ListEntry *target, void *data) {
    ListEntry *new_record = calloc(1, sizeof(ListEntry));

    if(new_record == NULL)
        return NULL;
    
    new_record->data = data;
    
    if(target == NULL)
        return new_record;

    new_record->next = target;
    new_record->prev = target->prev;
    if(target->prev != NULL)
        target->prev->next = new_record;

    target->prev = new_record;
    return new_record;
}

void ListDestroy(ListEntry *target) {
    if(target == NULL)
        return;

    target = ListRewind(target);

    while(target != NULL) {
        target = ListDelete(target);
    }
}
