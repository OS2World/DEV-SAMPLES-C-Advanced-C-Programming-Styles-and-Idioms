/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class EditWindow {
public:
    void addch(char x)       { window->addch(x); }
    void addstr(string x)    { window->addstr(x); }
    void clear()             { window->clear(); }
    . . . .
    EditWindow()             { if (\fIthis_is_an_X_environment\f5) {
                                   window = new XWindow;
                                   . . . . 
                               } else {
                                   window = new CursesWindow;
                                   . . . .
                             } }
private:
    Window *window;
    short topLine, bottomLine;
};
