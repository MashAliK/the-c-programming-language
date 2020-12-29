#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void filecopy(int, int, char*, char*);

int main(int argc, char *argv[]){
    int fd;
    char *prog;
    prog = *argv++;
    if(argc == 1)
        filecopy(0, 1, prog, "stdin");
    else{
        while(argc-- > 1){
            if((fd = open(*argv, O_RDONLY, 0)) == -1){
                fprintf(stderr, "%s: cannot open %s", prog, *argv);
                exit(1);
            }
            filecopy(fd, 1, prog, *argv);
            close(fd);
            argv++;
        }
    }
    exit(0);
}

void filecopy(int f, int out, char *p, char *in){
    char buf[BUFSIZ];
    int nr, nw;
    while((nr=read(f, buf, BUFSIZ)) > 0){
        nw = write(out, buf, nr);
        if(nw == -1){
            fprintf(stderr, "%s: cannot output\n", p);
            exit(2);
        }
    }
    if(nr == -1){
        fprintf(stderr, "%s: cannot read from %s\n", p, in);
        exit(3);
    }
}
