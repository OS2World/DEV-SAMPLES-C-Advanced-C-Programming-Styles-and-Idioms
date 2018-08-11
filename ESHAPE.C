/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E S H A P E . C                           //
//                                                            //
//         Code for class Shape                               //
//                                                            //
//************************************************************//

#include "eshape.h"
#ifndef _SHAPEREP_H
#include "eshaprp.h"
#endif
#ifndef _TRIANGLE_H
#include "etringl.h"
#endif
#ifndef _RECTANGLE_H
#include "erect.h"
#endif
#include "List.h"

// Class Shape does much of the memory management work for
// all Shapes.

// Handles to all extant Shape instances everywhere
List<Topp> *Shape::allShapes = 0;

// List of all Exemplars that are made for subclasses
// of class ShapeRep
List<Thingp> *Shape::allShapeExemplars = 0;

// Shape exemplar
extern Shape *shape = 0;

void
Shape::init() {
    // initializes all global data structures for
    // Shapes, so main can orchestrate order of
    // initialization
    allShapes = new List<Topp>;
    allShapeExemplars = new List<Thingp>;
    shape = new Shape;

    // orchestrate initialization of ShapeRep types
    ShapeRep::init();
    Triangle::init();
    Rectangle::init();
}

Top *
Shape::doit() {
    // handy function that can be reloaded by users
    // and used as a utility
    return 0;
}

Shape::Shape() {
    // default shape constructor
    Topp tp = this;

    // log self in allShapes list
    allShapes->put(tp);

    // we don't know what kind of Shape:
    // just make it a dummy for now
    rep = new ShapeRep;
}

Shape::~Shape() {
    Listiter<Topp> tp = *allShapes;
    Topp t;
    for ( tp.reset(); tp.next(t); ) {
        if (t == (Thingp)this) {
            tp.remove_prev(t);
            break;
        }
    }
    if (allShapes->length() == 0) {
        // last gasp garbage collection
        gc();
    }
}

Shape::Shape(Shape &x) {
    // copy constructor
    Thingp tp = (Thingp) this;

    // log self with allShapes list
    allShapes->put(tp);

    // just point to parameter's rep
    rep = x.rep;
}

Shape::Shape(ShapeRep &x) {
    // build a Shape from a ShapeRep:  used
    // mainly to convert the ShapeReps built
    // by Triangle, Rectangle, etc., into
    // Shapes that are returned to the users
    // (users never see the inner classes)
    Topp tp = this;

    // log self with allShapes
    allShapes->put(tp);

    // note:  no ->ref();  caller must yield copy!
    rep = &x;
}

Shape&
Shape::operator=(Shape &x) {
    // assignment of shapes.  Don't worry about what
    // rep used to point to:  garbage collection
    // will get it.
    rep = x.rep;
    return *this;
}

Top *
Shape::type() {
    // A Shape's type is its own exemplar
    return shape;
}

void
Shape::dataUpdate(Thingp &oldExemplar,
                               const Thingp newExemplar) {
    // This function allows class replacement of a subclass
    // of ShapeRep.  It assumes that all virtual functions
    // have been recompiled and incrementally loaded
    // against the new class definition.  It also assumes
    // the programmer has provided a cutover function
    // which, when invoked on an old instance of the
    // shape, will return a pointer to a semantically
    // equivalent copy.

    ShapeRep* savedExemplar = (ShapeRep*) oldExemplar;
    Topp tp = 0;

    // get a static copy to iterate over;  we don't
    // want to catch new things as they are added!
    // The copy will be reclaimed on return from this
    // member function
    List<Topp> staticCopy = *allShapes;

    // change exemplars
    oldExemplar = newExemplar;

    // cut over all subobjects for this exemplar
    Listiter<Topp> shapeIter = staticCopy;
    for ( shapeIter.reset(); shapeIter.next(tp);  ) {
        Shapepointer sp = (Shapepointer)tp;
        if (sp->rep->type() == (Thingp)savedExemplar) {
            if (sp->rep->docutover()) {
                ShapeRep *oldrep = sp->rep;
                printf("\tchanging shape 0x%x to new format\n",
                    oldrep);
                sp->rep = (ShapeRep*)sp->rep->cutover();

                // must manually clean up old rep here:
                // garbage collector won't get it, as it's
                // about to go out of the arena
                oldrep->ShapeRep::~ShapeRep();
            }
        }
    }

    // Remove this exemplar from Shape's list of all exemplars
    // in the world--it is no longer participating as part
    // of this abstract base exemplar
    UnRegister(savedExemplar);
}

void
Shape::gc() {
    // Shape garbage collector: orchestrates collection
    // of unreachable objects for all subclasses of
    // ShapeRep.  Uses Baker's algorithm

    // First half of Baker:  mark all reachable shapes
    Listiter<Topp> shapeIter = *allShapes;
    shapeIter.reset();
    for ( Topp tp = 0; shapeIter.next(tp);  ) {
        Shapepointer sp = (Shapepointer)tp;
        if (sp->rep) {
            sp->rep->mark();
        }
    }        

    // Second half of Baker:  sweep.  Let individual
    // subtypes each do their own sweep of their own
    // pools, using their own gc member function.
    Listiter<Thingp> shapeExemplarIter = *allShapeExemplars;
    shapeExemplarIter.reset();
    for ( Thingp anExemplar = 0;
                shapeExemplarIter.next(anExemplar);  ) {
        ShapeRep *thisExemplar = (ShapeRep*)anExemplar;
        thisExemplar->gc(0);
    }

    // Baker swap of To and From spaces
    ShapeRep::FromSpace ^= 1;
    ShapeRep::ToSpace ^= 1;
}

void
Shape::Register(ShapeRep *s) {
    // routine by which ShapeRep exemplars
    // register themselves with Shape
    Thingp tp = s;
    allShapeExemplars->put(tp);
}

void
Shape::UnRegister(ShapeRep *s) {
    // Allows an exemplar to unregister itself
    // (as when it is replaced by a new version)
    Thingp tp = 0;
    Listiter<Thingp> shapeIter = *allShapeExemplars;
    for ( shapeIter.reset(); shapeIter.next(tp); ) {
        if (tp == (Thingp)s) {
            shapeIter.remove_prev(tp);
        }
    }
}
