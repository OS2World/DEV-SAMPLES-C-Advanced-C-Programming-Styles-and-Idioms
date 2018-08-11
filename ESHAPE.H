/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E S H A P E . H                           //
//                                                            //
//         Interface for class Shape                          //
//                                                            //
//************************************************************//

// Class Shape is the user interface to the entire graphics
// package--all other classes are just used for internal
// implementation

#ifndef _SHAPE_H
#define _SHAPE_H
#include "ek.h"
#endif
#include "List.h"

// forward reference declaration
class ShapeRep;

class Shape: public Top {    // Top defined in k.h
public:
    // forwards all operations to rep
    ShapeRep *operator->() const {
        return rep;
    }

    // constructors and orthodox canonical form
    Shape();
    Shape(ShapeRep&);
    ~Shape();
    Shape(Shape& x);
    Shape& operator=(Shape& x);

    // yield type of letter object
    Top *type();
    // replace one exemplar with a new version,
    // updating its instances using the user-
    // provided cutover function
    void dataUpdate(Thingp&, const Thingp);

    // general purpose function that can be loaded
    // by a user to do whatever they want
    Top *doit();

    // garbage collector for Shape empire
    void gc();

    // routines for exemplars to register and
    // unregister themselves with Shape
    void Register(ShapeRep*);
    void UnRegister(ShapeRep*);

    // initializes class variables
    static void init();    // class initialization
private:
    friend ShapeRep;
    // operator new is called only from ShapeRep.
    // operator delete is unused
    static void *operator new(size_t s) {
        return ::operator new(s);
    }
    static void operator delete(void *) { }

    // keep a list of all instances of myself
    static List<Topp> *allShapes;

    // keep a list of all exemplars of things
    // derived from ShapeRep
    static List<Thingp> *allShapeExemplars;

    // pointer to the business end of an actual Shape
    ShapeRep *rep;
};

typedef Shape *Shapepointer;

// pointer to the Shape exemplar, dynamically
// created by Shape::init
extern Shape *shape;         // exemplar

class Point: public Shape {
public:
    // . . . .
    ShapeRep *operator->() const;
    Point();
    ~Point();
} point;

// users shouldn't have to know about, or include,
// the header file for ShapeRep

#ifndef _SHAPEREP_H
#include "eshaprp.h"
#endif
