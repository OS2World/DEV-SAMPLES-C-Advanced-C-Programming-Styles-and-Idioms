/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

int
Thing::docutover() {
    if (!updateCountVal) {
        updateCountVal = refCountVal;
    }
    return !--updateCountVal;
}

typedef Thing *Thingp;

void
Shape::dataUpdate(Thingp &oldExemplar,
                   const Thingp newExemplar) {
    Thing *saveRep;
    Shape *sp;
    for (Listiter<Shape*> p = allShapes;
        p.next(sp);  p++) {
        if (sp->rep->type() == &oldExemplar) {
	    if (p->rep->docutover()) {
                saveRep = sp->rep;
                sp->rep = (ShapeRep*)sp->rep->cutover();
                delete saveRep;
            }
        }
    }
    saveRep = oldExemplar;
    oldExemplar = newExemplar;
    delete saveRep;
}
