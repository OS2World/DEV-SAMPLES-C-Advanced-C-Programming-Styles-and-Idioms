/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>
#include <math.h>

class Complex {
friend Imaginary;
public:
    Complex(double r = 0, double i = 0): rpart(r), ipart(i) { }
    Complex(const Complex &c): rpart(c.rpart), ipart(c.ipart) { }
    Complex& operator=(const Complex &c) {
        rpart = c.rpart; ipart = c.ipart; return *this;
    }
    Complex operator+(const Complex &c) const {
        return Complex(rpart + c.rpart, ipart + c.ipart);
    }
    friend Complex operator+(double d, const Complex &c) {
        return c + Complex(d);
    }
    friend Complex operator+(int i, const Complex &c) {
        return c + Complex(i);
    }
    Complex operator-(const Complex &c1) const {
        return Complex(rpart - c1.rpart, ipart - c1.ipart);
    }
    friend Complex operator-(double d, const Complex &c) {
        return -c + Complex(d);
    }
    friend Complex operator-(int i, const Complex &c) {
        return -c + Complex(i);
    }
    Complex operator*(const Complex &c) const {
        return Complex (rpart*c.rpart - ipart*c.ipart,
                   rpart*c.ipart + c.rpart*ipart);
    }
    friend Complex operator*(double d, const Complex& c) {
        return c * Complex(d);
    }
    friend Complex operator*(int i, const Complex& c) {
        return c * Complex(i);
    }
    friend ostream& operator<<(ostream &o, const Complex& c) {
	o << "(" << c.rpart << "," << c.ipart << ")"; return o;
    }
    Complex operator/(const Complex &c) const { return 0; }
    operator double() {
        return ::sqrt(rpart*rpart + ipart*ipart);
    }
    Complex operator-() const { return Complex(-rpart, -ipart); }
private:
    double rpart, ipart;
};

class Imaginary: public Complex {
public:
    Imaginary(double i = 0): Complex(0, i) { }
    Imaginary(const Complex &c): Complex(0, c.ipart) { }
    Imaginary& operator=(const Complex &c) {
        rpart = 0; ipart = c.ipart; return *this;
    }
};

int main() {
	Complex c = 5;
	Complex d = Complex(2,-7.0);
	Complex e = d + c;
	cout << e << " = " << d << " + " << c << endl;
	d = c;
	Imaginary i(10);
	cout << "i = " << i << endl;
	Imaginary j = e;
	cout << "j = " << j << endl;
	Imaginary imaginary2 = 2;
	Complex f = Complex(1,2);
	Complex sum = f - imaginary2;
	cout << sum << " = " << f << " - " << imaginary2 << endl;
	cout << "2 * Complex(1,2) = " << 2 * Complex(1,2) << endl;
}
