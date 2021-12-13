#include "hotel.h"
#include "suite.h"
#include "cameradoppia.h"
#include "royalsuite.h"
#include "camerasingola.h"
#include <QFile>
#include <QTextStream>

Hotel::Hotel(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f) :
    stanze(a,vector<Stanza*>(b,0)), piani(a), stanzePiano(b),
    Nsuite(c), Nroyalsuite(d), Ncameredoppie(e), Nmonolocale(f) //4,10,10,4,16,10
{
    QFile myfile ("inputstanze.txt");
    if(!myfile.exists()){
        std::cout << "Problema con il file" << std::endl;
    }
    if(myfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&myfile);
        unsigned int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
        for(unsigned int i = 0; i < a; i++)//vari piani
            {
                for(unsigned int j = 0; j < b; j++)//varie stanze
                {
                    int e,f,g;
                    in >> e >> f >> g;
                    if(c1 < Nmonolocale)//10
                    {
                        stanze[i][j] = new CameraSingola(f,e,g);
                        c1++;
                    }
                    else if(c2 < Ncameredoppie)//16
                    {
                        stanze[i][j] = new CameraDoppia(f,e,g);
                        c2++;
                    }
                    else if(c3 < Nsuite)//10
                    {
                        stanze[i][j] = new Suite(f,e,g);
                        c3++;
                    }
                    else if(c4 < Nroyalsuite)// 4
                    {
                        stanze[i][j] = new RoyalSuite(f,e,g);
                        c4++;
                    }
                }
            }
    }
    myfile.close();

}

Stanza* Hotel::GetStanza(int piano, int numero) const
{
    piano--; numero--;
    return stanze[piano][numero];
}

Hotel::~Hotel()
{
    for(unsigned int i=0; i<piani; i++)
    {
        for(unsigned int j=0; j<stanzePiano; j++)
            delete stanze[i][j];
    }
}

unsigned int Hotel::GetPiani() const
{
    return piani;
}

unsigned int Hotel::GetStanze() const
{
    return stanzePiano;
}

ostream& operator<<(ostream& os, const Hotel& H)
{
    for(vector<vector<Stanza*> >::size_type i = 0; i < H.stanze.size(); i++)
    {
        for(vector<int>::size_type j = 0; j < H.stanze[i].size(); j++)
        {
            os << j << ") " << *H.stanze[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
