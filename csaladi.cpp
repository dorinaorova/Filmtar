#include "csaladi.h"
#include <iostream>

#include "memtrace.h"

Csaladi::Csaladi(std::string cim, int hossz, int ev, int korhat) : Film(cim, hossz, ev), korhat(korhat) {}
int Csaladi::getKorhat() const {return korhat;}


std::ostream& Csaladi::kiir(std::ostream& os){
    os<<cim<<"\n "<<hossz<<" perc\n "<<ev<<"\n csaladi\n "<<korhat<<std::endl;
    return os;
}

