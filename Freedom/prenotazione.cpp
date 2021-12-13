#include "prenotazione.h"

Prenotazione::Prenotazione(const QString& s,const QDate& a, const QDate& b, unsigned int c) : nome(s), inizio(a),
    fine(b), NumPersone(c) {}

QDate Prenotazione::getInizio() const
{
    return inizio;
}

QDate Prenotazione::getFine() const
{
    return fine;
}

bool Prenotazione::operator ==(const Prenotazione& p) const
{
    return (inizio == p.inizio && fine == p.fine);
}

bool Prenotazione::operator!=(const Prenotazione& p) const
{
    return (inizio != p.inizio || fine != p.fine);
}

QString Prenotazione::GetNome() const
{
    return nome;
}

unsigned int Prenotazione::GetNumPersone() const
{
    return NumPersone;
}

QTextStream& operator<<(QTextStream& out, const Prenotazione& p)
{
    out << p.nome << " " << "$" << "\n";
    out << p.inizio.day() << " " << p.inizio.month() << " " << p.inizio.year() << "\n";
    out << p.fine.day() << " " << p.fine.month() << " " << p.fine.year() << "\n";
    out << p.NumPersone << "\n";
    return out;
}

QTextStream& operator>>(QTextStream& in, Prenotazione& p)
{
    QString cliente, str;
    int c,d,e,f,g,h,i;
    while(!str.endsWith('$') && !in.atEnd())
    {
        in >> str;
        if(str != "$")
        {
            cliente=cliente+str;
            cliente=cliente + " ";
        }
    }
    in >> c >> d >> e;//prima data
    in >> f >> g >> h;//seconda data
    in >> i;
    QDate d1(e,d,c);
    QDate d2(h,g,f);
    p.nome = cliente;
    p.inizio = d1;
    p.fine = d2;
    p.NumPersone = i;
    return in;
}
