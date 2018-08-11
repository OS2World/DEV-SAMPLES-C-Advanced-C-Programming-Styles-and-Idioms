/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stdlib.h>
#include <string.h>

class ParseTree {
    // . . . .
};

class Node {
    // . . . .
public:
    Node *leftChild() const, * rightChild() const;
    const char * const contents() const;
};

class String {
public:
    String operator+(const String &s) const;
    String();
    String(const String& s);
    String(const char *s);
    String operator=(const String& q);
    ~String();
    operator ParseTree() { /* . . . . */ }
    String(Node);
    int length();
private:
    String nodeWalk(const Node*);
    char *p;
};


String
String::nodeWalk(const Node *n) {      // infix node walk
    if (n == 0) return "";
    String retval = String("(") + nodeWalk(n->leftChild());
    retval = retval + " " + n->contents();
    retval = retval + " " + nodeWalk(n->rightChild()) + ")";
}

String::String(Node n)
{
    String temp = nodeWalk(&n);
    p = new char[temp.length() + 1];
    ::strcpy(p, temp.p);
}
