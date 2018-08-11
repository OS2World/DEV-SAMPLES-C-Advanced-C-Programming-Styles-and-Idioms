/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E V 3 T R I C . C                         //
//                                                            //
//         Cutover control code for version 3 Triangle code   //
//                                                            //
//************************************************************//

#include "ev3tri.h"
#include "Map.h"

// --------------------------------------------------------------

class v2Triangle: public ShapeRep {
public:
    Shape make();
    Shape make(Coordinate, Coordinate, Coordinate);
    v2Triangle();
    void move(Coordinate);
    void *operator new(size_t);
    void operator delete(void *);
    void gc(size_t = 0);
    void draw();
    v2Triangle(Exemplar);
    static void init();
private:
    friend Thing *Triangle::cutover();  // put in for conversion
    static void poolInit(size_t);
    Shape make(Coordinate) { return *aShape; }
    Shape make(Coordinate, Coordinate) { return *aShape; }
    Coordinate p1, p2, p3;
};

// --------------------------------------------------------------

// Use this map to keep track of all old objects we are
// asked to convert, and of the new ones they were converted to.
// That way, if we are asked to convert the same object
// several times, we map all requests onto the same return
// value.

Map<Thingp, Thingp> objectMap;

Thing *
Triangle::cutover() {
    // we are going to return a pointer to a converted triangle
    Triangle *retval = this;

    // instance passed in is really old triangle
    // the old triangle declaration is preserved
    // under the name v2Triangle;  class Triangle
    // is the version 3 one
    v2Triangle *old = (v2Triangle *)this;
    Thingp oldtp = this;
    ShapeRep *oldsr = (ShapeRep*)this;

    if (objectMap.element(oldtp)) {
        // if we've converted it already, don't
        // convert it again--just return old
        // converted value
        retval = (Triangle*)(objectMap[oldtp]);
    } else {
        // create a new (version 3) triangle to return
        // store it in several different kinds of pointers
        retval = new Triangle;
        ShapeRep *newsr = retval;
        Thingp newtp = retval;

        // copy over just the base class (ShapeRep) part
        *newsr = *oldsr;

        // now set up the fields of the new object
        retval->exemplarPointer = triangle;
        retval->p1 = old->p1;
        retval->p2 = old->p2;
        retval->p3 = old->p3;
        retval->color = Black;

        // save converted one for later
        objectMap[oldtp] = newtp;
    }
    return retval;
}

Triangle::Triangle() { }
