#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include "filmlista.h"
#include "gtest_lite.h"
#include "memtrace.h"

void test_1(){
    TEST(test11,def_konstr){
        Film film;
        Dokumentum dok;
        Csaladi csal;
        EXPECT_EQ(0,film.getEv())<< "HIBA" << std::endl;
        EXPECT_EQ(0,dok.getHossz())<< "HIBA" << std::endl;
        EXPECT_EQ(0,csal.getKorhat())<< "HIBA" << std::endl;
    }
    END

    TEST(test12,konstr){
        Film film("cim", 90, 2000);
        Dokumentum dok("cim", 90, 2000, "leiras");
        Csaladi csal("cim", 90, 2000, 12);
        EXPECT_EQ("cim",film.getCim())<< "HIBA" << std::endl;
        EXPECT_EQ("leiras",dok.getLeiras())<< "HIBA" << std::endl;
        EXPECT_EQ(12,csal.getKorhat())<< "HIBA" << std::endl;
    }
    END
}
void test_2(){
    TEST(test2,filmlista_uj film felvetele){
        FilmLista lista;
        EXPECT_EQ(0,lista.getDb())<< "HIBA" << std::endl;
        Film *f = new Film();
        lista.ujfilm(f);
        EXPECT_EQ(1,lista.getDb())<< "HIBA" << std::endl;
    }
    END
}
void test_3(){
    TEST(test3, fileolvasas){
        FilmLista lista;
        EXPECT_NO_THROW(lista.file_olvas("filmek.txt")) <<"Hiba a file megnyitasakor"<<std::endl;
        EXPECT_NE(0,lista.getDb())<<"Hiba az adatok beolvasakor"<<std::endl;
    }
    END
}
void test_4(){
    TEST(test41,feliras_ureslista){
        FilmLista lista;
        EXPECT_FALSE(lista.file_ir())<<"Megis van film, amit ki lehetne irni"<<std::endl;
    }
    END
    TEST(test42, fileiras_nemureslista){
        FilmLista lista;
        Film *f = new Film();
        lista.ujfilm(f);
        EXPECT_NO_THROW(lista.file_ir()) <<"Hiba a file megnyitasakor"<<std::endl;
        EXPECT_TRUE(lista.file_ir()) <<"Nincs film amit fileba lehetne irni"<<std::endl;
    }
    END
}
void test_5(){
    TEST(test51,kiiras_film){
        Film f("film_cim", 90, 2000);
        std::stringstream ss;
        f.kiir(ss);
        EXPECT_STREQ("film_cim\n 90 perc\n 2000\n egyeb\n", ss.str().c_str())<<"Nem jo a kiiro fuggveny - Film"<<std::endl;
    }
    END
    TEST(test52,kiiras_csaladi){
        Csaladi cs("csal_cim", 90, 2000, 12);
        std::stringstream ss;
        cs.kiir(ss);
        EXPECT_STREQ("csal_cim\n 90 perc\n 2000\n csaladi\n 12\n", ss.str().c_str())<<"Nem jo a kiiro fuggveny - Dokumentum"<<std::endl;
    }
    END
    TEST(test53,kiiras_dok){
        Dokumentum d("dok_cim", 90, 2000, "leiras");
        std::stringstream ss;
        d.kiir(ss);
        EXPECT_STREQ("dok_cim\n 90 perc\n 2000\n dokumentum\n leiras\n", ss.str().c_str())<<"Nem jo a kiiro fuggveny - Csaladi"<<std::endl;
    }
    END
    TEST(test54, kiiras_lista){
        FilmLista lista;
        Film *f1=new Film("film_cim", 90, 2000);
        Film *f2 = new Dokumentum("dok_cim", 100, 2001, "leiras");
        Film *f3 = new Csaladi("csal_cim", 110, 2002, 12);
        lista.ujfilm(f1);
        lista.ujfilm(f2);
        lista.ujfilm(f3);
        std::stringstream ss;
        lista.kiiras(ss);
        EXPECT_STREQ("film_cim\n 90 perc\n 2000\n egyeb\ndok_cim\n 100 perc\n 2001\n dokumentum\n leiras\ncsal_cim\n 110 perc\n 2002\n csaladi\n 12\n", ss.str().c_str())<<"Nem jo a kiiro fv - FilmLista"<<std::endl;
    }
    END
}
void test_6(){
    TEST(test61, keres_ureslista){
        FilmLista lista;
        EXPECT_FALSE(lista.keres("barmi"))<<"Hiba kereso fuggvenyben"<<std::endl;
    }
    END
    TEST(test62, keres_nemureslista){
        FilmLista lista;
        Film *f1= new Film("kisbetuscim", 90, 2000);
        lista.ujfilm(f1);
        EXPECT_TRUE (lista.keres("kisbetuscim"))<<"Hiba kereso fuggvenyben - egesz cimre kereses"<<std::endl;
        EXPECT_FALSE(lista.keres("ilyencimnincs"))<<"Hiba kereso fuggvenyben - nem letezo cimre van talalat"<<std::endl;
        EXPECT_TRUE(lista.keres("cim"))<<"Hiba kereso fuggvenyben - cim egy reszere kereses"<<std::endl;
        Film *f2=new Film("NAGYBETUSCIM", 90, 2000);
        lista.ujfilm(f2);
        EXPECT_TRUE(lista.keres("nagybetus"))<<"Hiba kereso fuggvenyben - kisbetus kereses nagybetus cimre"<<std::endl;
        EXPECT_TRUE(lista.keres("KISBETUS"))<<"Hiba kereso fuggvenyben - nagybetus kereses kisbetus cimre"<<std::endl;
    }
    END
}
void test_7(){
    TEST(test71, rendezes_cim){
        Film *f1=new Film("C", 90, 2000);
        Film *f2=new Dokumentum("A", 110, 2008, "dokumentumfilm leiras");
        Film *f3=new Csaladi("B", 87, 2003, 12);
        FilmLista lista;
        lista.ujfilm(f1);
        lista.ujfilm(f2);
        lista.ujfilm(f3);
        lista.rendezes(1);
        EXPECT_EQ("A", lista[0]->getCim())<<"Hiba a rendezesben - cimek nincsenek sorban"<<std::endl;
        EXPECT_EQ("C", lista[2]->getCim())<<"Hiba a rendezesben - cimek nincsenek sorban"<<std::endl;
        EXPECT_EQ(2003, lista[1]->getEv())<<"Hiba a rendezesben - mas adatok nincsenek sorban"<<std::endl;
        EXPECT_EQ(110, lista[0]->getHossz())<<"Hiba a rendezesben - mas adatok nincsenek sorban"<<std::endl;
    }
    END
    TEST(test72, rendezes_hossz){
        Film *f1=new Film("C", 90, 2000);
        Film *f2=new Dokumentum("A", 110, 2008, "dokumentumfilm leiras");
        Film *f3=new Csaladi("B", 87, 2003, 12);
        FilmLista lista;
        lista.ujfilm(f1);
        lista.ujfilm(f2);
        lista.ujfilm(f3);
        lista.rendezes(2);
        EXPECT_EQ(87, lista[0]->getHossz())<<"Hiba a rendezesben - hossz nincs sorban"<<std::endl;
        EXPECT_EQ(110, lista[2]->getHossz())<<"Hiba a rendezesben - hossz nincs sorban"<<std::endl;
        EXPECT_EQ(2000, lista[1]->getEv())<<"Hiba a rendezesben - mas adatok nincsenek sorban"<<std::endl;
        EXPECT_EQ("B", lista[0]->getCim())<<"Hiba a rendezesben - mas adatok nincsenek sorban"<<std::endl;
    }
    END
    TEST(test73, rendezes_ev){
        Film *f1=new Film("C", 90, 2000);
        Film *f2=new Dokumentum("A", 110, 2008, "dokumentumfilm leiras");
        Film *f3=new Csaladi("B", 87, 2003, 12);
        FilmLista lista;
        lista.ujfilm(f1);
        lista.ujfilm(f2);
        lista.ujfilm(f3);
        lista.rendezes(3);
        EXPECT_EQ(2000, lista[0]->getEv())<<"Hiba a rendezesben - ev nincs sorban"<<std::endl;
        EXPECT_EQ(2008, lista[2]->getEv())<<"Hiba a rendezesben - ev nincs sorban"<<std::endl;
        EXPECT_EQ(110, lista[2]->getHossz())<<"Hiba a rendezesben - mas adatok nincsenek sorban"<<std::endl;
        EXPECT_EQ("C", lista[0]->getCim())<<"Hiba a rendezesben - mas adatok nincsenek sorban"<<std::endl;
    }
    END

}

#endif // TEST_HPP_INCLUDED
