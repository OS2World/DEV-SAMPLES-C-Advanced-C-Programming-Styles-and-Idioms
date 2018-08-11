/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 2 T R I . H                           //
//                                                            //
//         Modified interface for class Triangle (Version 2)  //
//                                                            //
//************************************************************//

#define _TRIANGLE_H
#ifndef _SHAPEREP_H
#include "eshaprp.h"
#endif
#ifndef _COORDINATE_H
#include "ecoord.h"
#endif

class Triangle: public ShapeRep {
public:
    // Just like Triangle.h, except set up for a
    // new definition of Triangle::move
    Shape make();
    Shape make(Coordinate, Coordinate, Coordinate);
    Triangle();
    void draw();
    void move(Coordinate);
    void rotate(double);
    void *operator new(size_t);
    void operator delete(void *);
    void gc(size_t = 0);
    Triangle(Exemplar);
    static void init();
private:
    static void poolInit(size_t);
    Shape make(Coordinate) { return *aShape; }
    Shape make(Coordinate, Coordinate) { return *aShape; }
    Coordinate p1, p2, p3;
private:
    static char *heap;
    static size_t poolInitialized;
    enum { PoolSize = 10 };
};

extern ShapeRep *triangle;
