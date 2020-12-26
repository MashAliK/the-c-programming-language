#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXOP 25
#define MAXSTACK 20
#define NUM '0'

void push(double);
double pop(void);
int getop(char *);

int main(){
    char op[MAXOP], type;
    double opand;
    while((type=getop(op)) != EOF){
        if(type == NUM){
            sscanf(op,"%lf",&opand);
            push(opand);
        }else{
            switch(type){
            case '\n':
                printf("%lf\n",pop());
            case '+':
                push(pop()+pop());
                break;
            case '-':
                opand = pop();
                push(pop()-opand);
                break;
            case '*':
                push(pop()*pop());
                break;
            case '/':
                opand = pop();
                if(opand == 0.0){
                    printf("Error: cannot divide by zero\n");
                }else
                    push(pop()/opand);
                break;
            default:
                printf("Error: %c operator not recognized\n",type);
            }
        }
    }
    return 0;
}

char ch;

char scanch(char *c){
    if(ch != '\0'){
        *c = ch;
        ch = '\0';
        return 1;
    }else
        return scanf("%c",c);
}

void unscanch(char c){
    ch = c;
}

int getop(char *s){
    char c;
    int rtrn;
    do{
        rtrn = scanch(&c);
    }while(c == ' ' || c == '\t');
    if(rtrn == EOF)
        return EOF;
    if(!isdigit(c) && c != '.'){
        *s++ = c;
        *s = '\0';
        return c;
    }
    if(isdigit(c)){
        *s++ = c;
        while(scanch(&c) && isdigit(c))
            *s++ = c;
        unscanch(c);
    }
    if(c=='.'){
        *s++ = c;
        while(scanch(&c) && isdigit(c))
            *s++ = c;
        unscanch(c);
    }
    *s = '\0';
    return NUM;
}

double stack[MAXSTACK];
int sp;

void push(double n){
    if(sp > 20)
        printf("Error: stack full");
    else
        stack[sp++] = n;
}

double pop(void){
    return (sp == 0) ? 0.0 : stack[--sp];
}
