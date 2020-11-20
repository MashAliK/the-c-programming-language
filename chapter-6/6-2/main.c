#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "variableinterpreter.h"

enum {FALSE,TRUE};

/*uses my version of getword() from exercise 6-1
and a binary tree which holds different binary trees of
groups of variable names that occurred in the input*/

char *id[] = {"int",
        "double","float","char",
        "void","\0"};
void printall(struct mastertree*);
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
            for(keywrd = id;varflag == FALSE && **keywrd != '\0';keywrd++)
                if(strcmp(*keywrd,word) == 0)
                    varflag = TRUE;
        }
        else if(isvar(word)){
            root = addmaintree(root,word);
            varflag = FALSE;
        }
    }
    printall(root);
    return 0;
}

int isvar(char *w){
    int varstat = TRUE;
    char c;
    if(!isalpha(c=(*w++)))
        varstat = FALSE;
    while((c=(*w)) != '\0' && varstat == TRUE)
        if(!isalnum(c=(*w++)))
            varstat = FALSE;
    return varstat;
}

void printtree(struct vargroup *s){
    if(s!=NULL){
       printtree(s->l);
       printf("%s\n",s->varname);
       printtree(s->r);
    }
}

void printall(struct mastertree *p){
    if(p!=NULL){
       printall(p->l);
       printf("\n");
       printtree(p->root);
       printall(p->r);
    }
}



