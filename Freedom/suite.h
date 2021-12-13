#ifndef SUITE_H
#define SUITE_H
#include "stanza.h"

class Suite : public Stanza
{
private:
    static int sconto;//rappresenta il numero dei giorni di prenotazione per i quali
                      //si effettua uno sconto del 20%
public:
    Suite(unsigned int =0, int =0, bool =1);
    virtual QString PostiDisponibili() const;
    virtual double CostoPrenotazione(int,int) const;
    virtual QString Nome() const;
    bool HasSconto(int) const;
};

#endif // SUITE_H
