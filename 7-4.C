/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

template <class T> class ListItem;

template <class T> class List {
public:
    void sort();          // sort list in place
    void put(T& t);
    T get();
    int element(const T&) const;
    int size() const;
    //  . .               // many other interesting operations
    List() { head = 0; }  // default constructor
private:
    ListItem<T> *head;    // list head
};

template <class T> class ListItem {
friend class List<T>;
private:
    ListItem<T> *next;
    T *item;
    ~ListItem() { delete item; }
    ListItem(const ListItem<T> *n, T *i)
        { item=new T(*i); next=(ListItem<T>*)n; }
};

template <class T> T List<T>::get() {             // get from head of list
    T retval = *(head->item);
    ListItem<T> *temp = head;
    head = head->next;
    delete temp;
    return retval;
}

template <class T> void
List<T>::put(T& t) { head = new ListItem<T>(head, &t); }

class SetBase {
friend ErsatzListElement;
private:
    virtual int comparelt(const void*, const void*)
        const = 0;
    virtual int compareeq(const void*, const void*)
        const = 0;
};

class ErsatzListElement {
    // this is unparameterized, which means that there is one
    // List template instantiation to serve all Sets.
public:
    void *rep;
    int operator< (const ErsatzListElement& l) const {
        return theSet->comparelt(this,&l);
    }
    int operator==(const ErsatzListElement& l) const {
        return theSet->compareeq(this,&l);
    }
    ErsatzListElement(const void* v = 0) { rep = (void*)v; }
    ErsatzListElement(SetBase *s, void *v=0): theSet(s) {
        rep = v;
    }
private:
    SetBase *theSet;
};

template <class T> class Set: private SetBase {
public:
    void add(T t2) {
        ErsatzListElement t(this, new T(t2)); rep.put(t);
    }
    T get() {
        ErsatzListElement l=rep.get(); return *((T*)(l.rep));
    }
    void remove(const T&);
    int exists(const T& e) {
        ErsatzListElement t(this, (T*)&e);
        return rep.element(t);
    }
    Set<T> Union(const Set<T>&) const;
    Set<T> Intersection(const Set<T>&) const;
    int size() const { return rep.size(); }
    void sort() { rep.sort(); }
    Set();
private:
    List<ErsatzListElement> rep;
    int comparelt(const void* v1, const void* v2) const {
        const T* t1 = (const T*) v1;
        const T* t2 = (const T*) v2;
        return *t1<*t2;
    }
    int compareeq(const void* v1, const void* v2) const {
        const T* t1 = (const T*) v1;
        const T* t2 = (const T*) v2;
        return *t1==*t2;
    }
};

template <class T> Set<T>::Set() { }

#include <iostream.h>

int main() {
    Set<int> foo;
    Set<double> bar;
    foo.add(1);
    foo.add(2);
    cout << foo.get() << "\n";
    cout << foo.get() << "\n";
    bar.add(3.0);
    bar.add(4.0);
    cout << bar.get() << "\n";
    cout << bar.get() << "\n";
}
