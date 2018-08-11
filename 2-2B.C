/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

const int STACK_SIZE = 10;

class Stack {
private:
    long items[STACK_SIZE];
    int sp;
public:
    void initialize();
    long top() const;
    long pop();
    void push(long);
};

void Stack::initialize() {
 sp = -1;
}

long Stack::top() const {
    return items[sp];
}

long Stack::pop() {
    return items[sp--];
}

void Stack::push(long i) {
    items[++sp] = i;
}

int main()
{
    Stack q;
    q.initialize();
    q.push(1);
    int i = q.top();
    q.pop();
}
