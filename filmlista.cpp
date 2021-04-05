#include "filmlista.h"
#include "memtrace.h"

//konstruktor
FilmLista::FilmLista(int db) : db(db), Lista(new Film*[db]) {};
//destruktor
FilmLista::~FilmLista(){
    for(int i=0; i<db; i++) delete Lista[i];
    delete[] Lista;
}
//másoló konstruktor
FilmLista::FilmLista(const FilmLista& a) : FilmLista(a.getDb()){
    if(db>0){
        *Lista=*a.Lista;
    }
}

int FilmLista::getDb() const {return db;}

Film* FilmLista::operator[](int i) { return Lista[i];}
const Film* FilmLista::operator[](int i) const { return Lista[i];}

void FilmLista::ujfilm(Film* ujfilm){
    Film** ujlista=new Film*[db+1];
    for(int i=0; i<db; i++){
        ujlista[i]=Lista[i];
    }
    ujlista[db]= ujfilm;
    delete[] Lista;
    Lista=ujlista;
    ++db;
}

void FilmLista::file_olvas(std::string filenev){
    Film* uj;
    int cnt=0;
    std::ifstream f;
    try{
            f.open(filenev);
            if(f.fail()){
                    std::cout<<"Nincs ilyen file, nem sikerult a filmek beolvasasa!\n";
                    throw "HIBA";
            }
        }
        catch(...){
            f.close();
            return;
        }
        while(f.peek()!=EOF){
                std::string cim;
                std::string leiras;
                unsigned int hossz;
                unsigned int ev;
                char tipus;
                unsigned int korhat;

            if(cnt>0) f.ignore();
            cnt++;
            std::getline(f, cim);
            f>>hossz;
            f>>ev;
            f>>tipus;

            switch(tipus){
                case 'd':
                    f.ignore();
                    std::getline(f, leiras);
                    uj=new Dokumentum(cim, hossz, ev, leiras);
                    ujfilm(uj);
                    cnt=0;
                    break;
                case 'c':
                    f>>korhat;
                    uj=new Csaladi(cim, hossz, ev, korhat);
                    ujfilm(uj);
                    break;
                case 'e':
                    uj=new Film(cim, hossz, ev);
                    ujfilm(uj);
                    break;
            }
        }
    f.close();
}

bool FilmLista::file_ir() const{
    if(db==0) return false;
    std::ofstream f;
    try{
        f.open("filmlista.txt");
        if(f.fail()){
            std::cout<<"Nem sikerült megnyitni"<<std::endl;
            throw "HIBA";
            return false;
        }
    }
    catch(...){
        f.close();
        return false;
    }
    kiiras(f);
    f.close();
    return true;
}

void FilmLista::rendezes(int a){
    bool x;
    for(int i=0; i<db; i++){
        for(int j=i+1; j<db; j++){
            switch(a){
            case 1:
                x=cmp(Lista[i]->getCim(), Lista[j]->getCim());
                break;
            case 2:
                x=cmp(Lista[i]->getHossz(), Lista[j]->getHossz());
                break;
            case 3:
                x=cmp(Lista[i]->getEv(), Lista[j]->getEv());
                break;
                }
            if(x){
                Film* csere=Lista[i];
                Lista[i]=Lista[j];
                Lista[j]=csere;
            }
        }
    }
}

std::ostream& FilmLista::kiiras(std::ostream& os) const{
    for(int i=0; i<db; i++){
        Lista[i]->kiir(os);
    }
    return os;
}

bool FilmLista::keres(std::string mit) const {
    bool talalt=false;
    for(size_t k=0; k<mit.length(); k++){
        mit[k]=tolower(mit[k]);
    }
    for(int i=0; i<db; i++){
        std::string cim = Lista[i]->getCim();
        for(size_t k=0; k<cim.length(); k++){
            cim[k]=tolower(cim[k]);
        }
        if(cim.find(mit)!=std::string::npos){
                Lista[i]->kiir(std::cout);
                talalt=true;
        }
    }
    return talalt;
}

