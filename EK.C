/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E K . C                                   //
//                                                            //
//         Code for class Thing                               //
//                                                            //
//************************************************************//

#include "ek.h"

Thing *
Thing::cutover() {
    // placeholder for cutover function.  This function is
    // provided by the user on a case-by-case basis to
    // orchestrate the conversion between an old class
    // data format and a new one.  The function is
    // invoked on an instance of the old class, and should
    // return an instance of the new one.
    return this;
}

int
Thing::docutover() {
    // the user may choose not to cut over some objects
    // on a class data conversion.  This function returns
    // true or false on an object-by-object basis to tell
    // whether the object should be converted to the new
    // format.  This is done mainly for objects shared
    // by multiple envelope classes:  the object needs
    // to be converted exactly once, NOT once per
    // envelope, and docutover can orchestrate when that
    // shared object is converted (by looking at its
    // reference count, keeping a shadow counter, etc.)
    return 1;
}
