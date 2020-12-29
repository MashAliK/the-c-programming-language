#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMLINE 50
#define MAXLINE 100
#define MAXNAME 30

int main(int argc, char *argv[]){
    char line[MAXLINE], header[MAXLINE], *prog, filename[MAXNAME], *ext, temp[MAXNAME];
    prog = *argv++;
    int i, pg;
    FILE *fp, *nfp;
    if(argc < 2){
        printf("Error: Expected filename as input\n");
    }
    else{
        while(argc-- > 1){
            if((fp=fopen(*argv, "r")) == NULL){
                fprintf(stderr, "%s: can't open %s\n",prog, *argv);
                exit(1);
            }
            strcpy(filename,*argv);
            if((ext=strrchr(filename, '.')) != NULL){ //if the file has an extension
                strcpy(temp, ext);
                strcpy(ext, "_formatted");
                strcat(filename,temp);
            }else
                strcat(filename,"_formatted");
            if((nfp=fopen(filename, "w")) == NULL){
                fprintf(stderr, "%s: can't create new file\n",prog);
                exit(2);
            }
            for(i = 1, pg = 1; fgets(line, MAXLINE, fp); i++){
                if(((i-1)%NUMLINE) == 0){
                    sprintf(header,"Page: %d\t\t%s\n", pg++, filename);
                    fputs(header, nfp);
                    i++;
                }
                fputs(line,nfp);
            }
            argv++;
        }
    }
    return 0;
}
