#ifndef CONTENITORE_H
#define CONTENITORE_H
#include "stanza.h"
#include "prenotazione.h"
#include "hotel.h"
#include <QDate>
#include <QDataStream>
#include<QTextStream>
#include<iostream>
#include<QDebug>
using std::ostream;
class Prenotazione;

class Contenitore
{
    friend class iteratore;
private:
    class nodo;
    class smartP
    {
    public:
        nodo* n;
        smartP(nodo* =0);
        smartP(const smartP&);
        ~smartP();
        smartP& operator=(const smartP&);
        nodo* operator->() const;
        nodo& operator*() const;
        bool operator==(const smartP&) const;
        bool operator!=(const smartP&) const;
    };
    class nodo
    {
    public:
        Stanza*punt;
        int riferimenti;
        Prenotazione prenot;
        smartP next;
        nodo(Stanza* =0, const Prenotazione& = Prenotazione(), const smartP& =0);
    };
    smartP first;
    Hotel* H; // serve alla funzione LoadReservations
    void LoadReservations(); // ricaricare le prenotazioni all'avvio
public:
    class iteratore
    {
        friend class Contenitore;
    private:
        Contenitore::smartP s;
    public:
        bool operator==(const iteratore&) const;
        bool operator!=(const iteratore&) const;
        iteratore operator++(int); // postfisso
    };

    Contenitore();
    Contenitore(Hotel*);
    iteratore begin() const;
    iteratore end() const;
    const Stanza* GetS (const iteratore&) const;//iteratore costante
    const Prenotazione& GetP(const iteratore&) const;
    Stanza* GetS (const iteratore&);//metodo che permette le opportune modifiche
    Prenotazione& GetP(const iteratore&);

    bool Aggiungi_prenotazione(Stanza*, const Prenotazione&);
    void sort();//possibilità di ordinare la lista
    void Togli_prenotazione(Stanza*,const Prenotazione&); // togliere una prenotazione
    void Aggiorna(); // aggiornare la lista alla data corrente
    bool VerificaDisponibilita(Stanza*, const Prenotazione&) const; // vedere se la stanza richiesta è occupata
    bool WriteReservations() const; // salvare le prenotazioni
    int CountReservations() const; // necessità di contare le prenotazioni
    void RemoveEv(); // rimuovere tutto
    bool Vuota() const;
    void WriteUnusableRoom() const;
    bool Controlla(int, int) const;// controlla se non ci sono prenotazioni in quella stanza se questa
    //è inagibile
};

#endif // CONTENITORESTANZE_H
