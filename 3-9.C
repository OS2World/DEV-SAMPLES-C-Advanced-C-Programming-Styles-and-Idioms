/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <string.h>

class StringRep {
friend class String;
private:    // private so it does not pollute global name space
    typedef char *Char_p;
    StringRep(StringRep::Char_p* const r) {
        rep = *r; *r = 0; count = 1;
    }
public:
    StringRep(const char *s)
      { ::strcpy(rep = new char[::strlen(s)+1], s); count = 1; }
    ~StringRep() { delete[] rep; }
private:
    char *rep;
    int count;
};

class String {
public:
    String()               { rep = new StringRep(""); }
    String(const String& s) { rep = s.rep; rep->count++; }
    String& operator=(const String& s) {
       s.rep->count++;  if (--rep->count <= 0) delete rep;
       rep = s.rep;
       return *this;
    }
    ~String() { if (--rep->count <= 0) delete rep; }
    String(const char *s)  { rep = new StringRep(s); }
    String operator+(const String&) const;
    int length() const     { return ::strlen(rep->rep); }
private:
    String(StringRep::Char_p* const r) {
        rep = new StringRep(r);  // call new constructor
    }
    StringRep *rep;
};
 
String String::operator+(const String& s) const
{
    char *buf = new char[s.length() + length() + 1];
    ::strcpy(buf, rep->rep);
    ::strcat(buf, s.rep->rep);
    String retval( &buf );  // call the new private constructor
    return retval;
}
