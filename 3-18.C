/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stddef.h>

void *operator new(size_t, void *p) { return p; }

struct S {
    S();
    ~S();
};

char buf [sizeof(S)][100];
int bufIndex = 0;

void f() {
    S a;    // automatic allocation/initialization

    S *p = new S;          // explicit allocation
                           // operator new finds the store
                           // automatic initialization
    delete p;              // explicit deletion
                           // automatic cleanup

    S *ppp = new (buf) S;  // explicit allocation in buf
                           // automatic initialization
    ppp->S::~S();          // explicit cleanup

    // "a" automatically cleaned up/deallocated
    //    on return from f()
}
