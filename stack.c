#include <stdlib.h>
#include "stack.h"

int StackPush(Stack *target, void *data) {
    Node *new_node = calloc(1, sizeof(Node));
  
    if(new_node == NULL)
        return EXIT_FAILURE;
    
    new_node->next = *target;
    new_node->data = data;
    *target = new_node;
    
    return EXIT_SUCCESS;
}

void * StackPop(Stack *target) {
    void * data = NULL;
    Node * next; 

    if(*target == NULL) { 
        return NULL;
    }
    
    next = (*target)->next;
    data = (*target)->data;
    
    free(*target);
    *target = next;
    return data;
}

int StackInit(Stack *target) {
    *target = calloc(1,sizeof(Node));

    if(*target == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
