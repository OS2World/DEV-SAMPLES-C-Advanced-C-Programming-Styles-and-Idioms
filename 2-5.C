/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class B {
public:
    B() { p = 0; s = 0; }
    int f();
private:
    char *p;
    short s;
};

class C {
public:
    int g();    // no constructor
private:
    int i;
    B b;
};

class D {
public:
    int h();
private:
    int j, k;
};

C gc;           // p and s initialized, i set to zero

int main() {
    C c;        // p and s initialized, i undetermined
    D d;        // j and k uninitialized
    int l = c.g();
}
