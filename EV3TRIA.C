/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 3 T R I A . C                         //
//                                                            //
//         Code for version 3 of class Triangle               //
//                                                            //
//************************************************************//

#include "ev3tri.h"

Shape
Triangle::make()
{
    printf("Triangle::make() entered\n");
    Triangle *retval = new Triangle;;
    retval->p1 = retval->p2 = retval->p3 = Coordinate(0,0);
    retval->exemplarPointer = this;
    color = Black;
    return Shape(*retval);
}

// this will get statically expanded for use by make above
Triangle::Triangle() {  }  // size and vptr knowledge are in here
