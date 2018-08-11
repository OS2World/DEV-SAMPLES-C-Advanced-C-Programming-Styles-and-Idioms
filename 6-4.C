/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Name { public: Name(const char *); /* . . . . */ };

class Employee {
public:
    virtual char *name();
    Employee(Name);
private:
    // . . . .
};

class Manager: public Employee {
public:
    Manager(Name n): Employee(n) { }
protected:
    class Secretary: public Employee {
    public:
        Secretary(Name n) : Employee(n) { }
        char *name();
    };
};

class VicePresident: public Manager {
public:
    VicePresident(Name me, Name Asst, Name sec1, Name sec2);
private:
    Secretary SEC1obj, SEC2obj;
    class AdminAsst: public Employee {
        // . . . .
    } AsstObj;
};

class DeptHead: public Manager {
public:
    DeptHead(Name me, Name secy): Manager(me), SECobj(secy) { }
private:
    Secretary SECobj;
};

VicePresident::VicePresident(Name me, Name Asst, Name sec1, Name sec2):
        Manager(me), SEC1obj(sec1), SEC2obj(sec2),
        AsstObj(Asst) { }

Manager::Secretary Sam("Sam");
VicePresident Pat("Pat", "Terry", "Jean", "Marion");
DeptHead Jo("Jo", "Chris");
