/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E R E C T . H                             //
//                                                            //
//         Interface for class Rectangle                      //
//                                                            //
//************************************************************//

#define _RECTANGLE_H
#ifndef _SHAPEREP_H
#include "eshaprp.h"
#endif
#ifndef _COORDINATE_H
#include "ecoord.h"
#endif

// This defines the interface to the Rectangle abstraction

class Rectangle: public ShapeRep {
public:
    // exemplar constructors
    Shape make();
    Shape make(Coordinate, Coordinate);

    // default constructor
    Rectangle();

    // Exemplar constructor
    Rectangle(Exemplar);
    void draw();

    // Things to do to Rectangles
    void move(Coordinate);
    void rotate(double);

    // memory management routines
    void *operator new(size_t);
    void operator delete(void *);
    void gc(size_t = 0);
    static void init();
private:
    // These should never be called on rectangles
    Shape make(Coordinate, Coordinate, Coordinate) {
        return *aShape;
    }
    Shape make(Coordinate) {
        return *aShape;
    }
    Coordinate p1, p2;
private:
    // Memory management data structures
    static char *heap;
    static size_t poolInitialized;
    enum { PoolSize = 5 };
};

// Rectangle exemplar pointer declaration
extern ShapeRep *rectangle;
