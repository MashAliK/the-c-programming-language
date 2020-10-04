#include <stdio.h>
#include <stdlib.h>

void push(int n);
int pop(void);


int main(int argc, char *argv[])
{
    char *op;
    int op2;
    while(--argc > 0){
        op = *++argv;
        switch(*op){
        case '+':
            push(pop()+pop());
            break;
        case 'x':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop()-op2);
            break;
        case '/':
            op2 = pop();
            if(op2 != 0){
                push(pop()/op2);
                break;
            }else{
                printf("Error: cannot divide by zero\n");
            }
        default:
            push(atoi(op));
            break;
        }
    }
    printf("%d",pop());
    return 0;
}
