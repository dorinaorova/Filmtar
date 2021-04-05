#include <iostream>
#include <stdlib.h>
#include <string>
#include <limits>
#include "filmlista.h"
#include "test.hpp"
#include "memtrace.h"

#ifndef CPORTA
///HIBAKEZELES--------------------------
//ADATOK BEKERESE - HIBAKEZELES
void ujadat (int& adat, std::string szoveg){
        bool joadat;
        do{
            joadat = true;
            std::cout<<szoveg;
            std::cin>>adat;
            if(std::cin.fail() || adat<0){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Hibas adat"<<std::endl;
                    joadat=false;
            }
        }while(!joadat);
}
//ROSSZ MENUPONT HIBAKEZELES
void rosszmenu(size_t& x, size_t max, std::string szoveg){
    do{
        std::cout<<szoveg<<std::endl;
        std::cin>>x;
        if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                x=-1;
            }
        if(x>max || x==0) std::cout<<"Nincs ilyen menupont!"<<std::endl;
    }while(x>max || x==0);
}

///MENUPONTOK---------------------------
// 1 - FILE OLVASAS
void fileolvasas(FilmLista& lista){
    std::cout << "Filmek beolvasasa file-bol"<<std::endl<<"Adja meg a file nevet: ";
    std::string filenev;
    std::cin.ignore();
    std::getline(std::cin, filenev);
    lista.file_olvas(filenev);
}
// 2 - FILMEK LISTAZASA
void listazas(FilmLista& lista){
    size_t x;
        if(lista.getDb()==0){
                std::cout<<"Nincs egy film sem"<<std::endl;
                rosszmenu(x, 1, "1. Vissza a fomenube");
        }
        else{
            do{
                lista.kiiras(std::cout);
                rosszmenu(x, 4, "\n1. Cim szerinti rendezes\n"
                                "2. Hossz szerinti rendezes\n"
                                "3. Megjelenes datuma szerinti rendezes\n"
                                "4. Vissza a fomenube" );
                lista.rendezes(x);
            }while(x!=4);
        }
}
// 3 - FILEBA IRAS
void fileiras(FilmLista& lista){
    size_t x;
    if(!lista.file_ir()){
        std::cout<<"Nincs egy film sem, nem kerulne semmi a fileba!"<<std::endl;
        rosszmenu(x, 1, "1. Vissza a fomenube");
    }
    else{
        std::cout<<"Sikeres a file irasa"<<std::endl;
        rosszmenu(x, 1, "1. Vissza a fomenube");
    }
}
// 4 - UJ FILM
void ujfilm_felvetel(FilmLista& lista){
size_t t;
    do{
        std::string cim;
        int hossz;
        int ev;
        int korhat;
        std::string leir;
        rosszmenu(t, 4, "1. Csaladi film\n"
                        "2. Dokumentum film\n"
                        "3. Egyeb\n"
                        "4. Megse - vissza a fomenube");

        if(t==4) break;
        std::cout<<"Adja meg a film cimet: ";
        std::cin.ignore();
        std::getline(std::cin, cim);

        ujadat(hossz, "Adja meg a film hosszat: ");
        ujadat(ev, "Adja meg a film megjelenesi evet: ");

        Film* uj;
        switch(t){
            case 1:
                ujadat(korhat, "Adja meg a film korhatarat: ");
                uj=new Csaladi(cim, hossz, ev, korhat);
                break;
            case 2:
                std::cout<<"Adja meg a film leirasat: ";
                std::cin.ignore();
                std::getline(std::cin, leir);
                uj=new Dokumentum(cim, hossz, ev, leir);
                break;
            case 3:
                uj=new Film(cim, hossz, ev);
                break;
        }

        lista.ujfilm(uj);
        rosszmenu(t, 2, "1. Uj film felvetele\n"
                        "2. Vissza a fomenube");
        }while(t!=2);
}
// 5 - KERESES
void kereses(FilmLista& lista){
    size_t t;
    if(lista.getDb()==0){
        std::cout<<"Nincs egy film sem"<<std::endl;
        rosszmenu(t, 1, "1. Vissza a fomenube");
    }
    else{
        do{
            std::string str;
            std::cout<<std::endl<<"Adja megy egy film cimet, vagy annak reszletet: ";
            std::cin.ignore();
            std::getline(std::cin, str);
            bool talalt=lista.keres(str);
            if(!talalt) std::cout<<"Nincs talalat"<<std::endl;
            rosszmenu(t, 2, "1. Uj filmre kereses\n"
                            "2. Vissza a fomenube");
        }while(t!=2);
    }
}

void menu(FilmLista& lista){
    size_t a;
        do{
            rosszmenu(a, 6,"1. Filmek beolvasasa file-bol\n"
                            "2. Osszes film listazasa\n"
                            "3. Osszes film kiirasa file-ba\n"
                            "4. Uj film felvetele\n"
                            "5. Kereses filmre\n"
                            "6. Kilepes - TESZTEK" );
            std::string str;
            switch (a){
                case 1: //file olvasás
                    fileolvasas(lista);
                    break;
                case 2: //filmek listazasa
                    std::cout << "Osszes film listazasa"<<std::endl;
                    listazas(lista);
                    break;
                case 3: //fileba iras
                    std::cout << "Osszes film kiirasa file-ba"<<std::endl;
                    fileiras(lista);
                    break;
                case 4: //uj film felvetele
                    std::cout << "Uj film felvetele"<<std::endl;
                    ujfilm_felvetel(lista);
                    break;
                case 5: //kereses
                    std::cout << "Kereses filmre"<<std::endl;
                    kereses(lista);
                    break;
            }
        }while(a!=6);
}
#endif

int main(){
    #ifndef CPORTA
    FilmLista l;
    menu(l);
    #endif
///TESZTEK
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();

    return 0;
}
