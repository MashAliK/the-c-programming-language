#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct{
    unsigned int _READ : 1;
    unsigned int _WRITE : 1;
	unsigned int _UNBUF : 1;
	unsigned int _EOF : 1;
	unsigned int _ERR : 1;
} flgfld;

typedef struct _iobuf{
    int cnt;
    char *ptr;
    char *base;
    flgfld flag;
    int fd;
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(char *, char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE*);

#define feof(p) (((p)->flag._EOF) != 0)
#define ferror(p) (((p)->flag._ERR) != 0)
#define fileno(p) ((p) ->fd)

#define getc(p) (--(p)->cnt >= 0 \
		? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) ((--(p)->cnt >= 0) \
        ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE *fopen(char *name, char *mode){
    int fd;
    FILE *fp;
    if(*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for(fp = _iob; fp < _iob+OPEN_MAX; fp++)
        if(fp->flag._READ == 0 && fp->flag._WRITE == 0)
            break;
    if(fp >= _iob+OPEN_MAX)
        return NULL;
    if(*mode == 'w')
        fd = creat(name, PERMS);
    else if(*mode == 'a'){
        if((fd=open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }else
        fd = open(name, O_RDONLY, 0);
    if(fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if(*mode == 'r')
        fp->flag._READ = 1;
    else
       fp->flag._WRITE = 1;
    return fp;
}

int _fillbuf(FILE *fp){
    int bufsize;
    if(fp->flag._READ != 1 || fp->flag._ERR == 1 || fp->flag._EOF== 1)
        return EOF;
    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ;
    if(fp->base == NULL)
        if((fp->base = (char*) malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if(--fp->cnt < 0){
        if(fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* empties buffer onto FILE pointer provided and returns a zero value if successful*/
int fflush(FILE *fp){
    int bufsize, n;
    n = (bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ) - fp->cnt;
    if(write(fp->fd, fp->base, n) == NULL)
        return EOF;
}

int _flushbuf(int c, FILE *fp){
    int bufsize;
    if(fp->flag._WRITE != 1 || fp->flag._ERR == 1 || fp->flag._EOF== 1)
        return EOF;
    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ;
    if(fp->base == NULL){
        if((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    }else if(bufsize != 1)
        fflush(fp);
    if(bufsize == 1){
        *fp->base = c;
        fp->cnt = 0;
        write(fp->fd ,fp->base,bufsize);
        return c;
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize-1;
    return *fp->ptr++ = c;
}

int fclose(FILE *fp){
    if(fp->flag._WRITE == 1 && fp->flag._UNBUF == 0){
        if(fflush(fp) == EOF) //flush whatever is remaining in the buffer
            return EOF;
    }
    free(fp->base);
    fp->base = NULL;
    fp->fd = NULL;
}

FILE _iob[OPEN_MAX]={
    {0, (char*) 0, (char*) 0, {1,0,0,0,0}, 0 },
    {0, (char*) 0, (char*) 0, {0,1,0,0,0}, 1 },
    {0, (char*) 0, (char*) 0, {0,1,1,0,0}, 2 }
};

int main(int argc, char *argv[]){
    char c, *prog;
    prog = *argv++;
    FILE *fp;
    if(argc == 1){
        while((c=getc(stdin)) != EOF){
            putc(c,stdout);
        }
        fclose(stdout);
    }
    else{
        while(argc-- > 1){
            if((fp=fopen(*argv, "w")) == NULL){
                exit(1);
            }
            while((c=getc(stdin)) != EOF){
                if(putc(c, fp) == EOF)
                    exit(2);
            }
            fclose(fp);
        }
    }
    exit(0);
}
