/* 8-8: Write a routine bfree(p, n) that will free an arbitrary block p of n
 * characters into the free list maintained by malloc and free. By using bfree
 * a user can add a static or external array to the free list at any time. */

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
void *bfree(void *, unsigned int);


void *m_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned int nunits;

    if (nbytes == 0)
        return NULL;

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

    if (ap == NULL)
        return;

    bp = (Header *) ap - 1;

    if (bp->s.size < 1)
        return;

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

void *bfree(void *p, unsigned int n)
{
    Header *h;
    unsigned int nunits;

    h = (Header *) p;
    nunits = n / sizeof(Header);

    if (freep == NULL) {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    h->s.size = nunits;
    m_free((void *) (h + 1));
    return (void *) (h + 1);
}


int main()
{
    int p[128];
    bfree(p, 64);

    sprintf((char *) p, "Hello %s\n", "world");
    printf("%s", (char *) p);
    return 0;
}

