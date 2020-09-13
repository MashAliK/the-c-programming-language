#include <stdio.h>

#define LIMIT 30
#define LINELMT 10
#define OUT 0
#define IN 1

int readLine(char []);
void stringAdd(char[], char[], int);

/* program which deletes trailing blanks/tabs and
skips blank lines*/

main(){
    int status;
    char line[LIMIT], total[LIMIT*LINELMT];
    total[0] = '\0';
    while((status = readLine(line)) > 0){
        if(status > 1){
            stringAdd(total,line,status);
        }
    }
    if(status != -1)
        printf("%s\n",total);
    return 0;
}

void stringAdd(char s[], char t[], int n){
    int i, j;
    for(i = 0; s[i] != '\0';i++)
        ;
    for(j = 0; n-- != 0; j++)
        s[i++] = t[j];
    s[i] = '\0';
}
int readLine(char line[]){
    int c, i, state = IN;
    for(i = 0; i < LIMIT-1 && (c = getchar()) != EOF && c != '\n'; ++i){
            if(state == IN){
                if(c == ' ' || c == '\t'){
                    line[i] = c;
                    state = OUT;
                }
                else
                    line[i] = c;
            }else{
                if(c == ' ' || c == '\t')
                    i--;   //negates the counter of the for loop
                else{
                    line[i] = c;
                    state = IN;
                }
            }
    }
    if(c == EOF)
        return 0;
    else if(c == '\n')
        if(i == 0)
            return 1;
        else{
            line[i++] = '\n';
            line[i] = '\0';
            return i;
        }
    else
        printf("Error: Memory overload\n");
    return -1;
}





