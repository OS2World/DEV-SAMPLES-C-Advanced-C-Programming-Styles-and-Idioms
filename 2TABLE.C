/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>
#include <string.h>

class Table {
public:
	void sort() { cout << "sorted \"" << nameV << "\"\n"; }
	Table(const char *name1, const char *name2) {
		nameV = new char[strlen(name1)+strlen(name2)+1];
		strcpy(nameV, name1);
		strcpy(nameV+strlen(name1), name2);
	}
private:
	char *nameV;
};

class X {
public:
	Table t1, t2;
	X(const char*name): t1(name, ":X::t1"), t2(name, ":X::t2") { }
};

int main() {
	Table X::*tablePointer = &X::t1;
	X a = "a", *b = new X("b");
	(a.*tablePointer).sort();
	(b->*tablePointer).sort();
	tablePointer = &X::t2;
	(a.*tablePointer).sort();
	(b->*tablePointer).sort();
}
