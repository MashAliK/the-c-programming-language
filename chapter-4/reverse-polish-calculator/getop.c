#include <stdio.h>
#include <stdlib.h>
#include "rpc.h"


int getop(char s[]){
    int i, c, num = 0, v = 0;
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    if(c==EOF)
        return EOF;
    s[1] = '\0';
    i = 0;
    if(c == '-'){
        if(isdigit(c = getch()) || c == '.'){
            s[++i] = c;
            num = 1;
        }else if(islower(c))
            v = 1;
        else
            ungetch(c);
    }
    if(!isdigit(s[0]) && s[0] != '.' && num == 0 || v){
        if(islower(c)){
            if(!v)
                push(variable[c-'a']);
            else
                push(-1*variable[c-'a']);
            return SKIP;
        }
        return s[0] ;
    }
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()))
            ;

    if(c == '.')
        while(isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}



double stof(char s[]){
    int i, sign, dec;
    double n, p, num;
    i = 0;
    if(s[0] == '-'){
        sign = -1;
        ++i;
    }
    else
        sign = 1;
    for(n = 0, p = 1.0, dec = 0; isdigit(s[i]) || s[i] == '.'; i++){
        if(s[i] == '.'){
            dec = 1;
            continue;
        }
        if(dec)
            p *= 10;
        n = n*10 + (s[i] - '0');
    }
    num = sign * n/p;
    return sign * n/p;
}


