/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <math.h>
// #include <X11/X.h>

typedef long Display, Window, GContext;

/*
 * File Shapes.h
 * Author:  J. O. Coplien
 *
 * This header file contains declarations for classes used in
 * a demonstration Shape library.  Many member functions are
 * defined herein as inlines.
 */

/*-----------------------------------------------------------*/
/* class Angle is an angle in degrees or radians.  It is a   */
/* class so that it can be easily ported to systems using    */
/* either degrees or radians, and also so arithmetic         */
/* precision(float, double, or int) can be changed.          */
/*-----------------------------------------------------------*/

class Angle {
friend double cos(Angle);
friend double sin(Angle);
public:
    Angle(double d)       { radians = d; }
    Angle ()              { radians = 0; }
    Angle(const Angle& a) { radians = a.radians; }
    inline Angle &operator=(const Angle& a) {
        radians = a.radians;
        return *this;
    }
    Angle operator+(const Angle&) const;
private:
    double    radians;
};

/*-----------------------------------------------------------*/
/* class Coordinate describes a point on the Cartesian plane.*/
/*   It can be in micrometers, pixels, inches, or any other  */
/* convenient units and scale.                               */
/*-----------------------------------------------------------*/

class Coordinate {
public:
    inline long x() const       { return x_rep; }
    inline long y() const       { return y_rep; }
    Coordinate    &operator=(Coordinate &c) {
        x_rep = c.x_rep;
        y_rep = c.y_rep;
        return *this;
    }
    Coordinate(long x, long y) {
        x_rep = x; y_rep = y;
    }
    Coordinate(const Coordinate &c) {
        x_rep = c.x_rep;
        y_rep = c.y_rep;
    }
    Coordinate()        { x_rep = y_rep = 0;}
    ~Coordinate()       { }

    void rotateAbout(Coordinate,Angle);
private:
    long x_rep, y_rep;
};


/*-----------------------------------------------------------*/
/* These functions overload the normal trig functions,       */
/* arranging so that they can be called with Angle as an     */
/* argument.  Since overloading cannot be done on the basis  */
/* of return value--only on the basis of argument            */
/* type--the trig function atan, which needs to be able      */
/* to return an object of type Angle, cannot be overloaded   */
/* and must be made a whole new function.                    */
/*-----------------------------------------------------------*/

inline double cos(Angle a)      { return ::cos(a.radians); }
inline double sin(Angle a)      { return ::sin(a.radians); }
inline Angle Angleatan(double t) {
    Angle a(::atan(t)); return a;
}

/*-----------------------------------------------------------*/
/* Class Color encapsulated the implementation of color      */
/* encoding for the graphics package being used; its         */
/* internals can be accessed just by low-level interface     */
/* routines, while high-level routines deal at a more general*/
/* level.  This makes porting possible across a wide variety */
/* of machines.                                              */
/* Flashing is an attribute of color.  The commonly used     */
/* constants Black and White are predeclared as constant     */
/* global color objects.                                     */
/*-----------------------------------------------------------*/

enum Flash { FlashBlack, FlashWhite, FlashOff };

class Color {
public:
    inline    double    red()         { return red_rep;  }
    inline    double    green()       { return green_rep;  }
    inline    double    blue()        { return blue_rep;  }
    	    Color(double r=0.0, double g=0.0,
    	          double b=0.0, Flash f=FlashOff) {
        red_rep = r;
        green_rep = g;
	  blue_rep = b;
        flashing = f;
    }
    inline    Color&    operator=(const Color& c) {
        red_rep = c.red_rep;
        green_rep=c.green_rep;
        blue_rep = c.blue_rep;
    	return *this;
    }
    	    ~Color()    	{ }
private:
    double    red_rep, green_rep, blue_rep;
    Flash    flashing;
};

const Color Black, White = Color(1.0, 1.0, 1.0);

