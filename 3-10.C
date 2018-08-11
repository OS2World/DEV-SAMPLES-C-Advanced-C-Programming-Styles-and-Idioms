/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "3-10.h"
#include "3-11.h"

StringRep::StringRep()           { *(rep = new char[1]) = '\e0'; }

StringRep::StringRep(const StringRep& s) {
       ::strcpy(rep=new char[::strlen(s.rep)+1], s.rep);
}

StringRep::~StringRep()          { delete[] rep; }

StringRep::StringRep(const char *s) {
        ::strcpy(rep=new char[::strlen(s)+1], s);
}

String StringRep::operator+(const String& s) const {
        char *buf = new char[s->length() + length() + 1];
        ::strcpy(buf, rep);
        ::strcat(buf, s->rep);
        String retval( &buf );
        return retval;
}

int StringRep::length() const    { return ::strlen(rep); }

void StringRep::print() const    { ::printf("%s\n", rep); }
