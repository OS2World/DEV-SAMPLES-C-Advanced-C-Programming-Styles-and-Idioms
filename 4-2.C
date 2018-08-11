/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

enum Bool {true, false} ;

class Telephone {
public:
    void ring();
    Bool isOnHook();
    Bool isTalking();
    Bool isDialing();
    DigitString collectDigits();
    LineNumber extension();
    ~Telephone();
protected:
    LineNumber extensionData;
    Telephone();
};

// POTS is Plain Ordinary Telephone Service

class POTSPhone: public Telephone {
public:
    Bool runDiagnostics();
    POTSPhone();
    POTSPhone(POTSPhone&);
    ~POTSPhone();
private:
    // these are details of the phone's wiring
    // connections in the telephone office
    Frame frameNumberVal;
    Rack rackNumberVal;
    Pair pairVal;
};

// ISDN is Integrated Services Digital Network

class ISDNPhone: public Telephone {
public:
    ISDNPhone();
    ISDNPhone(ISDNPhone&);
    ~ISDNPhone();
    void sendBPacket();
    void sendDPacket();
private:
    Channel b1, b2, d;
};

class PrincessPhone: public POTSPhone {
    . . . .
};
