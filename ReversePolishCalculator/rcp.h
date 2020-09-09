#include <ctype.h>
#include <math.h>
#define NUMBER '0'
#define SKIP 0
#define MAXOP 100
#define MAXVAL 100
#define MAXBUFFER 100

enum {NO, YES};

int getop(char op[]);
double stof(char operand[]);
int getch(void);
void ungetch(int nextchar);
void push(double);
double pop(void);
double variable[26];

int sp;
double stack[MAXVAL];
void set(void);
