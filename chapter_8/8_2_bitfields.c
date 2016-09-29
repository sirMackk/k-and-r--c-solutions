/* 8-2: Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed. */

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

/* 8-2 - bit fields */

struct _flags {
    unsigned int _READ : 1;
    unsigned int _WRITE : 1;
    unsigned int _UNBUF : 1;
    unsigned int _EOF : 1;
    unsigned int _ERR : 1;
};

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    struct _flags flags;
    int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0]);
#define stdout (&_iob[1]);
#define stderr (&_iob[2]);

/*enum _flags {*/
    /*_READ = 01,*/
    /*_WRITE = 02,*/
    /*_UNBUF = 04,*/
    /*_EOF = 010,*/
    /*_ERR = 020*/
/*};*/



int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag._EOF  != 0)
#define ferror(p) (((p)->flag._ERR != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
        ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
        ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flags._READ == 0 && fp->flags._WRITE == 0)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flags._UNBUF = 0;
    fp->flags._EOF = 0;
    fp->flags._ERR = 0;

    if (*mode == 'r') {
        fp->flags._READ = 1;
        fp->flags._WRITE = 0;
    } else {
        fp->flags._READ = 0;
        fp->flags._WRITE = 1;
    }

    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!fp->flags._READ || fp->flags._ERR || fp->flags._EOF)
        return EOF;
    bufsize = (fp->flags._UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL)
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flags._EOF = 1;
        else
            fp->flags._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = {
    {0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0},
    {0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1},
    {0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2}
};

int main()
{
    return 0;
}
