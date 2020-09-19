#include <stdio.h>
#include <ctype.h>

enum {NO, YES};

#define MAXWORD 100
#define check(ch) if(c == ch)\
                    if(!isalnum(c = getch())){\
                        ungetch(c);\
                        c = ch;     \
                        return NO;}  //returns 0 if char is not
                                    //proceeded by an appropriate input

/*improved version of getword() which uses recursion to
skip comments and string constants. Also handles preprocessor
control lines and underscores appropriately
*/

int getch(void);
void ungetch(int);
int getword(char *w, int max);

int main(){
    char word[MAXWORD];
    while(getword(word, MAXWORD) != EOF)
        printf("%s\n",word);
    return 0;
}

int newline = YES;
int c;

int skipcomment(){
    int endstate = 0;
    while(c = getch()){
        if(!endstate && c == '*')
            endstate = 1;
        else if(endstate && c == '/')
            return checkword();
        else
            endstate = 0;
    }
}

int exitstring(){
    int bslash = 0;
    while(c = getch()){
        if(c == '\\')
            bslash++;
        else if(c == '"')
            if((bslash % 2) == 0)
                return checkword();
        else
            bslash = 0;
    }
}

int checkword(){
    while(isspace(c = getch()))
        ;
    if(c == '/'){
        if((c = getch()) == '/'){
            while((c = getch()) != '\n')
                ;
            return checkword();
        }
        else if(c == '*')
            return skipcomment();
        else{
            ungetch(c);
            c = '\\';
            return NO;
        }
    }
    if(c == '"')
        return exitstring();
    check('#');
    check('_');
    if(isalnum(c) || c == '_')
        return YES;
    else
        return NO;
}

int getword(char *w, int max){
    int valword;
    valword = checkword();
    *w++ = c;
    if(valword == NO){
        *w = '\0';
        return c;
    }else{
        for(;--max > 0;w++)
            if(!isalnum(*w = getch())){
                ungetch(*w);
                break;
            }
    }
    *w = '\0';
    return c;
}

