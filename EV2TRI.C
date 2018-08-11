/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 2 T R I . C                           //
//                                                            //
//         Modified code for class Triangle (Version 2)       //
//                                                            //
//************************************************************//

#include "ev2tri.h"

void
Triangle::move(Coordinate)
{
    printf("version 2 Triangle::move of size %d\n",
        sizeof(*this));
}
