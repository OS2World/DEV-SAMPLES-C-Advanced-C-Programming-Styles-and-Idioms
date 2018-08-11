/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class String {
friend class StringRep;
public:
    String operator+(const String &s) const { return *p + s; }
    StringRep* operator->() const   { return p; }
    String() {
        (p = new StringRep())->count = 1;
    }
    String(const String& s)  { (p = s.p)->count++; }
    String(const char *s) {
        (p = new StringRep(s))->count = 1;
    }
    String operator=(const String& q) {
        // a little different this time for variety's sake
        if (--p->count <= 0 && p != q.p) delete p;
        (p=q.p)->count++; return *this; 
    }
    ~String()       { if (--p->count<=0) delete p; }
private:
    String(char** r) {
        p = new StringRep(r);
    }
    StringRep *p;
};
