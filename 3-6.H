/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>
#include <string.h>

class StringRep {
friend String;
private:     // these are now accessible only to String
    StringRep()           { *(rep = new char[1]) = '\e0'; }
    StringRep(const StringRep& s)  {
      ::strcpy(rep=new char[::strlen(s.rep)+1], s.rep);
    }
    StringRep& operator=(const StringRep& s) {
       if (rep != s.rep) {
         delete[] rep;
         ::strcpy(rep=new char[::strlen(s.rep)+1], s.rep);
       }
       return *this;
    }
    ~StringRep()          { delete[] rep; }
    StringRep(const char *s) {
       ::strcpy(rep=new char[::strlen(s)+1], s);
    }
    StringRep operator+(const StringRep&) const;
    int length() const    { return ::strlen(rep); }
private:
    char *rep;
    int count;
};

StringRep StringRep::operator+(const StringRep& s) const
{
    char *buf = new char[s.length() + length() + 1];
    ::strcpy(buf, rep);
    ::strcat(buf, s.rep);
    StringRep retval( buf );
    delete[] buf;         // get rid of temporary storage
    return retval;
}
