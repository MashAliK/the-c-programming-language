#include <stdio.h>
#include <string.h>
#include "wordfreq.h"

int treetoarray(struct tnode *p, struct tnode *s[]){
    static int i;
    if(p != NULL){
        treetoarray(p->l,s);
        s[i++] = p;
        treetoarray(p->r,s);
    }
    return i-1;
}

void swap(struct tnode *s[], int j, int k){
    struct tnode *temp;
    temp = s[j];
    s[j] = s[k];
    s[k] = temp;
}

void qsort(struct tnode *s[], int x, int v){
    int i, prev;
    if(x >= v)
        return;
    swap(s, x, (x+v)/2);
    prev = x;
    for(i = 1+x; i<=v; i++){
        if(s[i]->count < s[x]->count)
            swap(s,i,++prev);
    }
    swap(s,prev,x);
    qsort(s,x,prev-1);
    qsort(s,prev+1,v);
}
