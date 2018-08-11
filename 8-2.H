/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Class {
};

typedef long Hours;
typedef long Dollars;
typedef long Days;

class String {
public:
	String();
        String(const char*);
};

class EmployeeId {
public:
    EmployeeId(long);
    EmployeeId();
};

class Exemplar { Exemplar(); };

class Employee: public Class {
public:
    Employee(Exemplar /* unused */) { }

    // the make() functions take the place of constructors
    Class *make() { return new Employee; }
    Class *make(const char *name, EmployeeId id) {
        return new Employee(name, id);
    }
    long printPaycheck();
    void logTimeWorked(Hours);
private:
    // note that constructors are private, meaning that
    // ordinary instances of this class cannot be created
    Employee(): salary(0), vacationAllotted(0),
        vacationUsed(0), name(""), id(0) { }
    Employee(const char *emp_name, EmployeeId emp_id):
        salary(0), vacationAllotted(0), vacationUsed(0)
        {
            name = emp_name;  id = emp_id;
        }
    Dollars salary;
    Days vacationAllotted, vacationUsed;
    String name;
    EmployeeId id;
};

// This variable serves as the globally known handle
// to the Employee exemplar object
extern Class *employee;