/*-----------------------------------------------------------*/
/* Shape is the base class for all of the graphical shapes.  */
/* It defines the signature (operations) possible on a shape,*/
/* and also provides the actual implementation of operators  */
/* common to all shapes (like move, common to all with some  */
/* exceptions).                                              */
/*-----------------------------------------------------------*/

class Shape { 
public:
    // rotate about center
    virtual    void    rotate(Angle a)    	{ } 
    virtual    void    move(Coordinate xy) {
        erase(); center_val=xy; draw();
    }
    virtual    void    draw()  = 0;     // renderer
    virtual    void    erase() {
        color = Black; draw();
    }

    virtual    void    redraw() {
        erase(); draw();
    }
    Shape();
    virtual   ~Shape();
    virtual   Coordinate origin() const  { return center_val; }
    virtual   Coordinate center() const  { return center_val; }
    inline    Shape   *next() const   { return next_pointer; }
    inline    Shape   *prev() const   { return prev_pointer; }
    inline    void    insert(Shape* i) {
        i->next_pointer= this;
        i->prev_pointer=prev_pointer;
        prev_pointer->next_pointer=i;
        prev_pointer = i;
    }
    inline    void    append(Shape* i)    {
                          i->next_pointer=next();
    	    	    	  i->prev_pointer = this;
    	    	    	  next_pointer->prev_pointer=i;
    	    	    	  next_pointer = i;
    	    	    	}
protected:

    /*
     * These are protected instead of private so they can be
     * accessed by routines in the derived classes
     */

    Coordinate    center_val;    // nominal center
    Color    	color;    	// shape's color

    /*
     * These class static variables are used by the underlying
     * window package (e.g., X) for general graphics setup.
    */

    static    	Display    	display;
    static    	Window    	window;
    static    	GContext    	gc;

private:
    Shape    	*next_pointer;   // pointer to next in list
    Shape    	*prev_pointer;   // pointer to previous in list
};

/*-----------------------------------------------------------*/
/* Line is a special shape, since it is usually the          */
/* rendering component of all other shapes. It alone among   */
/* shapes has a rotateAbout member function which is used as */
/* the primitive for rotating other shapes.  The rotate      */
/* operation is a degenerate form of rotateAbout. The center */
/* is defined as the average of the endpoints; the origin is  */
/* the first endpoint.                                       */
/*-----------------------------------------------------------*/

class Line : public Shape {
public:
    void    rotate(Angle a)    { rotateAbout(center(),a); }
    void    rotateAbout(Coordinate,Angle);
    void    draw();
    inline Line &operator=(const Line &l) {
         p=Coordinate(l.p); q=Coordinate(l.q); return *this;
    }
    Line(Coordinate,Coordinate);
    Line(Line& l) {
        p = l.p; q = l.q;
        center_val = l.center_val;
    }
    Line()    	    { p = Coordinate(0,0);
                      q = Coordinate(0,0); }
   ~Line()    	    { erase(); }
    inline  Coordinate      e() const   { return q; }
    inline  Coordinate origin() const   { return p; }
private:
    Coordinate    p, q;    	    // line endpoints
};

/*-----------------------------------------------------------*/
/* Rect is made up of four lines. Origin is upper-left hand  */
/* corner, and is established from the constructor's first   */
/* parameter. Center is geometric center, as expected.  The  */
/* operation erase is inherited from Shape. Reps are         */
/* protected instead of private so that subclass Square can  */
/*  use them.                                                */
/*-----------------------------------------------------------*/

class Rect : public Shape {
public:
    void    	rotate(Angle);
    void    	draw();
    void    	move(Coordinate);
    	    //upper left corner, x size, y size
    	    Rect(Coordinate,long,long);
    	    ~Rect()    	    { erase(); }
    inline    Coordinate    origin() const { return l1.origin(); }
protected:
    Line    	l1, l2, l3, l4;
};

/*-----------------------------------------------------------*/
/* Ellipse's center is geometric center; origin is center.   */
/* Ellipse is unimplemented.                                 */
/*-----------------------------------------------------------*/

