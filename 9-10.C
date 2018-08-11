/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <a.out.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <osfcn.h>

caddr_t load(const char *filename) {
    char buf[64];
    caddr_t oadx = (caddr_t)sbrk(0);
    caddr_t adx = ((char*)oadx) + PAGSIZ -
        (((long)oadx) % PAGSIZ);
    sprintf(buf, "ld -N -Ttext %X -A a.out %s -o a.out.new",
        adx, filename);

    system(buf);
    int fd = open(filename, O_RDONLY);
    exec Exec;
    read(fd, (char *)&Exec, sizeof(exec));
    sbrk(PAGSIZ - (((long)oadx) % PAGSIZ));
    caddr_t ldadx = (caddr_t)sbrk(Exec.a_text +
        Exec.a_data + Exec.a_bss);
    read(fd, ldadx, Exec.a_text + Exec.a_data);
    close(fd);
    return ldadx;
}
