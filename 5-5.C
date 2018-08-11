/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Number {          // base class
public:
    virtual void add(int);
    // . . . .
};

class BigNumber : public Number {    // derived class
public:
    void add(double);
    // . . . .
};

int main() {
    Number *a;
    BigNumber *b, bo;
    // . . . .
    a->add(1);             // Number::add(int)
    a->add(3.0);           // Number::add(int) with
                           //     coercion int(3.0)
    b->add(2);             // BigNumber::add(double) with
                           //     promotion double(2)
    b->add(2.0);           // BigNumber::add(double)
    b->Number::add(7.0);   // Number::add(int) with
                           //     coercion int(7.0)
    bo.add(8);             // BigNumber::add(double)
                           //     promotion double(8)
    bo.add(9.0);           // BigNumber::add(double)
    bo.Number::add(9);     // Number::add(int)
    bo.Number::add(10.0);  // Number::add(int) with
                           //     coercion int(10.0)
    return 0;
}
