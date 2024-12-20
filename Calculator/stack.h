#include <stdbool.h>
#ifndef STACK_H
#define STACK_H
#define STACKSIZE 100 // arbitrary
typedef struct stackType *stack;
// Note that passing a NULL stack to any of these routines, or
// indexing into a stack using an illegal value, is undefined
stack createStack(); // creates a stack
void freeStack(stack); // deallocates a stack
void push(stack,int); // pushes item onto stack; fails
// if stack is full
void pop(stack); // pops item off stack; fails
// if stack is empty
int top(stack); // returns top of stack; fails
// if stack is empty
bool isEmpty(stack); // returns true if stack is empty
bool isFull(stack); // returns true if stack is full
int size(stack); // returns the size of the stack
#endif
