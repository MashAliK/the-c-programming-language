#include <stdio.h>
#include <stdlib.h>
#include "rpc.h"



void push(double f){
    if(sp < MAXVAL)
        stack[sp++] = f;
    else
        printf("stack error: overload on stack\n");
}

double pop(void){
    if(sp>0)
        return stack[--sp];
    else
        printf("no values in stack\n");
        return 0.0;
}


