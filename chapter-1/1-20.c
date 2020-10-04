#include <stdio.h>

#define MAXLEN 1000
#define N 8 //n should be a symbolic parameter because it has to be constant

int getline(char s[]);

int main(){
    int i, j, col, spaces;
    char line[MAXLEN];
    while(getline(line) != EOF){
        for(i = 0, col = 1; line[i] != '\n'; i++){
            if(line[i]  == '\t'){
                spaces = N - ((col-1) % N);
                for(j = spaces; j > 0; --j)
                    putchar(' ');
                col += spaces;
            }else{
                putchar(line[i]);
                col++;
            }
        }
        putchar('\n');
    }
    return 0;
}

int getline(char s[]){
    int c, i;
    for(i = 0; i < MAXLEN-1 && (c = getchar()) != '\n' && c != EOF; i++)
        s[i] = c;
    if(c == EOF)
        return EOF;
    else if(c == '\n'){
        s[i++] = '\n';
        s[i] = '\0';
        return i;
    }else{
        printf("Error: Line too long\n");
        s[i] = '\0';
        return i;
    }
}
