#ifndef FILM_H_INCLUDED
#define FILM_H_INCLUDED

#include <string>
#include "memtrace.h"

class Film{
protected:
    std::string cim;
    int hossz; //hossz percben
    int ev; //kiadás éve
public:
    Film(std::string ci="nincs",  int hossz = 0,  int ev =0);
    std::string getCim() const;
    int getHossz() const;
    int getEv() const;
    virtual std::ostream& kiir(std::ostream& os) ;
    virtual ~Film(){}
    };

#endif // FILM_H_INCLUDED
