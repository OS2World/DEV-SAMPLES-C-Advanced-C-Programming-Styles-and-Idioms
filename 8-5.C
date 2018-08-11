/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Class {
public:
    virtual Class *make(const char*,EmployeeID);
    // . . . .
};

class Employee:  public Class {
public:
    Class *make(const char*, EmployeeID);
    // . . . .
};

Employee *employeeExemplar = new Employee(Exemplar());

class VicePresident: public Employee {
    // . . . .
};

class LineWorker:  public Employee {
    // . . . .
};

Class *
Employee::make(const char *name, EmployeeID id)
{
    Class *retval = 0;
    switch (id.firstChar()) {
    case 'M':    retval = new Manager(name, id);
                 break;
    case 'V':    retval = new VicePresident(name, id);
                 break;
    // . . . .
    }
    return retval;
}
