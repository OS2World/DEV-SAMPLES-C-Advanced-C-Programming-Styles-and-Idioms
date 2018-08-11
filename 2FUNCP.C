/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class String {
public:
	int curColumn() { return 0; }
	int length() { return 0; }
	int hash() { return 0; }
};

class Stack {
public:
	char pop(int) { return 'a'; }
	void push(char) { }
};

class PathName:public String {
public:
	int error(int, const char * ...) { return 0; }
};

int  (String::*p1)() = String::length;
char (Stack::*p2)(int) = Stack::pop;
void (Stack::*p3)(char) = Stack::push;
int  (PathName::*p4)(int, const char* ...) = PathName::error;

int main() {
	String s;
	Stack t;
	PathName pn1, *pn2 = new PathName;

	int m = (s.*p1)();
	char c = (t.*p2)(2);
	(t.*p3)('a');
	(pn1.*p4)(1, "at line %d\n", __LINE__);
	(pn2->*p4)(3, "another error (%d) in file %s", __LINE__, __FILE__);
}
