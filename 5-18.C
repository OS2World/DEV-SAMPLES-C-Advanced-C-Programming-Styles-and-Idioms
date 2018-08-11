/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <complex.h>

typedef double time;

class SeriesRLCStepResponse {
public:
    virtual complex current(time t) { return object->current(t); };
    double frequency() const { return 1.0 / (L * C); }
    SeriesRLCStepResponse(double r, double l,
        double c, double initialCurrent, short isenvelope=1);
protected:
    double R, L, C, currentT0;
    double alpha;
    complex omegad, a1, b1, a2, b2, s1, s2;
private:
    SeriesRLCStepResponse *object;
};

class UnderDampedResponse: public SeriesRLCStepResponse {
public:
    UnderDampedResponse(double r, double l, double c, double i) :
	SeriesRLCStepResponse(r,l,c,i,0) { }
    complex current(time t) {
        return exp(-alpha * t) * (b1 * cos(omegad * t) +
               b2 * sin(omegad * t));
    }
};

class OverDampedResponse: public SeriesRLCStepResponse {
public:
    OverDampedResponse(double r, double l, double c, double i) :
	SeriesRLCStepResponse(r,l,c,i,0) { }
    complex current(time t) {
        return a1 * exp(s1 * t) + a2 * exp(s2 * t);
    }
};

class CriticallyDampedResponse: public SeriesRLCStepResponse {
public:
    CriticallyDampedResponse(double r, double l, double c, double i) :
	SeriesRLCStepResponse(r,l,c,i,0) { }
    complex criticallyDampedResponse(time t) {
        return exp(-alpha * t) * (a1 * t + a2);
    }
};

SeriesRLCStepResponse::SeriesRLCStepResponse(
        double r, double l, double c, double initialCurrent,
	short isenvelope) {
    R = r; L = l; C = c; currentT0 = initialCurrent;
    alpha = R / (L + L);
    // calculation of a1, b1, a2, b2, etc
    if (isenvelope) {
        if (alpha < frequency()) {
            object = new UnderDampedResponse(r, l, c, initialCurrent);
        } else if (alpha > frequency()) {
            object = new OverDampedResponse(r, l, c, initialCurrent);
        } else {
            object = new CriticallyDampedResponse(r, l, c, initialCurrent);
        }
    } else {
	    omegad = sqrt(frequency() * frequency() - alpha * alpha);
    }
}

int main() {
	SeriesRLCStepResponse afilter(0.0, 0.0, 0.0, 0.0);
	complex i10 = afilter.current(10.0);
}
