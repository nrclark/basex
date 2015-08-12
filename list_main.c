#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void print_list(ListEntry *target) {
    target = list_rewind(target);

    while(target != NULL) {
        printf("data: %02d, prev: %08X, curr: %08X, next: %08X\n",
            target->data, target->prev, target, target->next);
        target = target->next;
    }
}

int main(void) {
    int x;
    int *buf;
    ListEntry * myList;
    myList = list_create();
    
    for(x = 0; x < 4; x++) {
        buf = malloc(sizeof(int));
        *buf = x;
        myList = list_add_after(myList, buf);
    }
   
    print_list(myList);
    list_destroy(myList);
    return 0;
}
