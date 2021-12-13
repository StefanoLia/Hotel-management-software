#include "stanza.h"
#include "cameradoppia.h"

Stanza::Stanza(unsigned int a, int b, bool c) : NumeroStanza(a), Piano(b), agibile(c) {}

void Stanza::SetStanzaAgibile(bool b)
{
    agibile = b;
}

double Stanza::TassaDiSoggiorno = 2.0;

unsigned int Stanza::GetPiano() const
{
    return Piano;
}

unsigned int Stanza::GetNum() const
{
    return NumeroStanza;
}

bool Stanza::GetStanzaInagibile() const
{
    return agibile;
}

bool Stanza::operator !=(const Stanza& s) const
{
    return (Piano != s.Piano || NumeroStanza != s.NumeroStanza || agibile != s.agibile);
}

bool Stanza::operator ==(const Stanza& s) const
{
    return (Piano == s.Piano && NumeroStanza == s.NumeroStanza && agibile == s.agibile);
}

void Stanza::Stampa() const
{
    cout << "Piano: " << Piano << std::endl;
    cout << "Numero Stanza: " << NumeroStanza << std::endl;
    //cout << "Posti Disponibili: " << PostiDisponibili() << std::endl;
}

double Stanza::GetTassa() const
{
    return TassaDiSoggiorno;
}

ostream& operator<<(ostream& os, const Stanza& s)
{
    s.Stampa();
    return os;
}
