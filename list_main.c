#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void print_list(ListEntry *target) {
    target = ListRewind(target);

    while(target != NULL) {
        printf("data: %02d, prev: %08X, curr: %08X, next: %08X\n",
            *((int *)(target->data)), target->prev, target, target->next);
        target = target->next;
    }
}

int main(void) {
    int x;
    ListEntry * myList = NULL;
    int *buf;
    
    buf = malloc(sizeof(int));
    *buf = 51;

    myList = ListCreate(buf);
    for(x = 0; x < 4; x++) {
        buf = malloc(sizeof(int));
        *buf = x;
        myList = ListAddAfter(myList, buf);
    }
   
    print_list(myList);
    ListDestroy(myList);
    return 0;
}
