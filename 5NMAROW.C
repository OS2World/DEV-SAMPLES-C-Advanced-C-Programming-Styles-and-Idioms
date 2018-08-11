/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>
#include <stdio.h>

struct BaseConstructor { BaseConstructor(int) { } };

class NumberRep;

class Number {
public:
    Number(BaseConstructor);
    Number();
    Number(double d);
    Number(double rpart, double ipart);
    Number operator=(Number &);
    void redefine(NumberRep *);
    Number(Number &);
    NumberRep *operator->();
private:
    NumberRep *rep;
};

class NumberRep {
public:
    virtual Number operator+(Number &);
    virtual Number complexAdd(NumberRep &);
    virtual Number doubleAdd(NumberRep &);
    virtual ostream &operator<<(ostream &o) { return o; }
    NumberRep(): referenceCount(0) { }
    short referenceCount;
};

Number
NumberRep::operator+(Number &) { static Number n;  return n; }

Number
NumberRep::complexAdd(NumberRep &) { static Number n; return n; }

Number
NumberRep::doubleAdd(NumberRep &) { static Number n; return n; }

NumberRep *
Number::operator->() { return rep; }

Number
Number::operator=(Number & n) {
        n.rep->referenceCount++;
        if (--rep->referenceCount == 0) delete rep;
        rep = n.rep;
        return *this;
}
void
Number::redefine(NumberRep *n) {
        if (--rep->referenceCount == 0) delete rep;
        rep = n;
}
Number::Number(Number & n) {
        n.rep->referenceCount++;
        rep = n.rep;
}

class Complex: public NumberRep {
friend class RealNumber;
public:
    Complex(double d, double e): NumberRep() {
        rpart = d; ipart = e;
        referenceCount = 1;
    }
    Number operator+(Number &num) {
        Number n = num->complexAdd(*this);
        return n;
    }
    Number complexAdd(NumberRep &n);
    Number doubleAdd(NumberRep &n);
    ostream& operator<<(ostream& o) {
        o << "Complex(" << rpart << "," << ipart << ")";
        return o;
    }
private:
    double rpart, ipart;
};

class RealNumber: public NumberRep {
friend Complex;
public:
    RealNumber(double d): NumberRep() {
        r = d;
        referenceCount = 1;
    }
    Number operator+(Number &num) {
        Number newnum = num->doubleAdd(*this);
        return newnum;
    }
    Number complexAdd(NumberRep &n);
    Number doubleAdd(NumberRep &n) {
        Number retval;
        RealNumber *c1 = new RealNumber(*this);
        RealNumber *c2 = (RealNumber*)&n;
        c1->r += c2->r;
        retval.redefine(c1);
        return retval;
    }
    ostream& operator<<(ostream& o) {
        o << "Float(" << r << ")";
        return o;
    }
private:
    double r;
};

ostream& operator<<(ostream&o, Number &n) {
    return n->operator<<(o);
}

Number::Number(BaseConstructor) {
}

Number::Number() {
    rep = new RealNumber(0.0);
}

Number::Number(double d) {
    rep = new RealNumber(d);
}

Number::Number(double d, double e) {
    rep = new Complex(d, e);
}

Number Complex::complexAdd(NumberRep &n) {
    Number retval;
    Complex *c1 = new Complex(*this);
    Complex *c2 = (Complex*)&n;
    c1->rpart += c2->rpart;
    c1->ipart += c2->ipart;
    retval.redefine(c1);
    return retval;
}

Number Complex::doubleAdd(NumberRep &n) {
    Number retval;
    Complex *c1 = new Complex(*this);
    RealNumber *c2 = (RealNumber*)&n;
    c1->rpart += c2->r;
    retval.redefine(c1);
    return retval;
}

Number RealNumber::complexAdd(NumberRep &n) {
    Number retval;
    Complex *c1 = new Complex(r, 0);
    Complex *c2 = (Complex*)&n;
    c1->rpart += c2->rpart;
    c1->ipart += c2->ipart;
    retval.redefine(c1);
    return retval;
}

int main() {
    Number a = Number(1.0, 1.0);
    Number b = 2.0;
    Number c = a->operator+(b);
    cout << "a = " << a << ", b = " << b << ", c = " << c << "\n";
}
