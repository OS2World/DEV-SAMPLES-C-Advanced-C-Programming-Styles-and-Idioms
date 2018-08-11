/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class TaxFormFramework {
public:
    TaxFormFramework(int numberOfLines) {
        . . . .
    }
    void draw() {
        makeField(loc1, taxpayer.name());
        makeField(loc2, taxpayer.ssn());
        . . . .
        addFields();
    }
private:
    void makeField(Point, const char *const);
    // derived class must have its own version of addFields
    virtual void addFields() = 0;
    Point loc1, loc2, . . . .
    . . . .
};

class ScheduleB: public TaxFormFramework {
public:
    ScheduleB(): TaxFormFramework(14) { }
private:
    Point locA, . . . .
    void addFields() {
        // add the lines for Schedule B
        makeField(locA, mortgage.income());
        makeField(locB, other.income());
        . . . .
    }
    . . . .
};
