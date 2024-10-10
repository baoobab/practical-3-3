#ifndef POLYNOM_H
#define POLYNOM_H

#include <number.h>
#include <array.h>

enum EPrintMode {
    EPrintModeClassic,
    EPrintModeCanonical
};

class TPolynom {
private:
    EPrintMode printMode;

    number canonicCoef;
    TArray* arrCoef;
    TArray* arrRoot;
public:
    TPolynom(number canonicCoef = 1);
    ~TPolynom();
    void addCoef(number coef);
    void addRoot(number root);
    void flushMemory();
    void setPrintMode(EPrintMode mode);
    void setCanonicCoef(number coef);
    number value(number val);
    friend ostream& operator<<(ostream&, TPolynom&);
    void calcCoefFromRoots();
};

#endif // POLYNOM_H
