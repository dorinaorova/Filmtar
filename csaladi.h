#ifndef CSALADI_H_INCLUDED
#define CSALADI_H_INCLUDED

#include <string>
#include "film.h"
#include "memtrace.h"

class Csaladi : public Film{
    int korhat;
public:
    Csaladi(std::string cim="nincs", int hossz=0, int ev=0, int korhat =0) ;
    int getKorhat() const;
    std::ostream& kiir(std::ostream& os);
};

#endif // CSALADI_H_INCLUDED
