#include "camerasingola.h"

CameraSingola::CameraSingola(unsigned int a, int b, bool c) : Stanza(a,b,c) {}

double CameraSingola::CostoPrenotazione(int num, int giorni) const
{
    return (60.0*giorni) + (GetTassa()*giorni)*num;
}

QString CameraSingola::PostiDisponibili() const
{
    return "1  piu' un eventuale bambino";
}

QString CameraSingola::Nome() const
{
    return "Camera Singola";
}
