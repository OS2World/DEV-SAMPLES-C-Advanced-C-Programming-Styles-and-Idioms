/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class String {
    // . . . .
public:
    char operator[](int);
    int length();
    String operator()(int,int);
    String();
    String(const char *const);
    String operator+(const String&);
};

class Atom {
};

class NumericAtom: public Atom {
public:
	NumericAtom(): sum(0) { }
	NumericAtom(String &s) {
		sum = 0;
		for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
			sum = (sum*10) + s[i] - '0';
		}
		s = s(i, s.length()-i);
	}
	NumericAtom(const NumericAtom &n) { sum = n.value(); }
	~NumericAtom() { }
	long value() const { return sum; }
	Atom *copy() {
		NumericAtom *retval = new NumericAtom;
		retval->sum = sum;
		return retval;
	}
private:
	long sum;
};

class Name : public Atom {
public:
    Name(): n("") { }
    Name(String& s) { 
        for (int i=0; s[i] >= 'a' && s[i] <= 'z'; i++) {
            n = n + s(i,1);
        }
        s = s(i, s.length()-i);
    }
    Name(const Name& m) { n = m.name(); }
    ~Name() {}
    String name() const { return n; }
    Atom *copy() { Name *retval = new Name;
                   retval->n = n; return retval; }
private:
    String n;
};

class Punct : public Atom {
public:
    Punct(): c('\e0')      { }
    Punct(String& s)      { c = s[0]; s = s(1,s.length()-1); }
    Punct(const Punct& p) { c = char(p); }
    operator char() const { return c; }
    ~Punct() {}
    Atom *copy() { Punct *retval = new Punct;
                   retval->c = c;  return retval; }
private:
    char c;
};

class Oper : public Atom {
public:
    Oper(): c('\e0') { }
    Oper(String& s) { c = s[0]; s = s(1,s.length()-1); }
    Oper(Oper& o)   { c = char(o); }
    ~Oper() {}
    operator char() const { return c; }
    Atom *copy() { Oper *retval = new Oper;
                   retval->c = c; return retval; }
private:
    char c;
};
