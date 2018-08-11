/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "k.h"       // from above

#include "9-3.h"     // for Envelope member functions

extern Thing *envelope, *letter; // exemplar pointers

class Envelope: public Top {     // Top defined in k.h
public:
    Letter *operator->() const { // forwards all operations
        return rep;              // to rep
    }
    Envelope()    { rep = letter->make(); }
    Envelope(Letter&);
    ~Envelope() {
        if (rep && rep->deref() <= 0) delete rep;
    }
    Envelope(Envelope& x) {
        (rep = x.rep)->ref();
    }
    Envelope& operator=(Envelope& x) {
        if (rep != x.rep) {
            if (rep && rep->deref() <= 0) delete rep;
            (rep = x.rep)->ref();
        }
        return *this;
    }
    Thing *type() { return envelope; }
private:
    static void *operator new(size_t) {
        Sys_Error("heap Envelope");
    }
    static void operator delete(void *) { }
    Letter *rep;
};
