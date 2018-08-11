/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

int main() {
    Value *v = new Value(100,1260); // voltage at a frequency
    BPF bpf(1000, 10000);    // a band-pass filter
    HPF hpf(1100);           // a high-pass filter
    LPF lpf(8000);           // a low-pass filter
    Filter *a;               // a pointer to a filter
    a = (Filter*)bpf(&hpf);  // apply a band-pass filter to a
    a->print();              //   high-pass filter:  result?
    (*a)(v)->print();        // apply to a voltage and print
    a = (Filter*)(*a)(&lpf); // apply that to a low-pass
    a->print();              //   filter:  whaddya get?
    a = (Filter*)(*a)(v);    // now apply voltage to input
    a->print();              //   of all that, and print
    lpf(&hpf)->print();      // combine low- & high-pass
    return 0;                //   filters
}
