/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "5-20.c"

class Filter: public Value {
public:
    Filter(Frequency w1, Frequency w2 = 0):
        Value(0, w1), omega2(w2), cachedInput(0) {
    }
    virtual Value *evaluate(Value* = 0) = 0;
    virtual Value *operator()(Value*) = 0;
    virtual void print() = 0;
    Frequency f2() { return omega2; }
    Type type() {
        if (cachedInput) return cachedInput->type();
        else return baseType;
    }
protected:
    Type myType, baseType;
    Value *cachedInput;
private:
    Frequency omega2;
};
