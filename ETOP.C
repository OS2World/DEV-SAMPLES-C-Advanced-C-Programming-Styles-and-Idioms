/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E T O P . C                               //
//                                                            //
//         Code for class Top                                 //
//                                                            //
//************************************************************//

#include "ek.h"
#include <sys/types.h>

Top *
Top::doit() {
    // unused function provided as a handy,
    // user-loadable hook to help orchestrate
    // class update
    return 0;
}

int
Top::compareFuncs(int vtblindex, vptp, vptp fptr) {
    // this compares two function pointer abstractions
    // for equality.  The first function pointer is
    // characterized by its vtbl index and a function
    // pointer;  the second, by just a function pointer.
    // The use of these parameters may be system dependent;
    // here the first pointer's function address is
    // unused
    return vtblindex == (int)fptr;
}

mptr *
Top::findVtblEntry(vptp f) {
    // Look in "this" object's virtual function table
    // for a function pointer equal to the f parameter,
    // and return the address of its mptr structure
    // (the full contents of the virtual function table
    // entry)

    // mpp will be the address of the vtbl pointer;  we
    // are guaranteed by the inheritance structure that
    // the vtbl pointer will be at the beginning of
    // every object of interest (all objects are derived
    // from Top)
    mptr ** mpp = (mptr**) this;

    // dereference the pointer address to get the
    // vtbl address which is sitting in the beginning
    // of this object
    mptr * vtbl = *mpp;

    printf("Top::findVtblEntry(%d):  vtbl = 0x%x\n", f, vtbl);

    // go through my own vtbl;  a zero entry is an end
    // sentinel, and the zeroth entry is unused.  Look
    // for the requested function
    for(int i = 1; vtbl[i].f; ++i ) {
        if (compareFuncs(i, vtbl[i].f, f)) {
            return vtbl + i;
        }
    }
    return 0;
}

// declaration of external "load" function from C land
extern "C" vptp load(const char *);

void
Top::update(    String filename,
                String fname,
                const char *const TypedefSpec) {

    // Get function fname from file filename and
    // load it into memory.  The last parameter
    // optionally specifies the type of a pointer
    // to the function;  it is necessary if the
    // function is overloaded.  The virtual function
    // table is updated accordingly.  Only virtual
    // functions can be updated.

    const String temp = "/tmp";

    printf("Top::update(\"%s\", \"%s\", \"%s\")\n",
        (const char *)filename, (const char *)fname,
        (const char *)TypedefSpec);
    String prepname = temp + "/" + "t.c";
    String Typedef, cast = "";
    if (strlen(TypedefSpec)) {
        Typedef = String("// TYPE used to disambiguate\
        overloaded function\n\t\t\ttypedef ") + TypedefSpec;
    } else {
        Typedef = "typedef vptp TYPE";
        cast = "(vptp)";
    }
    // make prepname:  helper function to return address
    // of the function being updated
    FILE *tempFile = fopen(prepname, "w");
    fprintf(tempFile, "#\
        include \"includes.h\"\n\
        extern vptp functionAddress() {\n\
            %s;\n\
            TYPE retval = %s&%s;\n\
            return (vptp)retval;\n\
        }\n",
        (const char*)Typedef,
        (const char *)cast,
        (const char*)fname);
    fclose(tempFile);

    // Compile the helper function
    String command = String("DIR=`pwd`; cd ") + temp + ";\
        CC +e0 -I$DIR -c -g " + prepname;
    system(command);
    unlink(prepname);
    String objectname =
            prepname(0, prepname.length() - 2) + ".o";

    // Load the helper function.  Recall that load
    // returns the new function's address
    vvptp findfunc = (vvptp)load(objectname);
    unlink(objectname);
    printf("Top::update: calling findVtblEntry(%d)\n",
                    (*findfunc)());

    // Now find the correct vtbl entry within this
    // class vtbl. The helper function is called to
    // tell findVtblEntry which function it is
    // looking for
    mptr *vtblEntry = findVtblEntry((*findfunc)());

    // Now load the new version of the function and store
    // its address in the vtbl entry
    printf("Top::update: old vtblEntry->f = 0x%x\n",
        vtblEntry->f);
    printf("Top::update: calling load(\"%s\")\n",
        (const char *) filename);
    vtblEntry->f = load(filename);
    printf("Top::update: complete, new vtblEntry->f = 0x%x\n",
        vtblEntry->f);
}
