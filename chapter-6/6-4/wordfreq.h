#define MAXWORD 1000
#define MAXNUMWORDS 10000
struct tnode{
    char *word;
    int count;
    struct tnode *l;
    struct tnode *r;
};
int getword(char *, int);
void qsort(struct tnode *s[], int x, int v);
int treetoarray(struct tnode *p, struct tnode *s[]);
