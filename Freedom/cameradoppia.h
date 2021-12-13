#ifndef CAMERADOPPIA_H
#define CAMERADOPPIA_H
#include "stanza.h"

class CameraDoppia : public Stanza
{
public:
    CameraDoppia(unsigned int =0, int =0, bool =1);
    virtual QString PostiDisponibili() const;
    virtual double CostoPrenotazione(int,int) const;
    virtual QString Nome() const;
};

#endif // CAMERADOPPIA_H
