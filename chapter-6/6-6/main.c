#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "preprocessor.h"
#define getobject (objstate=getobj(obj,&objlen))

int main(){
    int ignstate, c, curlen, linenum, objstate, objlen, err = VALID;
    char obj[MAXWORD], def[MAXWORD], line[MAXLINE], program[NUMLINE][MAXLINE];
    struct nlist *defp;
    for(linenum = 0, ignstate = NONE; (c = getch()) != EOF && err == FALSE && linenum < MAXLINE; linenum++){
        curlen = 0;
        if(c == '#' && ignstate==NONE){  //check for and handle definitions
            if(getobject == WORD){      //handle error in case of invalid definition
                if(strcmp(obj,"define") == 0){
                    if(getobject == BLANK){
                        if(getobject == WORD){
                            strcpy(def, obj);
                            if(getobject == BLANK){
                                if(getobject == WORD || objstate == WORDNUM)
                                    install(def, obj, objlen);
                                else
                                    err = INVDEF;
                            }else
                                pushobj(obj, objlen, objstate);
                        }
                        else
                            err = INVDEF;
                    }else
                        pushobj(obj, objlen, objstate);
                }
            }else
                pushobj(obj, objlen, objstate);
        }else{
            ungetch(c);
        }
        while(getobject != NEWL && err == VALID){
            if(ignstate == NONE && objstate == WORD){
                if((defp=lookup(obj)) != NULL){
                    strcpy(obj,defp->defn);
                    objlen = defp->deflen;
                }
            }else if(ignstate != SINCOM && ignstate == objstate) //single comment ignore state is only
                ignstate = NONE;                                //only set off after newline
            if((curlen+=objlen) > MAXLINE)
                err = EXCEED;
            else{
                strcat(line,obj);
            }
        }
        line[curlen++] = '\n';
        line[curlen] = '\0';
        if(ignstate == SINCOM)
                ignstate = NONE;
        strcpy(program[linenum],line);
    }
    return 0;
}

int createdef(char *obj, int objstate, int objlen)){
    stringhold[MAXLINE];
    if(getobject == WORD && strcmp(obj,"define")==0){


    }else{

    }
    return FALSE;
}

struct{
    char wrd[MAXWORD];
    char len;
    char state;
}objstack;


int getobj(char s[], int *len){
    if(objstack.state != NONE){
        *len = objstack.len;
        objstack.state = NONE;
        return objstack.state;
    }
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



void pushobj(char *s, int len, int state){
    strcpy(objstack.wrd, s);
    objstack.len = len;
    objstack.state = state;
}
