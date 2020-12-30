#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
#include <time.h>
#define MAX_PATH 1024
#ifndef DIRSIZ
#define DIRSIZ 14
#endif

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

int main(int argc, char *argv[]){
    if(argc == 1)
        fsize(".");
    else
        while(--argc > 0)
            fsize(*++argv);
    return 0;
}

void fsize(char *name){
    struct stat stbuf;
    struct tm t;
    if(stat(name, &stbuf) == -1){
        fprintf(stderr, "fsize: can't print %s\n", name);
        return;
    }
    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("inode device:%4ld inode number:%4ld size:%8ld name:%s\n",stbuf.st_dev
           ,stbuf.st_ino,stbuf.st_size,name);
    t = *localtime(&stbuf.st_atime);
    printf("last accessed: %d/%d/%d %d:%d\t", t.tm_mday ,
	      t.tm_mon, (1900 + t.tm_year),  t.tm_hour, t.tm_min);
    t = *localtime(&stbuf.st_mtime);
    printf("last modified: %d %d/%d %d:%d\n",t.tm_mday ,
	      t.tm_mon, (1900 + t.tm_year),  t.tm_hour, t.tm_min);
}

void dirwalk(char *dir, void (*fcn)(char *)){
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;
    if((dfd=opendir(dir))==NULL){
        fprintf(stderr, "dirwalk: can't print %s\n", dir);
        return;
    }
    while((dp=readdir(dfd))!=NULL){
        if(strcmp(".",dp->d_name) == 0 || strcmp("..",dp->d_name) == 0)
            continue;
        if(strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s\n", dir,dp->d_name);
        else{
            sprintf(name,"%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

