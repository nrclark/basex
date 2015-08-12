#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void print_stack(Stack *target) {
    Node *temp = *target;

    while(temp != NULL) {
        printf("data: %02d, curr: %08X, next: %08X\n",
        (int)(temp->data), temp, temp->next);
        temp = temp->next;
    }
}

int main(void) {
    int x;
    Stack myStack = NULL;

    for(x = 0; x < 4; x++) {
        StackPush(&myStack, x);
    }
   
    print_stack(&myStack);
    while(myStack != NULL) {
        printf("data: %d\n", StackPop(&myStack));
    }
    return 0;
}
