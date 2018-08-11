/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <math.h>
#include <stdio.h>

extern const double pi;

class Angle {
public:
    Angle(double degrees) {
        r = degrees * pi / 180.0;
    }
    void print() {
	printf("radians = %f\n", r);
    }
private:
    double r;
};
