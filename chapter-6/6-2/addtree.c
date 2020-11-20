#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variableinterpreter.h"

char *strvar(char *s){
    char *p;
    p = (char *)(malloc(strlen(s)+1));
    if(p!=NULL)
        strcpy(p,s);
    return p;
}

struct vargroup *addgroup(struct vargroup *s, char *w){
    int cond;
    if(s == NULL){
        s = (struct vargroup*) malloc(sizeof(struct vargroup));
        s->varname = strvar(w);
        s->l = s->r = NULL;
    }else if((cond = strncmp(s->varname,w,cmpval))<0)
        addgroup(s->l,w);
    else
        addgroup(s->r,w);
    return s;
}

struct mastertree *addmaintree(struct mastertree *p, char *w){
    int cond;
    if(p == NULL){
        p = (struct mastertree*) malloc(sizeof(struct mastertree));
        p->root = addgroup(NULL, w);
        p->l = p->r = NULL;
    }else if((cond = strncmp(p->root->varname,w,cmpval))==0)
        addgroup(p->root,w);
    else if(cond < 0)
        addmaintree(p->l,w);
    else
        addmaintree(p->r,w);
    return p;
}


