#include "contenitore.h"
#include <QFile>
#include <QTextStream>
#include <fstream>

//COSTRUTTORI NODO

Contenitore::nodo::nodo(Stanza* s,const Prenotazione& a, const smartP& p) : punt(s), riferimenti(0),
    prenot(a), next(p) {}

//COSTRUTTORI DI SMARTP

Contenitore::smartP::smartP(nodo* s) : n(s)
{
    if(n)
        n->riferimenti++;
}

Contenitore::smartP::smartP(const smartP& s) : n(s.n)
{
    if(n)
        n->riferimenti++;
}

Contenitore::smartP::~smartP()
{
    if(n)
    {
        n->riferimenti--;
        if(n->riferimenti==0)
            delete n;//chiamata ricorsiva
    }
}

//OPERATORI DI SMARTP

bool Contenitore::smartP::operator != (const smartP& s) const
{
    return (n != s.n);
}

bool Contenitore::smartP::operator ==(const smartP& s) const
{
    return (n == s.n);
}

Contenitore::smartP& Contenitore::smartP::operator =(const smartP& s)
{
    if(this != &s)
    {
        nodo*t = n;
        //t->riferimenti++
        //n->riferimenti--
        n = s.n;
        if(n)
            n->riferimenti++;
        if(t)
        {
            t->riferimenti--;
            if(t->riferimenti==0)
                delete t;
        }
    }
    return *this;
}

Contenitore::nodo& Contenitore::smartP::operator*() const
{
    return *n;
}

Contenitore::nodo* Contenitore::smartP::operator->()const
{
    return n;
}

//METODI CONTENITORE

bool Contenitore::iteratore::operator ==(const iteratore& i) const
{
    return s == i.s;
}

bool Contenitore::iteratore::operator !=(const iteratore& i) const
{
    return s != i.s;
}

Contenitore::iteratore Contenitore::iteratore::operator ++(int)
{
    iteratore aux = *this;
    if(s != 0)
        s = s->next;
    return aux;
}


//COSTRUTTORI DI CONTENITORE

Contenitore::Contenitore() : first(0) {}

Contenitore::Contenitore(Hotel* h) : H(h)
{
    LoadReservations();// legge dal file le prenotazioni e le aggiunge
}


//PUBBLICI

Contenitore::iteratore Contenitore::begin() const
{
    iteratore aux;
    aux.s = first;
    return aux;
}

Contenitore::iteratore Contenitore::end() const
{
    iteratore aux;
    aux.s = 0;
    return aux;
}

const Stanza* Contenitore::GetS(const Contenitore::iteratore& it) const
{
    return it.s->punt;
}

const Prenotazione& Contenitore::GetP(const Contenitore::iteratore& it) const
{
    return it.s->prenot;
}

Stanza* Contenitore::GetS(const Contenitore::iteratore& it)
{
    return it.s->punt;
}

Prenotazione& Contenitore::GetP(const Contenitore::iteratore& it)
{
    return it.s->prenot;
}


bool Contenitore::Aggiungi_prenotazione(Stanza *s, const Prenotazione& p1)
{
        if(!VerificaDisponibilita(s,p1))
            return 0;
        else
        {
            first = new nodo(s,p1,first);
            return 1;
        }
        return 0;
}

void Contenitore::sort() //ordina la lista a seconda della data di inizio (ordine crescente)
{
    smartP y, temp, z = first,start,temp2;
    while(z != 0)
    {
        y = z;
        QDate d(3000,12,30);
        while(y != 0)
        {
            if(y->prenot.getInizio() < d)
            {
                d = y->prenot.getInizio();
                temp = y;
            }
            else if(y->prenot.getInizio() == d)
            {
                if(y->prenot.getFine() < temp->prenot.getFine())
                    temp = y;
            }
            y=y->next;
        }
        if(start == 0)
        {
            start = new nodo(temp->punt, temp->prenot);
            temp2 = start;
        }
        else
        {
            temp2->next = new nodo(temp->punt, temp->prenot);
            temp2 = temp2->next;
        }
        Togli_prenotazione(temp->punt, temp->prenot);
        z = first;
    }
    first = start;
}

