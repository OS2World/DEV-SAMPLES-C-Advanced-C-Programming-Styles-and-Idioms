/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Window {
public:
    virtual void addch(char);
    virtual void addstr(string);
    virtual void clear();
    . . . .
private:
    Color curColor;
};

class CursesWindow : public Window {
public:
    void addch(char);
    void addstr(String);
    void clear();
    . . . .
private:
    WINDOW *cursesWindow;
};
