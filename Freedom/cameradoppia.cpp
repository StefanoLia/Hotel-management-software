#include "cameradoppia.h"

CameraDoppia::CameraDoppia(unsigned int a, int b, bool c) : Stanza(a,b,c) {}

double CameraDoppia::CostoPrenotazione(int num,int giorni) const
{
    return (90.0*giorni) + (GetTassa()*giorni)*num;
}

QString CameraDoppia::PostiDisponibili() const
{
    return "2  piu' un eventuale bambino";
}

QString CameraDoppia::Nome() const
{
    return "Camera Doppia";
}