class Ellipse : public Shape {
public:
    void    	rotate(Angle);
    void    	draw();
    	    // center, major axis, minor axis
    	    Ellipse(Coordinate,long,long);
    	    ~Ellipse()    	{ erase(); }
protected:
    long    	major, minor;
};

/*-----------------------------------------------------------*/
/* A triangle is made up of three lines.  Its center is      */
/* calculated as the average of all points.                  */
/*-----------------------------------------------------------*/

class Triangle : public Shape {
public:
    void    	rotate(Angle);
    void    	draw();
    void    	move(Coordinate);
    	    Triangle(Coordinate,Coordinate,Coordinate);
    	    ~Triangle()    	{ erase(); }
private:
    Line    	l1, l2, l3;
};

/*-----------------------------------------------------------*/
/* A square is just a degenerate rectangle.  All member      */
/* functions are inherited from Rect; only the constructor   */
/* is customized, and it does nothing but call Rect's        */
/*  constructor.                                             */
/*-----------------------------------------------------------*/

class Square : public Rect {
public:
    	    Square(Coordinate ctr, long x):
    	    	Rect(ctr, x, x)         { }
};

/*-----------------------------------------------------------*/
/*                                                           */
/* File Shapes.c, containing Shape code for example program  */
/*                                                           */
/*-----------------------------------------------------------*/


extern "C" {
    extern void doXInitialization(Shape&);
    // extern void
      // XDrawLine(Display, Window, GContext, int, int, int, int);
}

/*
 * CLASS ANGLE
 */

Angle
Angle::operator+(const Angle& angle) const {
    Angle retval = angle;
    retval.radians += radians;
    return retval;
}

/*
 * CLASS COORDINATE
 */

void
Coordinate::rotateAbout(Coordinate pivot, Angle angle)
{
    long xdistance = pivot.x()-x(), ydistance = pivot.y()-y();
    long xdistsquared = xdistance * xdistance,
    	ydistsquared = ydistance * ydistance;
    double r = ::sqrt( xdistsquared + ydistsquared );
    Angle newangle = angle +
                Angleatan(double(ydistance)/double(xdistance));
    x_rep = pivot.x() + long(r * ::cos(newangle));
    y_rep = pivot.y() + long(r * ::sin(newangle));
}

/*
 * CLASS SHAPE
 */

/* flag for underlying graphics package */

static int X_initialized = 0;

Shape::Shape() {
    center_val = Coordinate(0,0);
    next_pointer=prev_pointer=0;
    color = White;
    if( !X_initialized) {
    	doXInitialization(*this);
    	X_initialized = 1;
    }
}

/*
 * CLASS LINE
 */

void
Line::rotateAbout(Coordinate c, Angle angle) {
    erase();
    p.rotateAbout(c, angle);
    q.rotateAbout(c, angle);
    draw();
}

void
Line::draw() {
    if (p.x()-q.x() && p.y()-q.y()) {
//    	XDrawLine(display, window, gc, p.x(),
//                                         p.y(), q.x(), q.y());
    }
}

Line::Line(Coordinate p1, Coordinate p2) {
    p = p1; q = p2;
    center_val = Coordinate((p.x()+q.x())/2, (p.y()+q.y())/2);
    color = Color(White);
    draw();
}

/*
 * CLASS RECTANGLE
 */

void
Rect::rotate(Angle angle) {
    erase();
    l1.rotateAbout(center(), angle);
    l2.rotateAbout(center(), angle);
    l3.rotateAbout(center(), angle);
    l4.rotateAbout(center(), angle);
    draw();
}

void
Rect::draw() {
    l1.draw();
    l2.draw();
    l3.draw();
    l4.draw();
}

