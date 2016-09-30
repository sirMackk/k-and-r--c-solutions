/* 8-6: The standard library function calloc(n, size) returns a pointer to
 * n object of size size, with the storage initialized to zero. Write calloc,
 * by calling m_malloc or by modifying it. */

#include <stdio.h>

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned int size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned int);
void m_free(void *);


void *m_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned int nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

#define NALLOC 1024

static Header *morecore(unsigned int nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) - 1)
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;
    m_free ((void *)(up + 1));
    return freep;
}

void m_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *) ap -1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        p->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

void *m_calloc(int n, int size)
{
    int i;
    char *p;

    p = m_malloc(n * size);

    if (p == NULL)
        return NULL;

    for (i = 0; i < n * size; i++)
        p[i] = 0;

    return p;
}


int main()
{
    char *p;
    p = (char *) m_calloc(1, 16);
    sprintf(p, "Hello %s\n", "world");
    printf("%s", p);
    return 0;
}

