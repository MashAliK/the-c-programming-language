#include <stdio.h>
#include <ctype.h>

int ln;

int getword(char *w, int max){
    int c;
    while(!isalpha(c = getch()) && c != EOF)
        if(c == '\n')
            ln++;
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
