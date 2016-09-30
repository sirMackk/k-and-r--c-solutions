/* 8-5: Modify the fsize program to print the other information contained in the inode entry.
 */

/* To keep things compact, I'll keep everything in one file. */

#define NAME_MAX 14

/* Will use system's structures and routines from dirent.h for compatibility */

/*typedef struct {*/
		/*long ino;*/
		/*char name[NAME_MAX+1];*/
/*} Dirent;*/

/*typedef struct {*/
		/*int fd;*/
		/*Dirent d;*/
/*} DIR;*/

/*DIR *opendir(char *dirname);*/
/*Dirent *readdir(DIR *dfd);*/
/*void closedir(DIR *dfd);*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

void fsize (char *);

int main (int argc, char *argv[])
{
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

/*int stat(char *, struct stat *);*/
void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if (S_ISDIR(stbuf.st_mode))
        dirwalk(name, fsize);
    printf("%8ld %ld %ld %s\n", stbuf.st_size, stbuf.st_ino, stbuf.st_uid, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0
            || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }

    closedir(dfd);
}

/* Using system defined routines instead of these custom ones from the book. */

/*int fstat(int fd, struct stat *);*/

/*DIR *opendir(char *dirname)*/
/*{*/
    /*int fd;*/
    /*struct stat stbuf;*/
    /*DIR *dp;*/

    /*if ((fd = open(dirname, O_RDONLY, 0)) == -1*/
            /*|| fstat(fd, &stbuf) == -1*/
            /*|| (stbuf.st_mode & S_IFMT) != S_IFDIR*/
            /*|| (dp = (DIR *) malloc(sizeof(DIR))) == NULL)*/
        /*return NULL;*/
    /*dp->fd = fd;*/
    /*return dp;*/
/*}*/

/*void closedir(DIR *dp)*/
/*{*/
    /*if (dp) {*/
        /*close(dp->fd);*/
        /*free(dp);*/
    /*}*/
/*}*/

/*#include <sys/dir.h>*/

/*Dirent *readdir(DIR *dp)*/
/*{*/
    /*struct direct dirbuf;*/
    /*static Dirent d;*/

    /*while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {*/
        /*if (dirbuf.d_ino == 0)*/
            /*continue;*/
        /*d.ino = dirbuf.d_ino;*/
        /*strncpy(d.name, dirbuf.d_name, DIRSIZ);*/
        /*d.name[DIRSIZ] = '\0';*/
        /*return &d;*/
    /*}*/

    /*return NULL;*/
/*}*/
