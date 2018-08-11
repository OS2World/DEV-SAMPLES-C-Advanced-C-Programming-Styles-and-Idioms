/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>

class Complex {
public:
	int operator<(const Complex&);
};

ostream& operator<<(ostream&, const Complex&);
istream& operator>>(istream&, const Complex&);

template <class S>
void sort(S elements[], const int nelements) {
    int flip = 0, sz = nelements - 1;
    do {
        for (int j = 0, flip = 0; j < sz; j++) {
            if (elements[j] < elements[j+1]) {
                S t = elements[j+1];
                elements[j+1] = elements[j];
                elements[j] = t;
                flip++;
            }
        }
    } while (flip);
}

int main() {
    Complex cvec[12];
    for (int i = 0; i < 12; i++) cin >> cvec[i];
    sort(cvec, 12);    // calls sort(Complex[], const int)
    for (i = 0; i < 12; i++) cout << cvec[i] << endl;
    return 0;
}
