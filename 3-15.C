/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "3-14.h"

String *String::newlist = 0;

void String::operator delete(void *p) {
    String *s = (String *)p;
    s->freepointer = newlist;
    newlist = s;
}

void* String::operator new(size_t size) {
    if (size != sizeof(String)) {
        // this check is needed for cases when class
        // derivation is used (Chapter@\*(cE) and the
        // derived class has no operator new.
        // String::operator delete above will field
        // this over-sized block when it is reclaimed.
        return malloc(size);
    } else if (!newlist) {
        newlist = (String *)new char[100 * sizeof(String)];
        for (int i = 0; i < 99; i++) {
            newlist[i].freepointer = &(newlist[i+1]);
        }
        newlist[i].freepointer =0;
    }
    String *savenew = newlist;
    newlist = newlist->freepointer;
    return savenew;
}
