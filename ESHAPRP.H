/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E S H A P R P . H                         //
//                                                            //
//         Interface for class ShapeRep.                      //
//                                                            //
//************************************************************//

#define _SHAPEREP_H
#ifndef _SHAPE_H
#include "eshape.h"
#endif
#ifndef _COORDINATE_H
#include "ecoord.h"
#endif

class ShapeRep: public Thing {
public:
    /* all user-defined operators go here.  Note that, because
     * of the use of operator->, this signature does not have
     * to be mimicked in the Shape class.  However, the Shape's
     * rep field has to be appropriately typed.  Assignment
     * operators do not go here, but in the Shape class.
     *
     * return_type should either be a primitive
     * type, or of type Shape, of type Shape&, or
     * a concrete data type
     */
    virtual void rotate(double);
    virtual void move(Coordinate);
    virtual void draw();
    virtual void erase();

    // constructors
    Shape make(Coordinate,Thingp);
    Shape make(Coordinate,Coordinate,Thingp);
    Shape make(Coordinate,Coordinate,Coordinate,Thingp);

    // these are overridden in the derived classes;
    // their default action is to call the ones above,
    // with Thingp suitably defaulted
    virtual Shape make();
    virtual Shape make(Coordinate);
    virtual Shape make(Coordinate,Coordinate);
    virtual Shape make(Coordinate,Coordinate,Coordinate);

    // routine to mark this object as used for the
    // Baker algorithm
    virtual void mark();

    // type returns a pointer to an object's exemplar
    Thing *type();

    // Do garbage collection.  If the argument is zero,
    // sweep the current pool;  if non-zero, build a
    // new pool to hold objects of the designated size,
    // and forget about the old pool
    virtual void gc(size_t = 0);

    // class constructors
    ShapeRep();
    ~ShapeRep();
    ShapeRep(Exemplar);

    // used to orchestrate order of initialization of
    // static, class-specific information
    static void init();
protected:
    friend class Shape;
    Coordinate center;

    // this is the "type field"
    Top *exemplarPointer;

    // memory management state variables:  Space
    // is FromSpace or ToSpace; gcmark is the mark
    // bit for marking objects under Baker;  inUse
    // means that this object has been returned to
    // a caller for use, but that it hasn't yet been
    // reclaimed by the garbage collector
    unsigned char space:1, gcmark:1, inUse:1;
protected:
    // do common processing for (the sweep phase of)
    // Baker garbage collection
    static void gcCommon(size_t nbytes,
        const size_t poolInitialized,
        const int PoolSize, Char_p &h);

    // These two "constants" designate From space and
    // To space for the Baker algorithm.  They are flipped
    // every garbage collection cycle
    static unsigned char FromSpace, ToSpace;

    // general memory management operators, which use the
    // pool operated on by gc
    static void *operator new(size_t);
    static void operator delete(void *);

    // a typeless shape usable as a default return value
    static Shape *aShape;
};
