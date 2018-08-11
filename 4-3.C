/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>

void f(int j) { cout << "::f(int)" << endl; }

class A {
public:
	void f(int) { cout << "A::f(int)" << endl; }
};

class B: public A {
public:
	void f(double) { cout << "B::f(double)" << endl; }
	void g(int);
};

void B::g(int k) {
	f(k);
	A::f(k);
	this->A::f(k);
	::f(k);
	f(6);
	::f(5);
}

int main() {
	A *a = new A;
	B *b = new B;

	a->f(1);
	a->f(3.0);
	b->f(2);
	b->f(2.0);
	b->A::f(7.0);
	b->g(10);
}
