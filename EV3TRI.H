/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 3 T R I . H                           //
//                                                            //
//         Data structures for version 3 Triangle class       //
//                                                            //
//************************************************************//

#define _TRIANGLE_H
#ifndef _SHAPEREP_H
#include "eshaprp.h"
#endif
#ifndef _COORDINATE_H
#include "ecoord.h"
#endif

// This is the declaration of the NEW (Version 3) triangle
// class--it has a color attribute

class Triangle: public ShapeRep {
public:
    Shape make();
    Shape make(Coordinate, Coordinate, Coordinate);
    Triangle();
    void draw();
    void move(Coordinate);
    void rotate(double);
    void *operator new(size_t);
    void operator delete(void *);
    void gc(size_t = 0);
    Thing *cutover();
    Triangle(Exemplar);
    static void init();
private:
    static void poolInit(size_t);
    Shape make(Coordinate) { return *aShape; }
    Shape make(Coordinate, Coordinate) { return *aShape; }
    Coordinate p1, p2, p3;
    enum Color { Black, White } color;
private:
    static char *heap;
    static size_t poolInitialized;
    enum { PoolSize = 10 };
};

extern ShapeRep *triangle;
