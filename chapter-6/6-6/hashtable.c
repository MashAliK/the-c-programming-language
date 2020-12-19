#include <stdio.h>
#include <string.h>
#define HASHSIZE 101
#include "preprocessor.h"

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *w){
    unsigned hashval;
    for(hashval = 0; *w != '\0'; w++)
        hashval = *w + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *w){
    struct nlist *p;
    for(p = hashtab[hash(w)]; p != NULL; p = p->next)
        if(strcmp(w,p->name) == 0)
            return p;
    return NULL;
}

char *wrdstr(char *s){
    char *p;
    p = (char *) malloc(strlen(s)+1);
    if(p != NULL)
        strcpy(p,s);
    return p;
}

struct nlist *install(char *w, char *r, int n){
    struct nlist *p;
    unsigned hashval;
    if((p = lookup(w)) == NULL){
        p = (struct nlist*) malloc(sizeof(p));
        if(p == NULL || (p->name = wrdstr(w)) == NULL)
            return NULL;
        hashval = hash(w);
        p->next = hashtab[hashval];
        p->deflen = n;
        hashtab[hashval] = p;
    }else
        free((void *) p->defn);
    if((p->defn = wrdstr(r)) == NULL)
        return NULL;
    p->deflen = n;
    return p;
}

/*prev points to the previous structure in the list. If the
current structure contains the word to be removed, the
previous structure is linked to the next one from the current.
*/

void undef(char *w){
    struct nlist *crnt, *prev;
    int i;
    unsigned c;
    for(crnt = hashtab[c = hash(w)],prev = NULL
        ; crnt != NULL; prev = crnt,crnt = crnt->next){
        if(strcmp(crnt->name,w)==0){
            if(prev == NULL)
                hashtab[c] = crnt->next;
            else
                prev->next = crnt->next;
            return;
        }
    }
}
