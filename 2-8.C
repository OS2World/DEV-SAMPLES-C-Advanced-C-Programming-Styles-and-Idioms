/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <complex.h>

typedef double time;

class SeriesRLCStepResponse {
public:
    complex (SeriesRLCStepResponse::*current)(time t);
    SeriesRLCStepResponse(double r, double l,
        double c, double initialCurrent);
    double frequency() const { return 1.0 / sqrt(L * C); }
private:
    complex underDampedResponse(time t) {
        return exp(-alpha * t) * (b1 * cos(omegad * t) +
               b2 * sin(omegad * t));
    }
    complex overDampedResponse(time t) {
        return a1 * exp(s1 * t) + a2 * exp(s2 * t);
    }
    complex criticallyDampedResponse(time t) {
        return exp(-alpha * t) * (a1 * t + a2);
    }
    double R, L, C, currentT0, alpha;
    complex omegad, a1, b1, a2, b2, s1, s2;
};
