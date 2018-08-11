/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    eshaprp.c                                 //
//                                                            //
//         Code for class ShapeRep                            //
//                                                            //
//************************************************************//

// ShapeRep is the base class for all letter classes that
// use Shape as an envelope.  It is in the derived classes
// of ShapeRep where all the shape intelligence is

#include "eshaprp.h"
#ifndef _RECTANGLE_H
#include "erect.h"
#endif
#ifndef _TRIANGLE_H
#include "etringl.h"
#endif

// "constant" used as a degenerate return value
Shape *ShapeRep::aShape = 0;

// bits designating From space and To space for Baker's
// algorithm;  are flipped on every cycle
unsigned char ShapeRep::FromSpace = 0, ShapeRep::ToSpace = 1;

void ShapeRep::init() {
    // initializes class data structures
    aShape = new Shape;
}

void *
ShapeRep::operator new(size_t l) {
    // overridden in derived classes
    return ::operator new(l);
}

void
ShapeRep::operator delete(void *p) {
    // overridden in derived classes
    ::operator delete(p);
}

Thing *
ShapeRep::type() {
    // type of any derived class of
    // ShapeRep is kept in exemplarPointer
    return (Thingp)exemplarPointer;
}

Shape
ShapeRep::make() {
    // default ShapeRep manufacturer
    return *aShape;
}

Shape
ShapeRep::make(Coordinate c1, Thingp) {
    // one constraint: Point object
    return point->make(c1);
}

Shape
ShapeRep::make(Coordinate c1, Coordinate c2, Thingp type) {
    // exemplar constructor for Shape objects with two
    // constraints:  Lines and Rectangles
    return ((ShapeRep *)type)->make(c1, c2);
}

Shape
ShapeRep::make(Coordinate c1, Coordinate c2, Coordinate c3,
           Thingp type) {
    // exemplar constructor for Shape objects with three
    // constraints:  Triangles, Arcs, Parallelograms
    return ((ShapeRep*)type)->make(c1, c2, c3);
}

Shape
ShapeRep::make(Coordinate c1) {
    // make a Shape from one coordinate
    // default is to return a Point
    return make(c1, (Thingp)&point);
}

Shape
ShapeRep::make(Coordinate c1, Coordinate c2) {
    // make a Shape from two coordinates
    // default is to return a Rectangle
    return make(c1, c2, rectangle);
}

Shape
ShapeRep::make(Coordinate c1, Coordinate c2, Coordinate c3) {
    // make a Shape from three coordinates
    // default is to return a Triangle
    return make(c1, c2, c3, triangle);
}

void
ShapeRep::gcCommon(size_t nbytes, const size_t poolInitialized,
        const int PoolSize, Char_p &heap) {
    // Garbage collection common to all ShapeReps.  This
    // is where most of the "sweep" of the second half
    // of Baker's algorithm happens.  It is called by
    // the derived class gc routines, who call it
    // directly with appropriate parameters.

    // calculate s to be the size of the object.  If
    // nbytes is specified, use it:  it designates
    // a change in size (or is given at initialization
    // time to get things rolling).  Otherwise, use
    // the value saved in poolInitialized.
    size_t s = nbytes? nbytes: poolInitialized;

    // round up for alignment constraints
    size_t Sizeof = Round(s);

    // if a non-zero parameter was given, it is the size
    // of an object;  it indicates we are to discard the
    // old pool and allocate a new one.  This is done at
    // startup and after class update.
    if (nbytes) heap = new char[PoolSize * Sizeof];

    ShapeRep *tp = (ShapeRep *)heap;

    // sweep through the pool
    for (int i = 0; i < PoolSize; i++) {
        switch (nbytes) {
        case 0:   // normal garbage collection case
            // If still earmarked, but not checked off, and
            // in FromSpace, nuke it.
            if (tp->inUse) {
                if (tp->gcmark || tp->space != FromSpace) {
                    // don't sweep it away
                    tp->space = ToSpace;
                } else if (tp != tp->type()) {
                    // object needs to be reclaimed
                    tp->ShapeRep::~ShapeRep();
                    tp->inUse = 0;
                    printf("ShapeRep::gcCommon ");
                    printf("Reclaimed Shape object %c\n",
                     'A' + (((char *)tp-(char *)heap)/Sizeof));
                }
            }
            break;
        default:   // initialization of memory arena
            tp->inUse = 0;
            break;
        }
        tp->gcmark = 0;
        tp = (ShapeRep*)(Char_p(tp) + Sizeof);
    }
}

ShapeRep::ShapeRep(Exemplar) {
    // constructor to build ShapeRep's exemplar
    // (not very important)
    //
    // Recall that Exemplar is a dummy type used
    // to disambiguate this and the default constructor
    exemplarPointer = this;
    shape->Register(this);
}

void
ShapeRep::rotate(double) {
    // acts like pure virtual function
    printf("ShapeRep::rotate(double)\n");
}

void
ShapeRep::move(Coordinate) {
    // acts like pure virtual function
    printf("ShapeRep::move(Coordinate)\n");
}

void
ShapeRep::draw() {
    // acts like pure virtual function.  For now,
    // draw routines will just print the type's
    // name
    printf("<Shape>");
}

void
ShapeRep::erase() {
    // acts like pure virtual function
    printf("ShapeRep::erase()");
}

void
ShapeRep::gc(size_t) {
    // acts like pure virtual function
}

void
ShapeRep::mark() {
    // used by Shape in mark phase of Baker
    gcmark = 1;
}

ShapeRep::ShapeRep() {
    // default constructor
    exemplarPointer=this;
    gcmark=0;
    space=ToSpace;
    inUse=1;
}

ShapeRep::~ShapeRep() {
    // destructor does nothing
}
