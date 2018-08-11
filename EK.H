/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//      F I L E :   E K . H                                   //
//                                                            //
//         Declarations for classes Thing and Top             //
//                                                            //
//************************************************************//

#ifndef _MPTR_H
#include "emptr.h"
#endif

#define _K_H
#include <String.h>

//  MACHINE AND COMPILER DEPENDENT
const unsigned int WRDSIZE = sizeof(void*);

inline size_t
Round(size_t s) {
    return (size_t)((s + WRDSIZE - 1)/WRDSIZE)*WRDSIZE;
}

// commonly used character pointer type
typedef char *Char_p;

// dummy type, simply used to disambiguate between
// constructors of ShapeRep derived classes
enum Exemplar { };

//  MACHINE AND COMPILER DEPENDENT

class Top {
public:
    // This class has no data, except __vtbl which is
    // provided by the compiler.  Deriving all classes
    // from this class assures that the __vtbl will
    // always be the first element in any object.
    // If that is not true for the compiler being
    // used, then other mechanisms will be necessary
    // to find the __vtbl, and the implementation
    // here may need to change (viz., findVtblEntry).

    // This also reserves a __vtbl slot for system
    // internal use

    virtual ~Top() { }
    mptr* findVtblEntry(vptp);
    void update(String, String, const char *const = "");
    static void operator delete(void *p) {
        ::operator delete(p);
    }
    // doit is a general-purpose function to help users
    // to orchestrate update.
    virtual Top *doit();
protected:
    Top()  { }
    static void *operator new(size_t l) {
        return ::operator new(l);
    }
private:
    // compare two function pointers for equality
    int compareFuncs(int, vptp, vptp);
};

typedef Top *Topp;

class Thing: public Top {
    // All  "rep" fields are derived from Thing;  it defines
    // the canonical form for all Letter classes
public:
    virtual Thing *type() { return this; }
    Thing() { }
    virtual Thing *cutover();       // field update function
    virtual ~Thing() { }            // destructor
    int docutover();
};

typedef Thing *Thingp;
