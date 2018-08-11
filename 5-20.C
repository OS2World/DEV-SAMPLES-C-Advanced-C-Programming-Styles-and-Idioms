/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>

typedef double Frequency;
typedef double Voltage;

class Value {
public:
    enum Type { T_LPF, T_HPF, T_BPF, T_Notch, T_Data };
    virtual Type type() { return T_Data; }
    virtual Frequency f1() { return omega1; }
    virtual void print() {
        cout << "Value " << volts << " volts at frequency " <<
            omega1 << endl;
    }
    virtual Value *evaluate(Value* = 0) {
        return this;
    }
    Value(Voltage v=0, Frequency w1=0): volts(v), omega1(w1) {
    }
private:
    Frequency omega1;
    Voltage volts;
};

Value Zero(0);

Value *zero = &Zero;
