/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

void
ShapeRep::gcCommon(size_t nbytes, const size_t poolInitialized,
        const int PoolSize, Char_p &heap) {
    size_t s = nbytes? nbytes: poolInitialized;
    size_t Sizeof = Round(s);
    ShapeRep *tp = (ShapeRep *)heap;
    for (int i = 0; i < PoolSize; i++) {
        switch (nbytes) {
        case 0:   // normal garbage collection case
            if (tp->inUse) {
                if (tp->gcmark || tp->space != FromSpace) {
                    // don't sweep it away
                    tp->space = ToSpace;
                } else if (tp != tp->type()) {
                    // object needs to be reclaimed
                    tp->ShapeRep::~ShapeRep();
                    tp->inUse = 0;
                    printf("ShapeRep::gcCommon ");
                    printf("Reclaimed Triangle object %c\n",
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
