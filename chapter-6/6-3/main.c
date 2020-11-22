#include <stdio.h>
#include <string.h>
#define MAXWORD 100
#define MAXLINE 1000

int getword(char,int);
char *noisewords[]{"the","of","a","and","so","i","we","this","that",
                "are","also","for","into","it","is","was","in","\0"};
struct wordtree{
    char *word;
    int count;
    int lineoccur[MAXLINE];
    struct wordtree *l;
    struct wordtree *r;
};

int main()(
    struct wordtree* root = NULL;
    char *word;
    int linenum, dstnctwrd;
    for(linenum = 0; getword(word,MAXWORD) != EOF && linenum < MAXLINE; linenum++){
        char **cmpwrd;
        dstnctwrd = 1;
        for(cmpwrd = noisewords;dstnctwrd && **cmpwrd != '\0';cmpwrd++){
            if(strcmp(*cmpwrd,word)==0)
                dstnctwrd = 0;
        }
    }
    return 0;
)

char *strwrd(char *s){
    char *p;
    p = (char *)(malloc(strlen(s)+1));
    if(p!=NULL)
        strcpy(p,s);
    return p;
}

struct wordtree *addtree(struct wordtree *p, char *w, int ln){
    int cond;
    if(p == NULL){
        p = (struct wordtree*) malloc(sizeof(struct wordtree));
        p->word = strwrd(w);
        p->l = p->r = NULL;
        p->lineoccur[(p->count)=1] = ln;
    }else if((cond = strcmp(p->word,w))<0)
        p->l = addtree(p->l,w);
    else if(cond > 0)
        p->r = addtree(p->r,w);
    else{
        p->count++;
        p->lineoccur[p->count] = ln;
    }
    return s;
}
