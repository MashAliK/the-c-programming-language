#include <stdio.h>
#include <stdlib.h>
#include "rcp.h"

int present;
double holder;

int getch(void){
    if(present){
        present = 0;
        return holder;
    }else
        return getchar();
}

void ungetch(int c){
    if(present)
        printf("ungetch error: overload in buffer\n");
    else{
        present = 1;
        holder = c;
    }
}