void
Rect::move(Coordinate c) {
    /*
     * Argument is center.  Move center there; find out how far
     * center moved and displace all points by the same amount.
     */

    erase();
    long xmoved = c.x() - center().x();
    long ymoved = c.y() - center().y();
    center_val = c;
    l1 = Line(Coordinate(l1.origin().x()+xmoved,
                                      l1.origin().y()+ymoved),
    	    Coordinate(l1.e().x()+xmoved,l1.e().y()+ymoved) );
    l2 = Line(Coordinate(l2.origin().x()+xmoved,
                                      l2.origin().y()+ymoved),
    	    Coordinate(l2.e().x()+xmoved,l2.e().y()+ymoved) );
    l3 = Line(Coordinate(l3.origin().x()+xmoved,
                                      l3.origin().y()+ymoved),
    	    Coordinate(l3.e().x()+xmoved,l3.e().y()+ymoved) );
    l4 = Line(Coordinate(l4.origin().x()+xmoved,
                                      l4.origin().y()+ymoved),
    	    Coordinate(l4.e().x()+xmoved,l4.e().y()+ymoved) );
    draw();
}

Rect::Rect(Coordinate topLeft, long xsize, long ysize) {
    Coordinate    a(topLeft);
    Coordinate    b(a.x()+xsize, a.y());
    Coordinate    c(a.x(),a.y()+ysize);
    Coordinate    d(b.x(),c.y());
    l1 = Line(a,b);
    l2 = Line(b,c);
    l3 = Line(c,d);
    l4 = Line(d,a);
    center_val = Coordinate((l1.origin().x()+l2.e().x())/2,
    	    	    (l4.origin().y()+l4.e().y())/2);
    draw();
}

/*
 * CLASS TRIANGLE
 */

void
Triangle::rotate(Angle angle) {
    erase();
    l1.rotateAbout(center(), angle);
    l2.rotateAbout(center(), angle);
    l3.rotateAbout(center(), angle);
    draw();
}

void
Triangle::move(Coordinate c) {
    /*
     * Argument is center.  Move center there; find out how far
     * center moved and displace all points by the same amount.
     */

    erase();
    long xmoved = c.x() - center().x();
    long ymoved = c.y() - center().y();
    center_val = c;
    l1 = Line(Coordinate(l1.origin().x()+xmoved,
                                    l1.origin().y()+ymoved),
    	    Coordinate(l1.e().x()+xmoved,l1.e().y()+ymoved) );
    l2 = Line(Coordinate(l2.origin().x()+xmoved,
                                    l2.origin().y()+ymoved),
    	    Coordinate(l2.e().x()+xmoved,l2.e().y()+ymoved) );
    l3 = Line(Coordinate(l3.origin().x()+xmoved,
                                    l3.origin().y()+ymoved),
    	    Coordinate(l3.e().x()+xmoved,l3.e().y()+ymoved) );
    draw();
}

void
Triangle::draw() {
    l1.draw(); l2.draw(); l3.draw();
}

Triangle::Triangle(Coordinate a, Coordinate b, Coordinate c) {
    l1 = Line(a,b);  l2 = Line(b,c);  l3 = Line(c,a);
    center_val =
               Coordinate((l1.e().x()+l2.e().x()+l3.e().x())/3,
        	    	    (l1.e().y()+l2.e().y()+l3.e().y())/3);
    draw();
}

/*-----------------------------------------------------------*/
/* File main.c -- Driver program for Shapes example          */
/*-----------------------------------------------------------*/

const int XSIZE = 800;
const int YSIZE = 1024;

void
rotateList(Shape *s, Angle a)
{
    for (Shape *f = s;  f;  f = f->next())
    	f->rotate(a);
}

int
main()
{
    Coordinate origin (0,0);

    /*
     * windowBorder is not only the frame for the screen,
     * but also serves as list head for the list of shapes
     */

    Rect windowBorder(origin, XSIZE, YSIZE);

    Shape * t = new Triangle(
    	Coordinate(100, 100),
    	Coordinate(200, 200),
    	Coordinate(300, 100)
    );
    windowBorder.append(t);

//    Shape * c = new Circle(Coordinate(500,652), 150);
//    t->insert(c);

    rotateList(&windowBorder, 90.0);
    return 0;
}
