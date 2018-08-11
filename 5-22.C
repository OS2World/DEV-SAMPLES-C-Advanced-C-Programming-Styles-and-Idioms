/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

Value *
BPF::evaluate(Value *input = 0) {
    Value *f = cachedInput->evaluate(input);
    if (f->f1() > f1() && f->f1() < f2()) return f;
    else return zero;
}

Value *
BPF::operator()(Value* f) {
    switch(f->type()) {
    case T_LPF:
        if (f->f1() > f2()) return this;
        else return new BPF(f1(), f->f1());
    case T_HPF:
        if (f->f1() < f1()) return this;
        else return new BPF(f->f1(), f2());
    case T_BPF:
        Frequency lowfreq = f->f1();
        Frequency highfreq = ((Filter*)f)->f2();
        if (f1() > lowfreq) lowfreq = f1();
        if (f2() < highfreq) highfreq = f2();
        return new BPF(lowfreq, highfreq);
    case T_Notch:
        cachedInput = f;
        return this;
    case T_Data:
        myType = T_Data;
        cachedInput = f;
        return evaluate();
    }
}
