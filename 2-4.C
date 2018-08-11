/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

const int STACK_SIZE = 10;

class Stack {
public:
    Stack();
    Stack(int);
    ~Stack();
    long top() const;
    long pop();
    void push(long);
private:
    long *items;
    int sp;
};

Stack::Stack() {
    items = new long[STACK_SIZE];
    sp = -1;
}

Stack::Stack(int size) {
    items = new long[size]; // like a typed sbrk or malloc call,
                            //  except constructor is called
                            //  if present
    sp = -1;
}

Stack::~Stack() {
    delete[] items;         // like free, except destructor
                            //  is called
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
    Stack q;        // call Stack::Stack()
    Stack r(15);    // call Stack::Stack(int)
    q.push(1);
    long i = q.top();
    q.pop();
}
