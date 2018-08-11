/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E R E C T . C                             //
//                                                            //
//         Code for class Rectangle                           //
//                                                            //
//************************************************************//

#include "erect.h"

// This file contains the implementation for
// Rectangle abstractions

ShapeRep *rectangle = 0;      // Rectangle exemplar

void
Rectangle::init() {
    // initializes global variables associated
    // with Rectangle support, allowing main to
    // initialize things in the proper order.
    // Some data structure initialization is done
    // the first time ShapeRep::gcCommon is called
    rectangle = new Rectangle(Exemplar(0));
}

Shape
Rectangle::make()
{
    // create a default rectangle
    Rectangle *retval = new Rectangle;
    retval->p1 = retval->p2 = Coordinate(0,0);
    retval->exemplarPointer = this;
    return *retval;
}

Shape
Rectangle::make(Coordinate pp1, Coordinate pp2)
{
    // create a rectangle at a specified place
    Rectangle *retval = new Rectangle;
    retval->p1 = pp1;
    retval->p2 = pp2;
    retval->exemplarPointer = this;
    return *retval;
}

void
Rectangle::draw() {
    int Sizeof = poolInitialized? poolInitialized:
        sizeof(Rectangle);
    printf("<Rectangle object %c>",
        'A' + (((char *)this-(char *)heap)/Sizeof));
}

void
Rectangle::move(Coordinate) {
    // . . .
}

void
Rectangle::rotate(double) {
    // . . .
}

//************************************************************//
//       M e m o r y    M a n a g e m e n t                   //
//************************************************************//

char *Rectangle::heap = 0;             // pool for operator new
size_t Rectangle::poolInitialized = 0; // size of a Rectangle

void
Rectangle::gc(size_t nbytes) {
    // do garbage collection on Rectangle instances
    printf("Rectangle::gc(%d) entered\n", nbytes);
    gcCommon(nbytes, poolInitialized, PoolSize, heap);
}

void *
Rectangle::operator new(size_t nbytes) {
    // dynamically create memory for a new Rectangle
    if (poolInitialized - nbytes) {
        gcCommon(nbytes, poolInitialized, PoolSize, heap);
        poolInitialized = nbytes;
    }
    Rectangle *tp = (Rectangle *)heap;
    // good coder would add memory exhaustion test here
    while (tp->inUse) {
        tp = (Rectangle*)(((char*)tp) + Round(nbytes));
    }
    tp->gcmark = 0;
    tp->inUse = 1;
    return (void*) tp;
}

void Rectangle::operator delete(void *) {
    // does nothing--see Rectangle::gc, above, instead
}

Rectangle::Rectangle() {
    // size and vptr knowledge are in here
}

Rectangle::Rectangle(const Rectangle& t) {
    // copy constructor
    p1 = t.p1;
    p2 = t.p2;
}

Rectangle::Rectangle(Exemplar e) : ShapeRep(e) {
    // constructor to build Exemplar only
}
