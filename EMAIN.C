/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E M A I N . C                             //
//                                                            //
//         Sample driver code for geometric shapes example    //
//                                                            //
//************************************************************//
#include <a.out.h>
#include <fcntl.h>
#include "eshape.h"
#ifndef _COORDINATE_H
#include "ecoord.h"
#endif
extern void doClassUpdate();
extern int compile(const String &fileName);
extern int mkfile(const String &fileName,
				 const String &contents);

int main2() {
    Shape::init();
    Coordinate p1, p2, p3;
    Shape object = (*shape)->make(p1, p2, p3);
    printf("object is "); object->draw(); printf("\n");

    // demonstrate virtual function update
    object->move(p1);
    compile("ev2tri.c");
    String include = "includes.h";
    mkfile(include,
	"#include \"ek.h\"\n#include \"ev2tri.h\"\n");
    object->update("v2Triangle.o", "Triangle::move");
    object->move(p1);
    doClassUpdate();
    object->move(p1);
    {
        Shape object3 = (*shape)->make(p1, p2, p3);
        printf("object3 is "); object3->draw(); printf("\n");
    }
printf("main: making object2\n");
    Shape object2 = (*shape)->make(p1, p2, p3);
    shape->gc();        // do a gc now and then
    printf("object2 is "); object2->draw(); printf("\n");
printf("main: made object2, calling object2->move\n");
    object2->move(p1);
    shape->gc();        // do a gc now and then
printf("exiting\n");
    return 0;
}

int main() {
    int retval = main2();
    shape->gc();
    return retval;
}

void
doClassUpdate() {
    extern Shape *triangle;
    const String include = "includes.h";
    mkfile(include,
	"#include \"ek.h\"\n#include \"ev2tri.h\"\n");

    compile("ev3tria.c");
    (*triangle).update("ev3tria.o", "Triangle::make",
        "Shape (Triangle::*TYPE)()");

    compile("ev3trib.c");
    (*triangle).update("ev3trib.o", "Triangle::make",
        "Shape (Triangle::*TYPE)\
            (Coordinate,Coordinate,Coordinate)");

    compile("ev3trim.c");
    (*triangle).update("ev3trim.o", "Triangle::move");

    compile("v3tric.c");
    (*triangle).update("v3tric.o",
					"Triangle::cutover");

    mkfile(include, "#include \"ek.h\"\n\
       #include \"ev3tri.h\"\n");

    mkfile("ev3doit.c",  "#include \"ek.h\"\n\
       #include \"ev3tri.h\"\n\
        Top * Shape::doit() {\n\
            printf(\"v3 Shape::doit (new) called\\n\");\n\
            Thingp Ttriangle = triangle;\n\
            shape->dataUpdate(Ttriangle,\n\
                new Triangle(Exemplar(0)));\n\
            triangle = (ShapeRep*) Ttriangle;\n\
            printf(\"Shape::doit: did data update\\n\");\
            return 0;\n\
        }\n\n\
        Triangle::Triangle(Exemplar e): ShapeRep(e) { }\n");
    compile("ev3doit.c");
    printf("doClassUpdate:\
        calling shape->update(\"ev3doit.o\",\
        \"Shape::doit\")\n");
    shape->update("ev3doit.o", "Shape::doit");
    shape->doit();
    shape->gc();        // do a gc now and then
    unlink("ev3doit.c");
    unlink("ev3doit.o");
}

#include <sys/stat.h>

int compile(const String& fileName) {
    struct stat dotC, dotO;
    String fileNameDotO =
	    fileName(0,fileName.length()-2) + ".o";
    stat(fileName, &dotC);
    stat(fileNameDotO, &dotO);
    if (dotC.st_mtime < dotO.st_mtime) {
        printf("\"%s\" is up to date\n", (const char*)fileName);
        return 0;
    } else {
        String command = String("CC +e0 -c -g ") + fileName;
        printf("compile: <%s>\n", (const char*)command);
        return system(command);
    }
}

extern int mkfile(const String &fileName,
				    const String &contents) {
    FILE *inc = fopen(fileName, "w");
    printf("mkfile: creating <%s>\n", (const char *)fileName);
    fprintf(inc, (const char*)contents);
    return fclose(inc);
}
