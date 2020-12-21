#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define getc (c=getch())
#define MAXLINE 10
#define MAXINP 1000
enum{NONGRPH, INT, FLT, STR};

int getinp(char*);
void printout(int*,int*,int*);
int getch(void);
void ungetch(int);

/*Non-graphic inputs (including blanks) are displayed as a hex value
Long lines are broken appropriately
If the string is unable to fit in a single line it will be  split up into multiple
    lines with hyphen insertions*/
int main(){
    char input[MAXINP], toprint[MAXINP], *ptp;
    int printyp, inplen, curlen, lenleft, newl;
    for(curlen = 0, newl = 0;(printyp=getinp(input)) != EOF;){
        switch(printyp){
        case NONGRPH:
            if(input[0] == '\n')
                newl = 1;
            sprintf(toprint,"0x%.2x",input[0]); //space added around hex value for visibility
            inplen = 1;
            break;
        case INT:
            sprintf(toprint,"%u",atol(input));
            break;
        case FLT:
            sprintf(toprint,"%g",atof(input));
            break;
        case STR:
            sprintf(toprint,"%s",input);
            break;
        }
        inplen = strlen(toprint);
        if((lenleft=(MAXLINE-curlen))<inplen){
            if(inplen > MAXLINE){ //
                ptp = input;
                lenleft = MAXLINE;
                do{
                    printf("%.*s",lenleft-1, ptp);
                    putchar('-');
                    putchar('\n');
                    ptp += lenleft-1;
                }while(MAXLINE < inplen-(ptp-input));
                printf("%s", ptp);
                lenleft = inplen-(ptp-input);
            }else{
                putchar('\n');
                curlen = 0;
                printf(toprint);
                printout(&newl,&curlen,&inplen);

            }
        }else{
            printf(toprint);
            printout(&newl,&curlen,&inplen);
        }
    }
    return 0;
}

int getinp(char *s){
    int c, numstat;
    *s++ = getc;
    *s = '\0';
    int len = 1;
    if(c == EOF){
        return EOF;
    }else if(!isgraph(c)){
        return NONGRPH;
    }if(isdigit(c))
        numstat = INT;
    else if(c == '.')
        numstat = FLT;
    else
        numstat = STR;
    while(getc != EOF && isgraph(c) && len < MAXINP-1){
        if(numstat == FLT && (c == '.' || !isdigit(c))){
            numstat = STR;
        }else if(numstat == INT){
            if(c == '.'){
                numstat = FLT;
            }else if(!isdigit(c)){
                numstat = STR;
            }
        }
        *s++ = c;
        len++;
    }
    if(c == EOF){
        return EOF;
    }else{
        ungetch(c);
    }
    *s = '\0';
    return numstat;
}

void printout(int *nl, int *clen, int *ilen){
    if(*nl != 1){
        putchar(' ');
        *clen += *ilen+1; //'+1' for blank space
    }else{
        putchar('\n');
        *nl = 0;
        *clen = 0;
    }
}
