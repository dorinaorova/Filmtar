#include <string>
#include "film.h"
#include <iostream>

#include "memtrace.h"

Film::Film(std::string cim, int hossz, int ev) : cim(cim), hossz(hossz), ev(ev) {}
std::string Film::getCim() const {return cim;}
int Film::getHossz() const {return hossz;}
int Film::getEv() const {return ev;}


std::ostream& Film::kiir(std::ostream& os){
    os<<cim<<"\n "<<hossz<<" perc\n "<<ev<<"\n egyeb"<<std::endl;
    return os;
};

