/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>
#include <string.h>

class String;

class StringRep {
friend String;
private:
    StringRep();
    StringRep(const StringRep& s);
    ~StringRep();
    StringRep(const char *s);
    String operator+(const String&) const;
    int length() const;
    void print() const;
private:
    StringRep(char** const r);
    char *rep;
    int count;
};
