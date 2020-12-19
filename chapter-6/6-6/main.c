#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "preprocessor.h"
#define getobject (objstate=getobj(obj,&objlen))

int main(){
    int ignstate, c, curlen, linenum, objstate, objlen, err = VALID, defstate, i;
    char obj[MAXWORD], def[MAXWORD], line[MAXLINE], program[NUMLINE][MAXLINE];
    struct nlist *defp;
    for(linenum = 0, ignstate = NONE; err == VALID && (c = getch()) != EOF && linenum < MAXLINE; linenum++){
        line[0] = '\0';
        curlen = 0;
        if(c == '#')
            err = createdef(obj, line, &curlen);
        else
            ungetch(c);
        while(err == VALID && getobject != NEWL){
            if(ignstate == NONE){
                if(objstate == WORD){
                    if((defp=lookup(obj)) != NULL){
                        strcpy(obj,defp->defn);
                        objlen = defp->deflen;
                    }
                }else if(objstate >= QUOTE && objstate <= SINCOM)
                    ignstate = objstate;
            }else if(ignstate != SINCOM && ignstate == objstate) //single comment ignore state is only
                ignstate = NONE;                                //only set off after newline
            if((curlen+=objlen) > MAXLINE)
                err = EXCEEDL;
            else
                strcat(line,obj);
        }
        if(err != VALID){
            if(err == SKIP){
                err = VALID;
                linenum--;
            }else
                errhndl(err, linenum);
        }
        else{
            line[curlen] = '\0';
            if(ignstate == SINCOM)
                    ignstate = NONE;
            strcpy(program[linenum],line);
        }
    }
    if(err == VALID){
        for(i = 0; i < linenum; i++)
            printf("%s\n",program[i]);
    }
    return 0;
}

int createdef(char *obj, char *line, int* curl){
    char strhld[MAXLINE];
    struct nlist *newdef;
    int objstate, objlen;
    strhld[0] = '#';
    strhld[1] = '\0';
    getobject;
    strcpy(line,strcat(strhld,obj));
    *curl = 1+objlen; //'1+' for '#'
    if(!(objstate == WORD && strcmp(obj,"define")==0)){
        return VALID;
    }else{
        if(getobject != BLANK){
            strcat(line,obj);
            *curl += objlen;
            return VALID;
        }
    }
    if(getobject != WORD){
        return INVDEF;
    }else
        strcpy(strhld, obj);
    if(getobject == BLANK && (getobject == WORD || objstate == WORDNUM)){
        newdef = install(strhld, obj, objlen);
        if(getobject == NEWL)
            return SKIP;
    }
    return INVDEF;
}

int getobj(char s[], int *len){
    int c, nonum = TRUE, i;
    if(isalnum(c=getch())){
        i = 0;
        do{
            s[i++] = c;
            if(isdigit(c))
                nonum = FALSE;
        }while(isalnum(c=getch()));
        ungetch(c);
        s[i] = '\0';
        *len = i;
        if(nonum == TRUE)
            return WORD;
        else
            return WORDNUM;
    }else{
        s[0] = c;
        s[1] = '\0';
        *len = 1;
        switch(c){
        case '"':
            return QUOTE;
        case '\'':
            return SINQUOTE;
        case '/':
            if((c=getch())=='/' || c=='*'){
                s[1] = c;
                s[2] = '\0';
                *len = 2;
                return (c=='/') ? SINCOM : COM;
            }else{
                ungetch(c);
                return OTH;
            }
        case '\n':
            return NEWL;
        case ' ':
            return BLANK;
        case EOF:
            return EOF;
        default:
            return OTH;
        }
    }
}

void errhndl(int error, int ln){
    printf("Error on line %d: ",ln+1);
    switch(error){
    case(EXCEEDW):
        printf("Number of characters in word exceeds maximum allowed (%d characters)\n",MAXWORD);
        break;
    case(EXCEEDL):
        printf("Number of characters in line exceeds maximum allowed (%d characters)\n",MAXLINE);
        break;
    case(INVDEF):
        printf("Invalid use of '#define' preprocessor (Definition can only contain alphabets\n\
                 and text to replace can only contain alphabets and/or numbers)\n");
        break;
    }
}
