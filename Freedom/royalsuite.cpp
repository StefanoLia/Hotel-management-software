#include "royalsuite.h"

RoyalSuite::RoyalSuite(unsigned int a, unsigned int b, bool c) : Suite(a,b,c) {}

double RoyalSuite::CostoPrenotazione(int num, int giorni) const
{
    return (200.0*giorni) + (GetTassa()*giorni)*num - (HasSconto(giorni) ? (200*20)/100 : 0);
}

QString RoyalSuite::Nome() const
{
    return "Royal Suite";
}
