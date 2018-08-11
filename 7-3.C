/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

template <class T> class List {
};

template <class ElementType> class Set {
public:
    void add(const ElementType& e) {
        if (!rep.element(e)) rep.add(e); 
    }
    ElementType get() {
        return rep.get;
    }
    void remove(const ElementType&);
    int exists(const ElementType& e) const {
        return rep.element(e);
    }
    Set<ElementType> Union(const Set<ElementType>&) const;
    Set<ElementType> Intersection(const Set<ElementType>&)
        const;
    int size() const { return rep.size(); }
    void sort() { rep.sort(); }
private:
    List<ElementType> rep;
};
