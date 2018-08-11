/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E M P T R . H                             //
//                                                            //
//         Declarations of C++ compiler data structures       //
//                                                            //
//************************************************************//

#define _MPTR_H

// These data structures support the C++ virtual function
// mechanism.  vptp is a general function pointer;  it
// is used to address (but not call) member functions.
// vvptp is a pointer to a function returning a pointer
// to a function;  it is used in some setup idioms in the
// cutover empire.  mptr describes an entry in the
// virtual function table;  it can be derived from your
// C++ compilation system's object code.

typedef int (*vptp)();
typedef vptp (*vvptp)();
struct mptr {short d; short i; vptp f; };
