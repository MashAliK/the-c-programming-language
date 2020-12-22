#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXFMT 20

char *checkmod(char *s, char *spc);

void minprintf(char *fmt, ...){
    char fmtspc[MAXFMT];
    va_list ap;
    char *p, *sval, *pfs;
    int ival, c, a, notspec, i, nf, df, castype;
    double dval;
    void *vp;
    va_start(ap, fmt);
    for(p = fmt; *p; p++){
        if(*p != '%'){
            putchar(*p);
            continue;
        }
        i = nf = df = notspec = 0;
        pfs = fmtspc;
        *pfs++ = '%';
        while(i++ < MAXFMT-1 && (*pfs++=c=*++p) && (isdigit(c) || c == '-' || c == '.')){
            if(c == '-'){
                if(nf == 1){
                    notspec = 1;
                    break;
                }else
                    nf = 1;
            }
            if(c == '.'){
                if(df == 1){
                    notspec = 1;
                    break;
                }else
                    df = 1;
            }
        }
        *pfs = '\0';
        if(i >= MAXFMT-1 || !c || notspec){
            pfs = fmtspc+1; //'+1' to ignore the '%'
            printf("%s",pfs);
            continue;
        }
        switch(c){
        case '\0':
            pfs = fmtspc+1;
            printf("%s",pfs);
            continue;
        case 'd': //each of these specifiers behave similarly when used by printf
        case 'i':
        case 'u':
        case 'c':
        case 'x':
        case 'X':
        case 'o':
            ival = va_arg(ap, int);
            p = checkmod(p,pfs);
            printf(fmtspc,ival);
            break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            dval = va_arg(ap, double);
            p = checkmod(p,pfs);
            printf(fmtspc,dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            p = checkmod(p,pfs);
            printf(fmtspc,sval);
            break;
        case 'p':
            vp = va_arg(ap, void *);
            p = checkmod(p,pfs);
            printf(fmtspc,vp);
            break;
        default:
            pfs = fmtspc+1;
            printf("%s",pfs);
            continue;
        }
    }
    va_end(ap);
}

char *checkmod(char *s, char *spc){
    if(*++s == 'h' || *s == 'l'){
        *spc++ = *s;
        *spc = '\0';
    }else{
        s--;
    }
    return s;
}
