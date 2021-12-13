#ifndef MONOLOCALE_H
#define MONOLOCALE_H
#include "stanza.h"

class CameraSingola : public Stanza
{
public:
    CameraSingola(unsigned int =0, int =0, bool =1);
    virtual double CostoPrenotazione(int,int) const;
    virtual QString PostiDisponibili() const;
    virtual QString Nome() const;
};

#endif // MONOLOCALE_H
