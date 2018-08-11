/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Employee: public Class {
public:
    Employee(Exemplar);
    Employee *make();
    Employee *make(const char *name, EmployeeId id);
    long printPaycheck();
    void logTimeWorked(Hours);
protected:
    Employee();
    Employee(const char *name, EmployeeId id);
private:
    Dollars salary;
    Days vacationAllotted, vacationUsed;
    String name;
    EmployeeId id;
};
