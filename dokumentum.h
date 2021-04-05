#ifndef DOKUMENTUM_H_INCLUDED
#define DOKUMENTUM_H_INCLUDED

#include "film.h"
#include <string>
#include "memtrace.h"

class Dokumentum : public Film{
    std::string leiras;
public:
    Dokumentum(std::string cim="nincs",  int hossz=0,  int ev=0, std::string leiras ="nincs leiras") ;
    std::string getLeiras() const;
    std::ostream& kiir(std::ostream& os);
};

#endif // DOKUMENTUM_H_INCLUDED