void Contenitore::Togli_prenotazione(Stanza *s, const Prenotazione& p1)
{
    smartP p = first, prec, q;
    smartP original = first;
    first = 0;
    while(p != 0)
    {
        q = new nodo(p->punt,p->prenot);
        if(p->prenot == p1 && *p->punt == *s)
            break;
        if(prec == 0)
           first = q;
        else
           prec->next = q;
        prec = q;
        p = p->next;
    }
    if(p == 0)//prenotazione non trovata
    {
        first = original;
        std::cerr << "Prenotazione non trovata" << std::endl;
    }
    else if(prec == 0)//prenotazione in testa
    {
        if(p->prenot == p1 && *p->punt == *s)
            first = p->next;
        else
        {
            first = original;
            std::cerr << "Stanza non prenotata per questa data" << std::endl;
        }
    }
    else
        prec->next = p->next; // unisco al resto della lista
}

void Contenitore::Aggiorna()//aggiorna la lista
{
    smartP p = first;
    while(p != 0)
    {
        if(p->prenot.getFine() < QDate::currentDate())//se la data corrente supera la fine della prenotazione
            Togli_prenotazione(first->punt,p->prenot);
        p = p->next;
    }
}

bool Contenitore::VerificaDisponibilita(Stanza* s, const Prenotazione& p1) const
{
    smartP p = first;
    if(p == 0)
        return 1;
    while(p != 0)
    {
        if(s == p->punt && !(p1.getInizio() >= p->prenot.getFine() || p1.getFine() <= p->prenot.getInizio()))
            return 0;
        p = p->next;
    }
    return 1;
}

bool Contenitore::WriteReservations() const
{
    smartP p = first;
    QFile myfile ("outputPrenotazioni.txt");
    if(!myfile.exists())
    {
        std::cout << "Problemi con il file" << std::endl;
        return 0;
    }
    if(myfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&myfile);
        while(p != 0)
        {
            out << p->prenot;
            out << p->punt->GetPiano() << " " << p->punt->GetNum() << "\n";
            p = p->next;
        }
        out.flush();
    }
    myfile.close();
    return 1;
}

void Contenitore::LoadReservations()
{
    QFile myfile ("outputPrenotazioni.txt");
    if(!myfile.exists())
        std::cout << "Problema con il file" << std::endl;
    if(myfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&myfile);
        while(!in.atEnd())
        {
            int a,b;
            Prenotazione p;
            in >> p;
            in >> a >> b;
            if(a != 0 && b != 0)
                first = new nodo(H->GetStanza(a,b),p,first);
        }
    }
    myfile.close();
}

int Contenitore::CountReservations() const // conta le prenotazioni
{
    smartP p = first;
    int cont = 0;
    while(p != 0)
    {
        cont++;
        p = p->next;
    }
    return cont;
}

void Contenitore::RemoveEv()
{
    smartP p = first;
    while(p != 0)
    {
        Togli_prenotazione(p->punt,p->prenot);
        p = p->next;
    }
}

bool Contenitore::Vuota() const
{
    return first == 0;
}

void Contenitore::WriteUnusableRoom() const
{
    QFile myfile ("inputstanze.txt");
    if(!myfile.exists())
        std::cout << "Problema con il file" << std::endl;
    myfile.open(QIODevice::WriteOnly);
    QTextStream out(&myfile);
    if(myfile.isOpen())
    {
        for(unsigned int piano = 1; piano <= H->GetPiani(); piano++)
        {
            for(unsigned int numero = 1; numero <= H->GetStanze(); numero++)
                out << piano << " " << numero << " " << H->GetStanza(piano,numero)->GetStanzaInagibile() <<"\n";
        }
    }
    out.flush();
    myfile.close();
}

bool Contenitore::Controlla(int piano, int stanza) const//controlla che la stanza che si vuole rendere
//inagibile non sia già nella lista prenotazioni, se ciò dovesse accadere ritorna 1
{
    smartP p = first;
    while(p != 0)
    {
        if(*p->punt == *H->GetStanza(piano,stanza))// ha trovato la stanza
            return 1;
        p = p->next;
    }
    //non l'ha trovata
    return 0;
}

