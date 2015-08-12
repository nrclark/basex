/*
 * stack.h
 *
 *  Created on: Aug 11, 2015
 *      Author: nrclark
 */

#ifndef STACK_H_
#define STACK_H_

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef Node * Stack;

int StackInit(Stack *target);
int StackPush(Stack *target, void *data);
void *StackPop(Stack *target);

#endif /* STACK_H_ */
