#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
struct stackType {
int data[STACKSIZE];
int top;
};
stack createStack() {
stack s = malloc(sizeof(struct stackType));
s->top = -1;
return s;
}
void freeStack(stack s){ free(s); }
void push(stack s,int p) {
if(isFull(s)) {
printf("Error: stack overflow\n");
exit(EXIT_FAILURE);
} else {
s->data[++s->top] = p;
}
}
void pop(stack s){
if(isEmpty(s)){
printf("Error: stack underflow\n");
exit(EXIT_FAILURE);
} else {
s->top--;
}
}
int top(stack s) {
if(isEmpty(s)){
printf("Error: stack underflow\n");
exit(EXIT_FAILURE);
} else {
return s->data[s->top];
}
}
bool isEmpty(stack s) { return s->top == -1; }
bool isFull(stack s) { return s->top == STACKSIZE-1; }
int size(stack s) { return s->top + 1; }
