/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Stack {
public:
	Stack() { }
	~Stack() { }
	int pop() { return 1; }
	void push(int) { }
};

class CountedStack {
public:
    CountedStack(): rep(new CountedStackRep) { }
    int pop() { return rep->rep->pop(); }
    void push(int i) { rep->rep->push(i); }
    CountedStack(const CountedStack &c) {
	rep = c.rep;
	rep->count++;
    }
    CountedStack(const Stack &c) {
	rep = new CountedStackRep(new Stack(c));
    }
    operator Stack() { return *(rep->rep); }
    ~CountedStack() {
	if (--rep->count <= 0) delete rep;
    }
    CountedStack &operator=(const CountedStack &c) {
	c.rep->count++;
	if (--rep->count <= 0) delete rep;
	rep = c.rep;
	return *this;
    }
private:
    struct CountedStackRep {
	int count;
	Stack *rep;
	CountedStackRep(Stack *s = 0) {
	    rep = s? s: new Stack; count = 1;
	}
    } *rep;
};

int main() {
    CountedStack a, b;
    Stack s, t;
    a = b;
    b = s;
    t = b;
}
