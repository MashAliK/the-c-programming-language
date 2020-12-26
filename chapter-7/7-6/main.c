#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCMP 1000

int main(int argc, char *argv[])
{
    FILE *pf1, *pf2;
    char *prog = *argv++, line1[MAXCMP], line2[MAXCMP];
    int i, difflg;
    if(argc >= 3){
        if((pf1 = fopen(*argv++, "r")) == NULL){
            fprintf(stderr,"%s: can't access %s\n",prog,*argv);
            exit(1);
        }
        if((pf2 = fopen(*argv++, "r")) == NULL){
            fprintf(stderr,"%s: can't access %s\n",prog,*argv);
            exit(1);
        }
        for(i = 1, difflg = 0; !difflg && fgets(line1,MAXCMP,pf1) != NULL && fgets(line2,MAXCMP,pf2) != NULL; i++){
            if(strcmp(line1,line2) != 0)
                difflg = 1;
        }
        if(difflg)
            fprintf(stdout,"Programs first differ on line %d\n",i-1);
        else
            fprintf(stdout,"Programs do not differ\n");
        fclose(pf1);
        fclose(pf2);
    }else{
        fprintf(stderr,"%s: two program names not provided as arguments\n", prog);
        exit(2);
    }
    if(ferror(stdout)){
        fprintf(stderr,"%s: error writing stdout\n", prog);
        exit(3);
    }
    return 0;
}
