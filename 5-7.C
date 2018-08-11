/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>
#include <stdio.h>

struct BaseConstructor { BaseConstructor(int=0) { } };

class Number {
public:
    Number(BaseConstructor);
    Number();
    Number(double d);
    Number(double rpart, double ipart);
    Number operator=(Number & n) {
	printf("Number::operator=(Number&)\n");
        n.rep->referenceCount++;
        if (--rep->referenceCount == 0) delete rep;
        rep = n.rep;
        return *this;
    }
    void redefine(Number *n) {
	printf("Number::redefine(Number*)\n");
        if (--rep->referenceCount == 0) delete rep;
        rep = n;
    }
    Number(Number & n) {
	printf("Number::Number(Number&)\n");
        n.rep->referenceCount++;
        rep = n.rep;
    }
    virtual ostream& operator<<(ostream &s) {
	printf("Number::operator<<(ostream&)\n");
        return rep->operator<<(s);
    }
    virtual Number operator+(Number &n) {
	printf("Number::operator+(Number&)\n");
        return rep->operator+(n);
    }
    virtual Number complexAdd(Number &n) {
	printf("Number::complexAdd(Number&)\n");
        return rep->complexAdd(n);
    }
    virtual Number doubleAdd(Number &n) {
	printf("Number::doubleAdd(Number&)\n");
        return rep->doubleAdd(n);
    }
private:
    union {
        Number *rep;
        short referenceCount;
    };
};

class Complex: public Number {
friend class RealNumber;
public:
    Complex(double d, double e): Number(BaseConstructor()) {
	printf("Complex::Complex(double, double)\n");
        rpart = d; ipart = e;
    }
    Number operator+(Number &num) {
	printf("Complex::operator+(Number&)\n");
        Number n = num.complexAdd(*this);
        return n;
    }
    Number complexAdd(Number &n);
    Number doubleAdd(Number &n);
    ostream& operator<<(ostream& o) {
        o << "Complex(" << rpart << "," << ipart << ")";
        return o;
    }
private:
    double rpart, ipart;
};

class RealNumber: public Number {
friend Complex;
public:
    RealNumber(double d): Number(BaseConstructor()) {
	printf("RealNumber::RealNumber(double)\n");
        r = d;
    }
    Number operator+(Number &num) {
	printf("RealNumber::operator+(Number&)\n");
        Number newnum = num.doubleAdd(*this);
        return newnum;
    }
    Number complexAdd(Number &n);
    Number doubleAdd(Number &n) {
	printf("RealNumber::doubleAdd(Number&)\n");
        Number retval;
        RealNumber *c1 = new RealNumber(*this);
        RealNumber *c2 = (RealNumber*)&n;
        c1->r += c2->r;
        retval.redefine(c1);
        return retval;
    }
    ostream& operator<<(ostream& o) {
	printf("RealNumber::operator<<(ostream&)\n");
        o << "Float(" << r << ")";
        return o;
    }
private:
    double r;
};

ostream& operator<<(ostream&o, Number n) {
    Number *np = &n;
    return np->operator<<(o);
}

Number::Number(BaseConstructor) {
    printf("Number::Number(BaseConstructor)\n");
    referenceCount = 1;
}

Number::Number() {
    printf("Number::Number()\n");
    rep = new RealNumber(0.0);
}

Number::Number(double d) {
    printf("Number::Number(double)\n");
    rep = new RealNumber(d);
}

Number::Number(double d, double e) {
    printf("Number::Number(double,double)\n");
    rep = new Complex(d, e);
}

Number Complex::complexAdd(Number &n) {
    printf("Number::complexAdd(Number&)\n");
    Number retval;
    Complex *c1 = new Complex(*this);
    Complex *c2 = (Complex*)&n;
    c1->rpart += c2->rpart;
    c1->ipart += c2->ipart;
    retval.redefine(c1);
    return retval;
}

Number Complex::doubleAdd(Number &n) {
    printf("Complex::doubleAdd(Number&)\n");
    Number retval;
    Complex *c1 = new Complex(*this);
    RealNumber *c2 = (RealNumber*)&n;
    c1->rpart += c2->r;
    retval.redefine(c1);
    return retval;
}

Number RealNumber::complexAdd(Number &n) {
    printf("RealNumber::complexAdd(Number&)\n");
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
    Number c = a + b;
    cout << "a = " << a << ", b = " << b << ", c = " << c << "\n";
}
