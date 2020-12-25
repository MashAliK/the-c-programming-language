#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#define MAXFORMAT 20
#define flagcheck()
enum {
    SUPRESSION = 1 << 0,
    MAXFLD = 1 << 1,
    WIDTH = 1 << 2
}; //flags used to make sure that each optional specifier is only used once

/* minscanf() uses scanf() to perform the actual formatting
returns the number of successful assignments performed (-1 if EOF is encountered)
stops scanning if input does not match format
uses a modified version of getch() which returns the first non-white space input it encounters
*/

int getch(void);
void ungetch(int);

int minscanf(char *fmt, ...){
    va_list ap;
    char fmtstr[MAXFORMAT], *pfs;
    int cnt, vldspc, vldinp, vldscn, c, spcflg, scanstate;
    va_start(ap, fmt);
    cnt = 0;
    vldinp = 1;
    while(vldinp == 1 && (c=*fmt++) != '\0'){
        if(c != '%'){
            if(!isspace(c) && c != getch())
                vldinp = 0;
            continue;
        }
        pfs = fmtstr;
        *pfs++ = '%';
        vldspc = 1;
        spcflg &= ~(SUPRESSION | MAXFLD | WIDTH);
        while((pfs-fmtstr) < MAXFORMAT  && vldspc == 1 && (c=*pfs++=*fmt++)){
            scanstate = -2; //since -1 is used by EOF
            switch(c){;
            case '*':
                (spcflg & SUPRESSION) ? (vldspc = 0) : (spcflg |= SUPRESSION);
                break;
            case 'h':
            case 'l':
            case 'L':
                (spcflg & WIDTH) ? (vldspc = 0) : (spcflg |= WIDTH);
                break;
            case 'd':
            case 'i':
            case 'o':
            case 'u':
            case 'x':
                *pfs = '\0';
                scanstate = scanf(fmtstr, va_arg(ap, int*));
                break;
            case 'c':
            case 's':
                *pfs = '\0';
                scanstate = scanf(fmtstr, va_arg(ap, char*));
                break;
            case 'e':
            case 'f':
            case 'g':
                *pfs = '\0';
                scanstate = scanf(fmtstr, va_arg(ap, double*));
                break;
            default:
                if(isdigit(c)){
                    if(spcflg & MAXFLD)
                        vldspc = 0;
                    else{
                        while((pfs-fmtstr) < MAXFORMAT && isdigit(c = *fmt++)){
                            *pfs++ = c;
                        }
                        if(!isdigit(c)){
                            spcflg |= MAXFLD;
                            fmt--;
                        }
                        else
                            vldspc = 0;
                    }
                }else
                    vldspc = 0;
            }
            if(scanstate == 0)
                vldinp = 0;
            else if(scanstate == -1)
                return EOF;
            else if(scanstate != -2)
                vldspc += cnt += 1; //sets vldspc to a value greater than 1 allowing us to break out
        }                   //of the loop without triggering the conditional code after the while loop
        *pfs = '\0';
        if(vldspc == 0){
            pfs = fmtstr + 1; //'+1' to ignore '%'
            while(*pfs){
                if(*pfs++ != getch())
                    vldinp = 0;
            }
        }
    }
    return cnt;
}
