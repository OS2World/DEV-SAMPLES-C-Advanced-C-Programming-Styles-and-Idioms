/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E T R I N G L . C                         //
//                                                            //
//         Interface for class Triangle                       //
//                                                            //
//************************************************************//

#include "etringl.h"

// class-specific variables
ShapeRep *triangle = 0;
char *Triangle::heap = 0;
size_t Triangle::poolInitialized = 0;

void
Triangle::init() {
    // initialize Triangle-specific statics and globals.
    // Some data structure initialization is done
    // the first time ShapeRep::gcCommon is called
    triangle = new Triangle(Exemplar(0));
}

Shape
Triangle::make()
{
    // make a default (degenerate) triangle
    Triangle *retval = new Triangle;
    retval->p1 = retval->p2 = retval->p3 = Coordinate(0,0);
    retval->exemplarPointer = this;
    return *retval;
}

Shape
Triangle::make(Coordinate pp1, Coordinate pp2, Coordinate pp3)
{
    // set up and return a new Triangle
    Triangle *retval = new Triangle;
    retval->p1 = pp1;
    retval->p2 = pp2;
    retval->p3 = pp3;
    retval->exemplarPointer = this;
    return *retval;
}

void
Triangle::gc(size_t nbytes) {
    // pass Triangle memory data structures to common
    // garbage collection (sweep) routine in base class
    gcCommon(nbytes, poolInitialized, PoolSize, heap);
}

void
Triangle::draw() {
    // for now, just print out a name corresponding
    // to the triangle's position in the pool
    int Sizeof = poolInitialized? poolInitialized:
        Round(sizeof(Triangle));
    printf("<Triangle object %c>",
        'A' + (((char *)this-(char *)heap)/Sizeof));
}

void
Triangle::move(Coordinate) {
    // . . .
}

void
Triangle::rotate(double) {
    // . . .
}

void *
Triangle::operator new(size_t nbytes) {
    // if pool has not yet been initialized, or if we just
    // updated the Triangle class, give garbage collector
    // control
    if (poolInitialized - nbytes) {
        gcCommon(nbytes, poolInitialized, PoolSize, heap);
        poolInitialized = nbytes;
    }

    // find a free one
    Triangle *tp = (Triangle *)heap;
    // need to add memory exhaustion test
    while (tp->inUse) {
        tp = (Triangle*)(((char*)tp) + Round(nbytes));
    }

    // initialize memory bits appropriately
    tp->gcmark = 0;
    tp->inUse = 1;
    return (void*) tp;
}

void Triangle::operator delete(void *) {
    // this should never be called, but C++ insists
    // on its being here if new is
}

Triangle::Triangle() { }  // size and vptr knowledge are in here

Triangle::Triangle(const Triangle& t) {
    // copy constructor
    p1 = t.p1;
    p2 = t.p2;
    p3 = t.p3;
}

Triangle::Triangle(Exemplar e) : ShapeRep(e) {
    // build a Triangle exemplar
}

Shape
Triangle::make(Coordinate) {
    // dummy function--should never be called
    return *aShape;
}

Shape
Triangle::make(Coordinate, Coordinate) {
    // dummy function--should never be called
    return *aShape;
}
