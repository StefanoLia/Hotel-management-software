#ifndef ROYALSUITE_H
#define ROYALSUITE_H
#include "suite.h"

class RoyalSuite : public Suite
{
public:
    RoyalSuite(unsigned int =0, unsigned int =0, bool =1);
    virtual double CostoPrenotazione(int,int) const;
    virtual QString Nome() const;
};

#endif // ROYALSUITE_H
