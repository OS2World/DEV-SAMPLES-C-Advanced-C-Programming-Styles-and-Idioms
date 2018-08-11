/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>
#include <string.h>

class String {
public:
    String()                     { rep = new StringRep(""); }
    String(const String& s)      { rep = s.rep; rep->count++; }
    String& operator=(const String& s) {
       s.rep->count++;
       if (--rep->count == 0)
          delete rep;
       rep = s.rep;
       return *this;
    }
    ~String() {
        if (--rep->count <= 0) delete rep;
    }
    String(const char *s)        { rep = new StringRep(s); }
    String operator+(const String&) const;
    int length() const           { return ::strlen(rep->rep); }
private:
    class StringRep {
    public:
        StringRep(const char *s) {
           ::strcpy(rep = new char[::strlen(s)+1], s);
           count = 1;
        }
        ~StringRep() { delete rep; }
        char *rep;
        int count;
    };
    StringRep *rep;
};
