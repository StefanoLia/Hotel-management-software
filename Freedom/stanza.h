#ifndef STANZA_H
#define STANZA_H
#include <iostream>
#include <string>
#include <QString>
using std::ostream; using std::cout; using std::string;

class Stanza//classe astratta
{
private:
    unsigned int NumeroStanza;
    int Piano;
    bool agibile;// true se agibile
    static double TassaDiSoggiorno;
public:
    Stanza(unsigned int =1, int =0, bool =1);
    virtual ~Stanza() {} // distruttore virtuale
    virtual QString PostiDisponibili() const =0;
    virtual double CostoPrenotazione(int,int) const =0;
    virtual QString Nome() const =0;
    virtual void Stampa() const;
    void SetStanzaAgibile(bool);
    bool GetStanzaInagibile() const; // ritorna agibile
    unsigned int GetPiano() const;
    unsigned int GetNum() const;
    friend ostream& operator<<(ostream& os, const Stanza& s);
    bool operator!=(const Stanza&) const;
    bool operator==(const Stanza&) const;
protected:
    double GetTassa() const;
};

#endif // STANZA_H
