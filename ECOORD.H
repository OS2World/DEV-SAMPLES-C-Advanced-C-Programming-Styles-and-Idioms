/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E C O O R D . H                           //
//                                                            //
//         Interface for struct Coordinate                    //
//                                                            //
//************************************************************//

#define _COORDINATE_H

// This is a simple public class that represents a Cartesian
// coordinate on the graphics screen

struct Coordinate {
    int x, y;
    Coordinate(int xx = 0, int yy = 0) { x = xx; y = yy; }
};
