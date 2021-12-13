#ifndef HOTEL_H
#define HOTEL_H
#include "stanza.h"
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;using std::ifstream;

class Hotel
{
private:
    vector<vector<Stanza*> > stanze;
    unsigned int piani;
    unsigned int stanzePiano;
    unsigned int Nsuite;
    unsigned int Nroyalsuite;
    unsigned int Ncameredoppie;
    unsigned int Nmonolocale;
public:
    Hotel(unsigned int =0, unsigned int =0, unsigned int =0, unsigned int =0, unsigned int =0, unsigned int =0);
    friend ostream& operator<<(ostream& os, const Hotel& H);
    Stanza* GetStanza(int,int) const;
    unsigned int GetPiani() const;
    unsigned int GetStanze() const;
    ~Hotel();
};

#endif // HOTEL_H
