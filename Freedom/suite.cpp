#include "suite.h"

Suite::Suite(unsigned int a, int b, bool c) : Stanza(a,b,c) {}

int Suite::sconto = 6;

QString Suite::PostiDisponibili() const
{
    return "4";
}

double Suite::CostoPrenotazione(int num, int giorni) const
{
    return (130.0*giorni) + (GetTassa()*giorni)*num - (HasSconto(giorni) ? ((130*20)/100) : 0);
}

QString Suite::Nome() const
{
    return "Suite";
}

bool Suite::HasSconto(int a) const
{
    return sconto<=a;
}
