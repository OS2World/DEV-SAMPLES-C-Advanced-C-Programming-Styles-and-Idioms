/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>
#include <stddef.h>

void *operator new(size_t, void *p) { return p; }

class Foo {
public:
    Foo() { rep = 1; }
    Foo(int i) { rep = i; }
    ~Foo() { rep = 0; }
    void print() { cout << rep << "\en"; }
private:
    int rep;
};

struct { int:0; };  // machine-dependent alignment
char foobar[sizeof(Foo)];

Foo foefum;

int main()
{
    foefum.print();
    (&foefum)->Foo::~Foo();   // cause premature cleanup of
                              // object with global extent
    foefum.print();           // undefined results!
    Foo *fooptr = new(foobar) Foo;
    fooptr->Foo::~Foo();
    fooptr = new(foobar) Foo(1);   // unrelated to earlier
                                   //   allocation
    fooptr->Foo::~Foo();      // cause premature cleanup
                              // do NOT delete fooptr
    fooptr = new Foo;
    delete fooptr;
}
