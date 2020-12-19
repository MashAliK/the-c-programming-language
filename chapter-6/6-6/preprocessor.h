#define MAXWORD 25
#define MAXLINE 1000
#define NUMLINE 100
enum {FALSE, TRUE};
enum {VALID, EXCEED, INVDEF};
enum {NONE, QUOTE, SINQUOTE, COM, SINCOM, NEWL, WORD, WORDNUM, BLANK, OTH};

struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
    int deflen;
};
struct nlist *install(char*, char *, int);
struct nlist *lookup(char*);
int getch(void);
void ungetch(int);
int getobj(char s[], int *len);
void pushobj(char *s, int len, int state);
