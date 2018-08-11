/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E T R I . H                               //
//                                                            //
//         Interface for class Triangle                       //
//                                                            //
//************************************************************//

// This is the interface for the code implementing the
// semantics for the geometric shape, Triangle

#define _TRIANGLE_H
#ifndef _SHAPEREP_H
#include "eshaprp.h"
#endif
#ifndef _COORDINATE_H
#include "ecoord.h"
#endif

class Triangle: public ShapeRep {
public:
    // exemplar constructors
    Shape make();
    Shape make(Coordinate, Coordinate, Coordinate);

    // memory management
    void *operator new(size_t);
    void operator delete(void *);
    void gc(size_t = 0);

    // user application semantics
    void draw();
    void rotate(double);
    void move(Coordinate);

    // class routines
    Triangle(Exemplar);
    Triangle();
    static void init();
private:
    // these should never be called
    Shape make(Coordinate);
    Shape make(Coordinate, Coordinate);
private:
    // instance state variables
    Coordinate p1, p2, p3;
private:
    // memory management data
    static char *heap;
    static size_t poolInitialized;
    enum { PoolSize = 10 };
};

// Triangle exemplar pointer declaration
extern ShapeRep *triangle;
