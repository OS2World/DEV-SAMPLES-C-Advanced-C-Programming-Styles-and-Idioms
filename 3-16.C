/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>
#include <string.h>

class String {
private:
          static String *newlist;
          union {
               String *freepointer;
               char *rep;
          };
          int len;
public:
          enum { POOLSIZE = 1000 } ;
          String() { rep = new char[1]; *rep = '\e0'; }
          String(const char *s) {
              rep = new char[::strlen(s)+1];
              ::strcpy(rep,s);
          }
          ~String() { delete[] rep; }
    void  *operator new(size_t);
    void  operator delete(void*);
          // . . . .    // other interesting operations
};
