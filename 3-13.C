/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

// stddef.h to get size_t
#include <stddef.h>

#define HEAP_BASE_ADDRESS 0x001000;

struct Head {
   long length;
   struct Head *next;
};

static Head pool = { 0, 0 };

static Head *h = (Head *)HEAP_BASE_ADDRESS;

/* fast dumb first-fit allocator */

typedef char *Char_p;

// NEXT LINE IS MACHINE AND COMPILER DEPENDENT:
const long WRDSIZE = sizeof(void*);

void* operator new(size_t nbytes)
{
    /* First, look in free list */
    if (pool.next) {
        Head *prev = &pool;
        for (Head *cur = &pool; cur; cur = cur->next) {
            if (cur->length >= nbytes) {
                prev->next = cur->next;
                return (void*)(Char_p(cur) + sizeof(Head));
            } else prev = cur;
        }
    }
    /* Nothing on free list, get new block from heap */
    h = (Head*)(((int)((Char_p(h)+WRDSIZE-1))/WRDSIZE)*WRDSIZE);
    h->next = 0;
    h->length = nbytes;
    h += nbytes + sizeof(Head);
    return (void*)(Char_p(h) + sizeof(Head));
}

void operator delete(void *ptr)
{
    Head *p = (Head *)(Char_p(ptr) - sizeof(Head));
    p->next = pool.next;
    pool.next = p;
}
