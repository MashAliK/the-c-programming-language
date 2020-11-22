#include <stdio.h>
#include <string.h>
#define MAXWORD 100
#define MAXLINE 1000
#define MAXOCCUR 10000

extern int ln;
int getword(char *,int);
char *noisewords[]={"the","of","a","and","so","i","we","this","that",
                "are","also","for","into","it","is","was","in","yes",
                "to","too","\0"};
struct wordtree *addtree(struct wordtree *p, char *w);
void printtree(struct wordtree *);
struct wordtree{
    char *word;
    int count;
    int lineoccur[MAXOCCUR];
    struct wordtree *l;
    struct wordtree *r;
};

int main(){
    struct wordtree *root;
    root = NULL;
    char string[MAXWORD], *word;
    word = string;
    int dstnctwrd;
    while(getword(word,MAXWORD) != EOF && ln <= MAXLINE){
        char **cmpwrd;
        dstnctwrd = 1;
        for(cmpwrd = noisewords;dstnctwrd && **cmpwrd != '\0';cmpwrd++){
            if(strcmp(*cmpwrd,word)==0)
                dstnctwrd = 0;
        }
        if(dstnctwrd){
            root = addtree(root,word);
        }
    }
    printtree(root);
    return 0;
}

char *strwrd(char *s){
    char *p;
    p = (char *)(malloc(strlen(s)+1));
    if(p!=NULL)
        strcpy(p,s);
    return p;
}

struct wordtree *addtree(struct wordtree *p, char *w){
    int cond;
    if(p == NULL){
        p = (struct wordtree*) malloc(sizeof(struct wordtree));
        p->word = strwrd(w);
        p->l = p->r = NULL;
        p->lineoccur[(p->count)=1] = (ln+1);
    }else if((cond = strcmp(w,p->word))<0)
        p->l = addtree(p->l,w);
    else if(cond > 0)
        p->r = addtree(p->r,w);
    else{
        if(p->count< MAXOCCUR){
            p->count++;
            p->lineoccur[p->count] = (ln+1);
        }
    }
    return p;
}

void printtree(struct wordtree *p){
    int i;
    if(p != NULL){
        printtree(p->l);
        printf("%s:",p->word);
        for(i = p->count; i>0; i--)
            printf(" %d",p->lineoccur[i]);
        printf("\n");
        printtree(p->r);
    }
}
