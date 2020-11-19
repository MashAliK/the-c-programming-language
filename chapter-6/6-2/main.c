#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "variableinterpreter.h"

enum {FALSE,TRUE};

/*uses my version of getword() from exercise 6-1
and a binary tree which holds different binary trees of
groups of variable names that occurred in the input*/

int isvar(char *w);
void printall(struct mastertree *p);

int main(int argc, char **argv){
    if(!(argc >1 && (cmpval=atoi(*++argv))<=MAXVAR))
        cmpval = DEF;
    char word[MAXVAR], **keywrd;
    int varflag = FALSE;
    struct mastertree *root;
    root = NULL;
    while(getword(word,MAXVAR) != EOF){
        if(varflag == FALSE){
            for(keywrd = identifiers;varflag == FALSE && keywrd != '\0';(*keywrd)++)
                if(strcmp(*keywrd,word) == 0)
                    varflag = TRUE;
        }
        else if(isvar(word)){
            addmaintree(root,word);
            varflag = TRUE;
        }
    }
    return 0;
}

int isvar(char *w){
    int varstat;
    char c;
    for(varstat = TRUE;(c=(*w)) != '\0' && varstat == TRUE; w++)
        if(!(isalnum(c) || c == '_' ))
            varstat = FALSE;
    return varstat;
}



