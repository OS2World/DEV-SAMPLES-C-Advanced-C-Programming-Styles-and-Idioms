/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

/*
 * Put general inlines down here.  This is to support a
 * convention that inlines be broken out of the class
 * declaration.  Also, putting the inlines after both the
 * Envelope and Letter classes helps break some circular
 * dependencies.
 */

inline double
Letter::postage() {
    if (ounces < 2) return 29.0;
    else return 29.0 + ((ounces - 1) * 23.0);
}

inline Thing *
Letter::type() {
    extern Thing *letter;     // exemplar
    return letter;
}
