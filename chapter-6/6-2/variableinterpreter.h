#define DEF 6
#define MAXVAR 100

char *identifiers[] = {"int",
        "double","float","char",
        "void"};
struct vargroup{
    char *varname;
    struct vargroup *l;
    struct vargroup *r;
};
struct mastertree{
    struct vargroup *root;
    struct mastertree *l;
    struct mastertree *r;
};
int cmpval;
struct mastertree *addmaintree(struct mastertree *p, char *w);
int getword(char *w, int);
