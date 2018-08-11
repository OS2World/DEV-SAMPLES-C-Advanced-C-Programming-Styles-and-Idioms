/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

template<class T, class S>
    class Array: public CollectionRep<T, S> {
    public:
        Array();
        Array(Array<T, S>&);
        ~Array();
        class Collection<T, S> make();
        class Collection<T, S> make(int size);
        T& operator[](int i);
        void put(const T&);
    private:
        T *vec;
        int size;
    };

template<class T>
    struct HashTableElement {
        HashTableElement *next;
        T *element;
    };

template<class T, class S>
    class HashTable: public CollectionRep<T, S> {
    public:
        HashTable();
        HashTable(HashTable<T, S>&);
        ~HashTable();
        class Collection<T, S> make();
        class Collection<T, S> make(int);
        T& operator[](int i);
        T& operator[](S);
        void put(const T&);
    private:
        int nbuckets;
        virtual int hash(int l);
        HashTableElement<T> *buckets;
    };
