/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

class Telephone {
public:
    enum PhoneType { POTS, ISDN, OPERATOR, OTHER } phoneType()
        { return phoneTypeVal; }
    void ring();
    Bool isOnHook();
    Bool isTalking();
    Bool isDialing();
    DigitString collectDigits();
    LineNumber extension();  // not overridden below
    ~Telephone();
protected:
    LineNumber extensionData;
    PhoneType phoneTypeVal;
    Telephone();
};

.iX "\&\f4POTSPhone\fP\& (\*C class)" "and type selector fields"
class POTSPhone: public Telephone {
public:
    Bool runDiagnostics();
    POTSPhone(): phoneTypeVal(POTS) . . . .  {
        . . . .
    }
    POTSPhone(POTSPhone &p): phoneTypeVal(POTS) . . . .  {
        . . . .
    }
    ~POTSPhone();
private:
    Frame frameNumberVal;
    Rack rackNumberVal;
    Pair pairVal;
};

class ISDNPhone: public Telephone {
public:
    ISDNPhone(): phoneTypeVal(ISDN) . . . .   {  . . . .  }
    ISDNPhone(ISDNPhone &p): phoneTypeVal(ISDN) . . . . {
        . . . .
    }
    ~ISDNPhone();
    void sendBPacket();  // send a packet on the B channel
    void sendDPacket();  // send a packet on the D channel
private:
    Channel b1, b2, d;
};
