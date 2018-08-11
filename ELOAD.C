/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

//************************************************************//
//                                                            //
//     F I L E :    E L O A D . C                             //
//                                                            //
//         Code for C function loader function                //
//                                                            //
//************************************************************//

#include <a.out.h>
#include <fcntl.h>
#include "emptr.h"
#include "String.h"

static String symtab;
static char y = 'a';

extern "C" vptp load(const char *filename) {
    // load first link edits the specified file into
    // a new a.out, using a previous a.out file as
    // the base to resolve symbolic references.
    // load then opens the new file, figures out its
    // .text and .data sizes, and reads them into a
    // newly allocated block of memory.  It functions
    // as a dynamic loader, designed to work with an
    // outboard incremental link editor.  C linkage
    // is just so it can be called from C, too.

    int errcode = 0;
    String newfile;
    char buf[256];
    long adx, oadx;
    unsigned char *ldadx;
    struct exec Exec;
    int fd, wc;

    // use reasonable defaults first time through;  a.out will
    // be the file supplying the symbol table.  Each time we do
    // an incremental load, change the name of the file that
    // the link editor will produce.  Clean up old files as
    // we go along.

    if (!symtab.length()) {
        symtab = "a.out"; newfile = "b.out";
    } else {
        symtab = String(++y) + ".out";
        newfile = String(y+1) + ".out";
    }

    // find current memory high, and pad things so memory high
    // is on an even page boundary.
    oadx = (long)sbrk(0);
    adx = oadx + PAGSIZ - (oadx%PAGSIZ);

    // create load command to do an incremental link edit
    // of the provided .o against the current a.out, specifying
    // that the new code be linked at memory high
    sprintf(buf, "ld -N -Ttext %X -A %s %s -o %s",
        adx, (const char*)symtab, filename,
        (const char*)newfile);
    printf("<%s>\n", buf);
    if ((errcode=system(buf)) != 0) {
        printf("load: link edit returned error code %d\n",
            errcode);
    }
    if (symtab != "a.out") unlink(symtab);

    // open it up to load it into memory
    fd = open(newfile, O_RDONLY);
    if (fd < 0) {
        printf("load: open of \"%s\" failed\n", newfile);
        return 0;
    }

    // read the relocatable file header to get text,
    // data sizes
    read(fd, (char *)&Exec, sizeof(struct exec));

    // now do the memory pad, and allocate space for the
    // new program text
    sbrk(int(PAGSIZ-(oadx%PAGSIZ)));
    ldadx = (unsigned char *)
        sbrk(int(Exec.a_text + Exec.a_data + Exec.a_bss));

    // read the newly linked file into the running
    // process at the address just calculated
    wc = read(fd, (char *)ldadx,
	int(Exec.a_text + Exec.a_data));
    close(fd);

    // return load address
    return (vptp) ldadx;
}
