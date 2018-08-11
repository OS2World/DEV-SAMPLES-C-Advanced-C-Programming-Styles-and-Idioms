/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stddef.h>
#include <memory.h>

class LAPD {
friend class LAPDMemoryManager;
friend class Conn;
public:
    virtual int size() { return 0; }
    void *operator new(size_t);
    void operator delete(void *);
    LAPD(char *const);
protected:
    LAPD() { /* no-op */ }
private:
    int:8;
    union {
        struct {
            unsigned char flag;
            unsigned int sapi:6;
	    unsigned int commandResponse:1;
	    unsigned int zero:1;
	    unsigned int tei:7;
	    unsigned int ext:1;
            unsigned char control;
        } header;
        struct {
            LAPD *linkf, *linkb;
            unsigned short size;
        } minfo;
    };
    unsigned char tag;   // minfo system allocated tag
    int performCRCCheck() { /* . . . */ return 0; }
};

class Conn: public LAPD {
friend LAPD;
private:
    struct ConnPacketBody {
        unsigned char rep[4096];
    } *body;
    int bodySize;
    int size() { return sizeof(Conn) + bodySize; }
    Conn(const char *m): LAPD() {
        // . . . .
        ::memcpy(bodyStorage, m+sizeof(header), bodySize);
        body = (ConnPacketBody*) bodyStorage;
        manager.allocateResizeBlock( size() );
    }
    char bodyStorage[1];
};
