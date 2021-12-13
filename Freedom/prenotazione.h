#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#include <QDate>
#include <QString>
#include <QTextStream>

class Prenotazione
{
private:
    QString nome;
    QDate inizio;
    QDate fine;
    unsigned int NumPersone;
public:
    Prenotazione(const QString& = QString(),const QDate& = QDate(1,1,0), const QDate& = QDate(1,1,0), unsigned int =0);
    QDate getInizio() const;
    QDate getFine() const;
    bool operator==(const Prenotazione&) const;
    bool operator!=(const Prenotazione&) const;
    QString GetNome() const;
    unsigned int GetNumPersone() const;
    friend QTextStream& operator<<(QTextStream&, const Prenotazione&);
    friend QTextStream& operator>>(QTextStream&, Prenotazione&);
};

#endif // PRENOTAZIONE_H
