#include <stdio.h>
#include <string.h>
#include "wordfreq.h"

/*This program will be using reusing functions such us
getword() and addtree() from previous exercise to recursively
add distinct entries into a binary tree, however, a quick sort
function is used to sort words on their number of occurrences*/

struct tnode *addtree(struct tnode *p, char *w);

int main(){
    int c;
    char string[MAXWORD], *word;
    word = string;
    struct tnode *root;
    root = NULL;
    while(getword(word,MAXWORD) != EOF){
        root = addtree(root,word);
    }
    struct tnode *wordlist[MAXNUMWORDS];
    qsort(wordlist,0,c = treetoarray(root, wordlist));
    for(;c >= 0;c--)
        printf("%3d:%s\n",wordlist[c]->count,wordlist[c]->word);
    return 0;
}

char *strwrd(char *s){
    char *p;
    p = (char *)(malloc(strlen(s)+1));
    if(p!=NULL)
        strcpy(p,s);
    return p;
}

struct tnode *addtree(struct tnode *p, char *w){
    int cond;
    if(p == NULL){
        p = (struct tnode*) malloc(sizeof(struct tnode));
        p->word = strwrd(w);
        p->l = p->r = NULL;
        p->count = 1;
    }else if((cond = strcmp(w,p->word))<0)
        p->l = addtree(p->l,w);
    else if(cond > 0)
        p->r = addtree(p->r,w);
    else{
        p->count++;
    }
    return p;
}
