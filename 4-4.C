/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

void f(int j) { /* . . . . */ }

class A {               // base class (superclass)
public:
    void f(int);
    // . . . .
};

class B: public A {     // derived class (subclass)
public:
    void f(double);
    void g(int);
    // . . . .
};

void B::g(int k) {
    f(k);               // B::f(double) with promotion
    A::f(k);            // A::f(int);
    this->A::f(k);      // A::f(int);
    ::f(k);             // ::f(int);
}

int main() {
    A *a;
    B *b;
    int i;
    // . . . .
    a->f(1);        // A::f(int)
    a->f(3.0);      // A::f(int) with coercion int(3.0)
    b->f(2);        // B::f(double) with promotion double(2)
    b->f(2.0);      // B::f(double)
    b->A::f(7.0);   // A::f(int) with coercion int(7.0)
    b->g(10);       // B::g(int)
}
