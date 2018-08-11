/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 3 T R I B . C                         //
//                                                            //
//         Code for version 3 of class Triangle               //
//                                                            //
//************************************************************//

#include "ev3tri.h"

Shape
Triangle::make(Coordinate pp1, Coordinate pp2, Coordinate pp3)
{
    Triangle *retval = new Triangle;
    retval->p1 = pp1;
    retval->p2 = pp2;
    retval->p3 = pp3;
    retval->exemplarPointer = this;
    return *retval;
}

Triangle::Triangle() {  }  // size and vptr knowledge are in here
