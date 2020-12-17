#include <stdio.h>
#include <string.h>
#define MAXWORD 25
#define MAXLINE 1000
#define NUMLINE 100
enum {FALSE, TRUE};
enum {NONE, QUOTE, SINQUOTE, COM, SINCOM, NEWL, WORD, OTH};

struct nlist *install(char*, char );
struct nlist *lookup(char*);
int getch(void);
void ungetch(int);
int addobj(char *s, char *t, int len);

int main(){
    int ignstate, c, curlen, linenum;
    char obj[MAXWORD];
    struct nlist *def;
    for(linenum = 0; (c = getch) != EOF && err == FALSE && linenum < MAXLINE; linenum++){
        curlen = 0;
        if(c == '#' && ignstate==NONE){  //check for and handle definitions
                        //handle error in case of invalid definition
        }else
            ungetch(c);
        while((objstate=getobj(obj,&objlen)) != NEWL){
            if(ignstate == NONE && objstate == WORD){
                if((def=lookup(obj)) != NULL){
                    strcpy(obj,def->defn);
                    objlen = def->deflen;
                }
            }else if(ignstate != SINCOM && ignstate == objstate) //single comment ignore state is only
                ignstate = NONE;                                //only set off after newline
            if((curlen+=objlen) > MAXLINE)
                err = EXCEED;
            else{
                strcat(line,obj);
            }
        }
        if(ignstate == SINCOM)
                ignstate = NONE;
        strcpy(program[linenum],line);
    }
    return 0;
}
