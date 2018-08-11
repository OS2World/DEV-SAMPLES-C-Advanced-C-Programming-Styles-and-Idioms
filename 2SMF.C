/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>

class X {
public:
    // ...
    void foo() { fooCounter++;  /* . . . . */ }
    static void printCounts() {
        printf("foo called %d times\en", fooCounter);
    }
private:
    static int fooCounter;
};

int X::fooCounter = 0;

int main() {
    // printCounts();     // error (unless there really
                       //        is a global function f())
    X::printCounts();  // fine
}
