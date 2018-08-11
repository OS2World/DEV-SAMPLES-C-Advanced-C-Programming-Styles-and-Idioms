/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <String.h>

class Atom {
};

class NumericAtom: public Atom {
public:
	NumericAtom(): sum(0) { }
	NumericAtom(String &s) {
		sum = 0;
		for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
			sum = (sum*10) + s[i] - '0';
		}
		s = s(i, s.length()-i);
	}
	NumericAtom(const NumericAtom &n) { sum = n.value(); }
	~NumericAtom() { }
	long value() { return sum; }
	Atom *copy() {
		NumericAtom *retval = new NumericAtom;
		retval->sum = sum;
		return retval;
	}
private:
	long sum;
};

int main() {
	String p = "123";
	NumericAtom n = p;
}
