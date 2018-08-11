/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "3-6.h"

class String {
public:
    String() {
        rep = new StringRep; rep->count=1;
    }
    String(const String& s) {
        rep = s.rep; rep->count++;
    }
    String& operator=(const String& s) {
       s.rep->count++;
       if (--rep->count <= 0) delete rep;
       rep = s.rep;  return *this;
    }
    ~String()           {
        if (--rep->count <= 0) delete rep;
    }
    String(const char *s) {
       rep = new StringRep(s);
       rep->count = 1;
    }
    String operator+(const String& s) const {
       StringRep y = *rep + *s.rep;
       return String(y.rep);
    }
    int length() const {
        return rep->length();
    }
private:
    StringRep *rep;
};
