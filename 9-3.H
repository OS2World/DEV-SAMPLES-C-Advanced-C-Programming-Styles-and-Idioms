/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Letter: public Thing {
public:
    /* all user-defined operators go here.  Note that, because
     * of the use of operator->, this signature does not have
     * to be mimicked in the Envelope.  However, the Envelope's
     * rep field has to be appropriately typed.  Assignment
     * operators do not go here, but in the Envelope.
     *
     * return_type should either be a primitive
     * type, or of type Envelope, of type Envelope&, or
     * a concrete data type
     */
    virtual void send(String name, String address);
    virtual double postage();
    // virtual return_type user-defined-function
    // . . . .
    virtual Envelope make();          // constructor
    virtual Envelope make(double);    // another constructor
    virtual Envelope make(int days, double weight);
    virtual Thing *cutover(Thing*);  // run-time update function
    Letter() { }
    ~Letter() { }
    Thing *type();
protected:
    friend class Envelope;
    double ounces;
    static void *operator new(size_t l) {
        return ::operator new(l);
    }
    static void operator delete(void *p) {
        ::operator delete(p);
    }
    String name, address;
    // . . . .
private:
    // . . . .
};
