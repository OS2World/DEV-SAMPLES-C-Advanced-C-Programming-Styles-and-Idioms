/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class FirstClass : public Letter {
public:
    FirstClass();
    ~FirstClass();
    Envelope make();
    Envelope make(double weight);
    // . . . .
};

class OverNight : public Letter {
public:
    OverNight();
    ~OverNight();
    Envelope make();
    Envelope make(double weight);
    double postage() { return 8.00; }
    // . . . .
};
