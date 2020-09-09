#include <stdio.h>
#include <stdlib.h>
#include "rcp.h"

/*Modified version of the reverse polish calculator as prompted 
by the exercises in the book (mainly chapter 4). Added functionality 
includes modulo operator(%), negative numbers, sin, exp pow and variables 
can be assigned to a letter the user using the construction: 
(letter) (value) (equals sign) */

int main(void){
    set(); //initialize variables to prevent run-time errors
    char s[MAXOP];
    int err = NO;
    int type, letter;
    double op2, skip = 0, print, hold;
    while((type = getop(s)) != EOF){
        switch (type){
        case NUMBER:
            push(stof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op2 = pop();
            if(op2 == 0.0){
                printf("error: zero division\n");
                err = YES;
            }
            else
                push(pop() / op2);
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '%':
            op2 = (int) pop();
            if(op2 == 0.0){
                printf("error: zero modulus\n");
                err = YES;
            }
            else
                push((int) pop() % (int) op2);
            break;
        case '\n':
            if(err == NO){
                print = pop();
                printf("%.8f\n",print);
                if(skip){
                    push(print);
                    skip = 0;
                }
            }else{
                err = NO;
            }
            break;
        case '!':
            skip = 1;
            break;
        case '@':
            stack[sp] = stack[sp-1];
            sp++;
            break;
        case '#':
            hold = stack[sp-1];
            stack[sp-1] = stack[sp-2];
            stack[sp-2] = hold;
            break;
        case '$':
            sp = 0;
            break;
        case '<':
            push(sin(pop()));
            break;
        case '>':
            push(exp(pop()));
            break;
        case '?':
            op2 = pop();
            push(pow(pop(),op2));
            break;
        case '=':
            variable[letter-'a'] = pop();
            break;
        case SKIP:
            letter = (int) s[0];
            break;
        case 26:
            printf("\n%.8f\n",pop());
            return 0;
        default:
            printf("error: undefined input %c\n", type);
            break;
        }
    }
    return 0;
}

void set(void){
    int x;
    for(x = 0; x != 26; x++)
        variable[x] = 0.0;
}
