/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 3 T R I M . C                         //
//                                                            //
//         Code for version 3 Triangle's move implementation  //
//                                                            //
//************************************************************//

#include "ev3tri.h"

void
Triangle::move(Coordinate)
{
    printf("version 3 Triangle::move of size %d\n",
        sizeof(*this));
}
