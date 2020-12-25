#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void){
    int c;
    if(bufp > 0)
        return buf[--bufp];
    else{
        while(isspace(c = getchar()))
            ;
        return c;
    }
}
void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

