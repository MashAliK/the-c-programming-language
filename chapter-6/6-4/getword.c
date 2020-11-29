#include <stdio.h>
#include <ctype.h>
#include "wordfreq.h"

int getword(char *w, int max){
    int c;
    while(!isalpha(c = getch()) && c != EOF)
        ;
    *w++ = c;
    if(c == EOF){
        *w = '\0';
        return c;
    }
    while(isalpha(c=getch()))
        *w++ = c;
    ungetch(c);
    *w = '\0';
    return c;
}
