/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>

class String {
public:
    String();              // default constructor
    String(const String&); // copy constructor
    String& operator=(const String&);  // assignment
    ~String();             // destructor
    String(const char*);   // create a String from a "C string"
    String operator+(const String&) const;
                           // redefine "+" to mean catenation
    int length() const;    // length of string in characters
    const char *const C_rep() {
        return (const char *const)rep;
    }
private:
    char *rep;
};

int main() {
    String s;
    // . . . .
    printf("string is %s\en", s.C_rep());
}
