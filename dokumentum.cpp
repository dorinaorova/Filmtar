#include "dokumentum.h"
#include <iostream>

#include "memtrace.h"

Dokumentum::Dokumentum(std::string cim, int hossz, int ev, std::string leiras) :Film(cim, hossz, ev), leiras(leiras) {}
std::string Dokumentum::getLeiras() const {return leiras;}


std::ostream& Dokumentum::kiir(std::ostream& os){
    os<<cim<<"\n "<<hossz<<" perc\n "<<ev<<"\n dokumentum\n "<<leiras<<std::endl;
    return os;
}
