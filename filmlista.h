#ifndef FILMLISTA_H_INCLUDED
#define FILMLISTA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "dokumentum.h"
#include "csaladi.h"
#include "memtrace.h"

class FilmLista{
    int db;
    Film** Lista;
public:
    FilmLista(int db=0);
    FilmLista(const FilmLista& a);
    ~FilmLista();
    int getDb() const;
    Film* operator[](int i);
    const Film* operator[](int i) const;
    void ujfilm(Film* ujfilm);
    void file_olvas(std::string filenev);
    bool file_ir() const;
    void rendezes(int a);
    std::ostream& kiiras(std::ostream& os) const;
    bool keres(std::string mit)const ;
};

template<typename T>
bool cmp(T a, T b){
    return a>b? true:false;
}

#endif // FILMLISTA_H_INCLUDED
