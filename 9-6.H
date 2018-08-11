/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "k.h"
#include "collection.h"

// Store items of class T, indexed by values of class S

template<class T, class S>
    class CollectionRep: public Thing {
    public:
        virtual Collection<T, S> make();
        virtual Thing* cutover(Thing *);
        virtual T& operator[](int);
        virtual T& operator[](S);
        virtual void put(const T&);
        CollectionRep() { }
        ~CollectionRep() { }
        Thing *type();
    protected:
        friend class Collection<T, S>;
        static void *operator new(size_t l) {
            return ::operator new(l);
        }
        static void operator delete(void *p) {
            ::operator delete(p);
        }
    private:
        CollectionRep<T, S> *exemplarPointer;
    };
