/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include "k.h"

template<class T, class S> class CollectionRep;

template<class T, class S>
    class Collection: public Top {
    public:
        CollectionRep<T, S> *operator->() const { return rep; }
        Collection();
        Collection(CollectionRep<T, S>&);
        ~Collection();
        Collection(Collection<T, S>&);
        Collection& operator=(Collection<T, S>&);
        T& operator[](int i) { return (*rep)[i]; }
        T& operator[](S s) { return (*rep)[s]; }
    private:
        static void *operator new(size_t) { return 0; }
        static void operator delete(void *p) {
           ::operator delete(p);
        }
        CollectionRep<T, S> *rep;
    };
