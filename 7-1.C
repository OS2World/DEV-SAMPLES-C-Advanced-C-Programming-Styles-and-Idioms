/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

template <class T> class Stack;

template <class T> class Cell {
friend class Stack<T>;
private:
    Cell *next;
    T *rep;
    Cell(T *r, Cell<T> *c): rep(r), next(c) { }
};

template <class T> class Stack {
public:
    T *pop();
    T *top() { return rep->rep; }
    void push(T *v) { rep = new Cell<T>(v, rep); }
    int empty() { return rep == 0; }
    Stack() { rep = 0; }
private:
    Cell<T> *rep;
};

template <class T> T *Stack<T>::pop() {
    T *ret = rep->rep;
    Cell<T> *c = rep;
    rep = rep->next;
    delete c;
    return ret;
}
