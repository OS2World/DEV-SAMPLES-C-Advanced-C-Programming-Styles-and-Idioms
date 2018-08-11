/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class String {
public:
    // the public user interface to a String:

    // redefine "+" to mean catenation, two cases:
    friend String operator+(const char*, const String&);
    String operator+(const String&) const;
    int length() const;      // length of string in characters
    // . . . .               // other interesting operations

    // boilerplate member functions:

    String();                // default constructor
    String(const String&);   // constructor to initialize a new
                             //   string from an existing one
    String& operator=(const String&);  // assignment
    ~String();               // destructor

    /*
     * These operators are typical of the kinds of customized
     * behaviors a user can define for a type.  These are
     * examples suitable for a String class.
     */

    String(const char *);    // initialize from a "C string"
private:
    char *rep;               // implementation data and
                             //    internal functions
                             //    (here, represent internals
                             //    as a good old C string)

};
