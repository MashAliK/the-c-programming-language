#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 100

int stack[MAXSTACK];
int stackp;

void push(int n){
    if(stackp>MAXSTACK)
        printf("Error: stack is full");
    else
        stack[stackp++] = n;
}

int pop(void){
    return (stackp > 0) ? stack[--stackp] : 0;
}
