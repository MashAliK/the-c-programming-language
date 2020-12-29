#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

/* pattern-searching program finds the occurrences of the first argument from the input
files given as arguments will be searched and their file name along with line number will be
printed once the pattern is found
standard input is used if no file names are given
*/

int main(int argc, char *argv[]){
    char line[MAXLINE], *prog, *pattern;
    int i;
    FILE *fp;
    prog = *argv++;
    if(argc == 1)
        printf("Error: no arguments\n");
    else{
        pattern = *argv++;
        if(argc == 2){ //no file names provided
            for(i = 1; gets(line); i++){
                if(strstr(line,pattern) != NULL)
                    printf("%d: %s\n", i, line);
            }
        }else{
            while(argc-- > 2){
                if((fp = fopen(*argv, "r")) == NULL){
                    fprintf(stderr, "%s: can't open %s\n",prog, *argv);
                    exit(1);
                }else{
                    for(i = 1; fgets(line, MAXLINE, fp); i++){
                        line[strlen(line)-1] = '\0'; //remove newline
                        if(strstr(line,pattern) != NULL)
                            printf("%d on %s: %s\n", i, *argv, line);
                    }
                    argv++;
                    fclose(fp);
                }
            }
        }
    }
    if(ferror(stdout)){
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    return 0;
}
