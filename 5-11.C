/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <stddef.h>
#include <memory.h>

class LAPD {
friend class LAPDMemoryManager;
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
    int performCRCCheck() { /* . . . */ }
};

#define round(a,b) (((a+b-1)/b)*b)

class LAPDMemoryManager {
friend LAPD;
private:
    enum { MessageBufSize=4096, Log2MessageBufSize=13 };
    unsigned char availBuf[
	   (1+Log2MessageBufSize)*round(sizeof(LAPD),4)];
    LAPD *avail;
    unsigned char buf[MessageBufSize];
    LAPD *buddy(int k, LAPD *l) {
        char *cp = (char *) l;
        return (LAPD*)(long(cp) ^ (1<<(k+1)));
    }
public:
    LAPDMemoryManager() {
        LAPD* buf = (LAPD*)this->buf;
        avail = (LAPD*)availBuf;
        avail[Log2MessageBufSize].minfo.linkf = 0;
        avail[Log2MessageBufSize].minfo.linkb = 0;
        buf[0].minfo.linkf = buf[0].minfo.linkb =
                              &avail[Log2MessageBufSize];
        buf[0].tag = 1;
        buf[0].minfo.size = Log2MessageBufSize;
        for (int k = 0; k < Log2MessageBufSize; k++) {
            avail[k].minfo.linkf = avail[k].minfo.linkb =
                                        (LAPD*)&avail[k];
        }
    }
    int savej;
    LAPD *largestBlock() {
        for (int k = Log2MessageBufSize; k >= 0; --k) {
            if (avail[k].minfo.linkf != &avail[k]) {
                savej = k;
                return avail[k].minfo.linkf;
            }
        }
        return 0;
    }
    void allocateResizeBlock(int ktemp) {
        int k, j = savej;
        // Round up to next 2**n
        for (int i = 1; i < Log2MessageBufSize; i++) {
            k = 1 << i;
            if (k > ktemp) break;
        }
        LAPD *l = avail[j].minfo.linkf;
        avail[j].minfo.linkf = l->minfo.linkf;
        l->minfo.linkf->minfo.linkb = &avail[j];
        for(l->tag = 0; j - k; ) {
            --j;
            LAPD *p = (LAPD*)(((char *)l) + (1 << j));
            p->tag = 1;
            p->minfo.size = j;
            p->minfo.linkf = &avail[j];
            p->minfo.linkb = &avail[j];
            avail[j].minfo.linkf = p;
            avail[j].minfo.linkb = p;
        }
    }
    void deallocateBlock(LAPD *l, int k) {
        for(;;) {
            LAPD *p = buddy(k,l);
            if (k==Log2MessageBufSize || p->tag == 0 ||
                                    p->minfo.size != k) {
                break;
            }
            p->minfo.linkb->minfo.linkf = p->minfo.linkf;
            p->minfo.linkf->minfo.linkb = p->minfo.linkb;
            ++k;
            if (p < l) l = p;
        }
        l->tag = 1;
        l->minfo.linkf = avail[k].minfo.linkf;
        avail[k].minfo.linkb = l;
        l->minfo.size = k;
        l->minfo.linkb = &avail[k];
        avail[k].minfo.linkf = l;
    }
};

static LAPDMemoryManager manager;

// this operator allows one object in the LAPD
// hierarchy to overlay itself with an instance
// of one of its derived classes

inline void *operator new(size_t, LAPD* l) { return l; }

class X25: public LAPD {
friend LAPD;
private:
    struct X25PacketBody {
           unsigned char rep[4096];
    };
    int size() { return sizeof(X25); }
    X25(char *const m): LAPD() {
        manager.allocateResizeBlock( size() );
        ::memcpy(&body, m, sizeof(body));
    }
    X25PacketBody body;
};

class EIN: public LAPD {
friend LAPD;
private:
    struct EINPacketBody {
       unsigned char rep[4096];
    };
    int size() { return sizeof(EIN); }
    EIN(char *const m): LAPD() {
        manager.allocateResizeBlock( size() );
        ::memcpy(&body, m, sizeof(body));
    }
    EINPacketBody body;
};

void *
LAPD::operator new(size_t /* unused */) {
    return manager.largestBlock();
}

void
LAPD::operator delete(void *l) {
    manager.deallocateBlock((LAPD*)l, ((LAPD*)l)->size());
}

LAPD::LAPD(char *const bits) {
    ::memcpy(&header, bits, sizeof(header));
    performCRCCheck();

    // Determine type of message based on address
    switch(bits[0]) {
    case 'a':
        (void) ::new(this) X25(bits); break;
    case 'b':
        (void) ::new(this) EIN(bits); break;
    default:
        // error("invalid message"); break;
        ;
    }
}

int main() {
	LAPD *m, *n, *o, *p;
	m = new LAPD("abcdefg");
	n = new LAPD("badfljk;adsflkj;asldf");
	delete n;
	n = new LAPD("aadflkj;sadf");
	o = new LAPD("aad;sflkj;lsdf");
	p = new LAPD("bb");
	delete p;
	delete m;
	delete n;
	delete o;
}
