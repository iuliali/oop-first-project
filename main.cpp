#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system ("clear");
#endif
}

class Carte{
public:
    Carte();
    Carte(string nume, string autor, int nr_pagini);
    friend istream& operator >> (istream& stream, Carte& carte);
    friend ostream& operator << (ostream& o, Carte carte);
    int operator+( vector<Carte>& carti);
    bool operator==( Carte& carte);
    void SetNumeCarte(string nume);
    void SetAutorCarte(string autor);
    string GetNume();
    string GetAutor();
    void SetNrPagini(int nr_pagini);
    int GetNrPagini();

private:
    int nr_pagini;
    string nume_carte;
    string autor;

};


class Utilizator{
public:

    Utilizator(string nume, string parola_user);
    Utilizator(const Utilizator& user);
    ~Utilizator();
    void SetNumeUtilizator(string nume_utilizator);
    string GetNumeUtilizator();
    void SetParola(string noua_parola);
    friend istream& operator >> (istream& stream, Utilizator& user);
    friend ostream& operator << (ostream& o, Utilizator user);
    bool operator==( Utilizator& user);
    bool operator!=( Utilizator& user);
    bool VerificareParola(string parola_introdusa);
    void SchimbaParola();
    bool PoateImprumutaCartea(Carte& carte);
    vector<Carte> carti_imprumutate;

private:
    string nume_utilizator;
    string parola;

};


class BibliotecaOnline{
public:
    BibliotecaOnline();
    BibliotecaOnline(string user_admin, string parola_admin);
    ~BibliotecaOnline();
    void BunVenit();
    void LogareCont();
    void CreareCont();
    Utilizator* ExistaNumeUser(string nume);
    void DateGresite();
    void IesireDinCont();
    void AdaugaCarte(string nume_carte, string autor, int nr_pagini);
    void StergeCarte(string nume_carte, string autor);
    void IntrareInCont(Utilizator& user);
    void AfisareCartiPentruImprumut();
    void ReturneazaCarte(Utilizator& user, int poz_in_lista);
    void StergeCont(Utilizator& user);
    void ImprumutaCarte(Utilizator& user);
    int GetNrCarti();
    int GetNrUtilizatori();
    friend istream& operator >> (istream& stream, BibliotecaOnline& biblio);
    friend ostream& operator << (ostream& o, const BibliotecaOnline& biblio);
    bool operator==( BibliotecaOnline& biblio);
    bool operator!=( BibliotecaOnline& biblio); // 2 biblioteci sunt egale daca au acelasi nr de carti
    BibliotecaOnline& operator+=( Carte& carte);// adauga o carte si returneaza biblioteca avand acea carte in plus
    BibliotecaOnline& operator-=( Carte& carte);//sterge o carte doar daca ea exista !!! daca nu exista in biblioteca, returneaza biblioteca nemodificata

private:
    vector<Utilizator> bd_utilizatori{};
    vector<Carte> bd_carti;


};


///--------------------------------------------------------------


///IMPLEMENTARE CARTE
//constructori initializare -- supraincarcare constructori initializare

Carte::Carte(string nume, string autor, int nr_pagini=100){
    this->nume_carte = nume;
    this->autor = autor;
    this->nr_pagini = nr_pagini;
}


//supraincarcare operatori citire si scriere
istream& operator >> (istream& stream, Carte& carte){
    int nr_pagini;
    string nume_carte, nume_autor;
    stream>> nume_carte>> nume_autor >> nr_pagini;
    carte.SetNumeCarte(nume_carte);
    carte.SetAutorCarte(nume_autor);
    carte.SetNrPagini(nr_pagini);
    return stream;
}

ostream& operator << (ostream& o, Carte carte){
    o<< carte.GetNume()<<" scrisa de "<< carte.GetAutor();
    return o;
}


//setteri si getteri pt datele membru private
void Carte::SetNumeCarte(string nume){
    this->nume_carte= nume;
}

void Carte::SetAutorCarte(string autor){
    this->autor= autor;
}

void Carte::SetNrPagini(int nr_pagini){
    this->nr_pagini= nr_pagini;
}

string Carte::GetNume(){
    return this->nume_carte;
}

string Carte::GetAutor(){
    return this->autor;
}

int Carte::GetNrPagini(){
    return this->nr_pagini;
}


//supraincarcarea operatorilor aritmetici binari
int Carte::operator+( vector<Carte>& carti){
    vector<Carte>::iterator p;
    int suma_pagini = 0;
    for(p=carti.begin();p<carti.end(); p++){
        suma_pagini += (*p).GetNrPagini();
    }
    suma_pagini += this->GetNrPagini();
    return suma_pagini;
}

//supraincarcarea operatorilor aritmetici relationali
bool Carte::operator==( Carte& carte){
    if(this->GetNume()== carte.GetNume())
        return true;
    else
        return false;
}

///--------------------------------------------------------------


///IMPLEMENTARE UTILIZATOR
//constructor

Utilizator::Utilizator(string nume="", string parola_user=""){
    this->nume_utilizator= nume;
    this->parola=parola_user;
    vector<Carte> carti_imprumutate={};
}


//constructor de copiere
Utilizator::Utilizator(const Utilizator& user){
    this->nume_utilizator= user.nume_utilizator;
    this->parola=user.parola;
    vector<Carte> carti_imprumutate={};
    int n = user.carti_imprumutate.size();
    for(int i = 0; i < n; i++){
        Carte book(user.carti_imprumutate[i]);
        this->carti_imprumutate.push_back(book);
    }


}

//destructor
Utilizator::~Utilizator(){
    carti_imprumutate.clear();
}

//setter si getteri - nu am facut pt parola ca sa nu poata fi accesata din afara clasei
void Utilizator::SetNumeUtilizator(string nume_utilizator){
    this->nume_utilizator = nume_utilizator;
}

void Utilizator::SetParola(string noua_parola){
    this->parola = noua_parola;
}

string Utilizator::GetNumeUtilizator(){



///supraincarcare operatori de citire si scriere
    return this->nume_utilizator;
}
//supraincarcarea operatorilor de citire si scriere
istream& operator >> (istream& stream, Utilizator& user){
    cout<<"Nume utilizator:"<<endl;
    stream>> user.nume_utilizator;
    cout<<"Parola:"<<endl;
    stream>>user.parola;
    stream.get();
    clear_screen();
    return stream;
}

ostream& operator << (ostream& o, Utilizator user){
    o<<"Nume utilizator: ";
    o<<user.GetNumeUtilizator()<<endl;
    o<<"Numar carti imprumutate : "<< user.carti_imprumutate.size()<<endl;
    vector<Carte>::iterator p;
    int k = 1;
    for(p=user.carti_imprumutate.begin();p<user.carti_imprumutate.end(); p++){
        o<<k<<" ";
        k++;
        o<< (*p);
        o<<endl;
    }


    return o;
}


//supraincarcarea operatorilor relationali
bool Utilizator::operator==( Utilizator& user){
    if (this->GetNumeUtilizator()==user.GetNumeUtilizator()){
        return true;
    }
    else
        return false;
}

bool Utilizator::operator!=( Utilizator& user){
    if (this->GetNumeUtilizator()!=user.GetNumeUtilizator()){
        return false;
    }
    else
        return true;
}


//functii membru publice
bool Utilizator::VerificareParola(string parola_introdusa){

    if (this->parola==parola_introdusa)
        return true;
    else
        return false;
}
void Utilizator::SchimbaParola(){
    string parola_noua;
    cout<<"Introduceti noua parola :"<<endl;
    cin>>parola_noua;
    this->SetParola(parola_noua);
    clear_screen();
    cout<< "Parola schimbata cu succes! "<<endl;

}

bool Utilizator::PoateImprumutaCartea(Carte& carte){
     vector<Carte>::iterator p;
     int nr_carti = this->carti_imprumutate.size();

     for(p = this->carti_imprumutate.begin(); p < this->carti_imprumutate.end(); p++){
        if((*p)==carte)
        {
            return false;
        }

    }

    ///vreau sa verific si cate carti si daca suma paginilor e mai mare decat 1000;
    if((nr_carti>=3) or (carte + this->carti_imprumutate >= 1000)){
        return false;
    }
    return true;


}
///--------------------------------------------------------------


///IMPLEMENTARE BIBLIOTECA ONLINE
//supraincarcarea constructorilor de initializare

BibliotecaOnline::BibliotecaOnline(){
    Utilizator admin("admin","admin123");
    this->bd_utilizatori.push_back(admin);

    Carte book1("Surely You're Joking, Mr. Feynman","Richard Feynman",400);
    this->bd_carti.push_back(book1);
    Carte book2("Care e diferenta intre un copil si un laptop?","Cristian Presura",284);
    this->bd_carti.push_back(book2);
    Carte book3("Cilka's Journey","Heather Morris",352);
    this->bd_carti.push_back(book3);
    Carte book4("Tatuatorul de la Auschwitz","Heather Morris",272);
    this->bd_carti.push_back(book4);
    Carte book5("Emma","Jane Austen",474);
    this->bd_carti.push_back(book5);
    Carte book6("1984","George Orwell",298);
    this->bd_carti.push_back(book6);
    Carte book7("Animal Farm","George Orwell",141);
    this->bd_carti.push_back(book7);
    Carte book8("Un veac de singuratate","Gabriel Garcia Marquez",480);
    this->bd_carti.push_back(book8);
    Carte book9("De veghe in lanul de secara","J.D.Salinger",280);
    this->bd_carti.push_back(book9);
    Carte book10("Anna Karenina","Lev Tolstoi",964);
    this->bd_carti.push_back(book10);

}

BibliotecaOnline::BibliotecaOnline(string user_admin, string parola_admin){

    Utilizator admin(user_admin,parola_admin);
    this->bd_utilizatori.push_back(admin);

}


//destructor
BibliotecaOnline::~BibliotecaOnline(){
    this->bd_carti.clear();
    this->bd_utilizatori.clear();
}


//getteri
int BibliotecaOnline::GetNrCarti(){
    int nr_carti = int(this->bd_carti.size());
    return nr_carti;
}

int BibliotecaOnline::GetNrUtilizatori(){
    int nr_useri = int(this->bd_utilizatori.size());
    return nr_useri;
}

//operatori relationali
bool BibliotecaOnline::operator==( BibliotecaOnline& biblio){
    if (this->GetNrCarti()== biblio.GetNrCarti())
        return true;
    else
        return false;
}

bool BibliotecaOnline::operator!=( BibliotecaOnline& biblio){
    if (this->GetNrCarti()== biblio.GetNrCarti())
        return false;
    else
        return true;
}


//operatori compusi de atribuire
BibliotecaOnline& BibliotecaOnline::operator+=( Carte& carte){
    this->bd_carti.push_back(carte);
  return (*this);
}

//supraincarcarea operatori citire si scriere
istream& operator >> (istream& stream, BibliotecaOnline& biblio){
    string nume_admin, parola_admin;
    Utilizator user = biblio.bd_utilizatori[0];
    cout<<"Nume admin:"<<endl;
    stream>> nume_admin;
    user.SetNumeUtilizator(nume_admin);
    cout<<"Parola_admin:"<<endl;
    stream>>parola_admin;
    user.SetParola(parola_admin);
    stream.get();
    clear_screen();
    return stream;
}

ostream& operator << (ostream& o,const BibliotecaOnline& biblio){
    o<<"Biblioteca are : " << biblio.bd_carti.size() <<" carti si "<<biblio.bd_utilizatori.size()<<" utilizatori. "<< endl;
    return o;
}




//functii membru publice

void BibliotecaOnline::DateGresite(){
    cout<<"Scrie 1 Pentru a incerca sa te loghezi din nou"<<endl;
    cout<<"Scrie 2 pentru a-ti crea un cont nou"<<endl;
    int raspuns;
    cin>>raspuns;
    if (raspuns==1){
        this->LogareCont();
    }
    else{
        this->CreareCont();
    }

}

void BibliotecaOnline::LogareCont(){

string nume, parola;
cout<<"Introduceti numele de utilizator:"<<endl;
cin>>nume;

Utilizator* ptr=ExistaNumeUser(nume);

if (ptr!=nullptr)
{   cout<<"Introduceti parola:"<<endl;
    cin>>parola;
    clear_screen();
    cout<<"Parola introdusa...Verificare parola..."<<endl;
    if (ptr->VerificareParola(parola)){

        this->IntrareInCont(*ptr);
    }
    else{
        cout<<"Parola GRESITA"<<endl;
        this->DateGresite();

    }

} else {
    cout<<"Nu exista utilizatorul"<<endl;
    this->DateGresite();



}
}
void BibliotecaOnline::IntrareInCont(Utilizator& user){
    int raspuns,raspuns2;
    cout<<"Bun Venit In Biblioteca Ta Online!"<<endl;
    cout<<"Optiuni:"<<endl;
    cout<<"1 Imprumuta Carti"<<endl;
    cout<<"2 Schimba parola"<<endl;
    cout<<"3 Returneaza carte"<<endl;
    cout<<"4 Iesi din cont"<<endl;
    cin>>raspuns;
    if (raspuns == 1)
    {
        this->AfisareCartiPentruImprumut();
        this->ImprumutaCarte(user);
    }
    else {
        if (raspuns == 2)
        {
            user.SchimbaParola();
            this->IntrareInCont(user);
        }
        else {
            if (raspuns == 3)
            {
                cout<<user;
                cout<<"Alege o carte pentru a o returna"<<endl;
                cin>> raspuns2;
                this->ReturneazaCarte(user,raspuns2-1);
                this->IntrareInCont(user);
            }
            else {
                    if(raspuns == 4){
                        this->BunVenit();
                    }
                    else {
                        clear_screen();
                        cout<<"Va rog introduceti o comanda valida!"<<endl;
                        this->IntrareInCont(user);
                    }
            }
        }
    }
}

void BibliotecaOnline::ReturneazaCarte(Utilizator& user, int poz_in_lista){
    if (user.carti_imprumutate.size()==0)
    {
    cout<<"Nu ai imprumutat inca nicio carte!"<<endl;
    }
    else{
    if(int(user.carti_imprumutate.size()) > poz_in_lista && poz_in_lista>=0){
        user.carti_imprumutate.erase(user.carti_imprumutate.begin() + poz_in_lista);
        clear_screen();
        cout<<"Ai returnat cartea cu succes!"<<endl;
    }
    else {
        int rasp;
        cout<<"Alege un nr valid!"<<endl;
        cin>> rasp;
        ReturneazaCarte(user,rasp-1);
    }
    }
}

void BibliotecaOnline::AfisareCartiPentruImprumut(){
    int k = bd_carti.size();
    cout<<"Cartile disponibile pentru imprumut sunt :"<<endl;

    for(int i=0; i< k; i++)
    {
        cout<<i+1<<". "<< bd_carti[i].GetNume()<<" scrisa de "<< bd_carti[i].GetAutor()<<endl;
    }


}

void BibliotecaOnline::IesireDinCont(){
    this->BunVenit();
}
void BibliotecaOnline::ImprumutaCarte(Utilizator& user){
    int nr_carte;
    cout<<"Alege nr. cartii pe care vrei sa o imprumuti: "<<endl;
    cin>> nr_carte;
    nr_carte --;
    bool verif = user.PoateImprumutaCartea(this->bd_carti[nr_carte]);
    if(int(this->bd_carti.size()) <= nr_carte){
        cout<<"Va rog introduceti un nr al unei carti din biblioteca!"<<endl;
        this->ImprumutaCarte(user);
    }
    else{
        if (verif == true){
            user.carti_imprumutate.push_back(this->bd_carti[nr_carte]);
            clear_screen();
            cout<<"Felicitari! Ai imprumutat cartea ";
            cout<< this->bd_carti[nr_carte];
            cout<<endl;
            cout<<"Lectura placuta !"<<endl;
        }
        else {
            clear_screen();
            cout<< "Nu poti imprumuta cartea!"<<endl;
            cout<<"Ori ai imprumutat-o deja, ori ai deja mai mult de 3 carti sau suma paginilor depaseste 1000"<<endl;
            cout<<"Citeste intai cartile imprumutate sau returneaza o carte pentru a imprumuta alta"<<endl;

        }


        this->IntrareInCont(user);
    }
}
Utilizator* BibliotecaOnline::ExistaNumeUser(string nume){
    vector<Utilizator>::iterator p;

    for(p=this->bd_utilizatori.begin();p<this->bd_utilizatori.end(); p++){
        if ((*p).GetNumeUtilizator()==nume)
            return &(*p);
    }

    return nullptr;
}


void BibliotecaOnline::CreareCont(){

    Utilizator user;
    cin>>user;
//aici tb sa verific daca mai exista un utilizator cu numele asta
    Utilizator* p = this->ExistaNumeUser(user.GetNumeUtilizator());
    if (p!=nullptr){
        cout<<"Numele exista deja! Alegeti alt nume!"<<endl;
        this->CreareCont();
    }
    else{
        this->bd_utilizatori.push_back(user);
        cout<<"Contul a fost creat!";
        this->IntrareInCont(user);
    }
}


void BibliotecaOnline::BunVenit(){
    string raspuns1;
    cout<<"Bine ati venit in Biblioteca Online!"<<endl;
    cout<<"Pentru a avea acces la nenumarate carti, va rugam sa intrati in contul dumneavoastra"<<endl;
    cout<<"Aveti deja cont? da/nu"<<endl;
    cout<<"Pentru a iesi din Biblioteca scrieti 'x'"<<endl;
    cin>>raspuns1;
    if(raspuns1=="x"){
            exit(0);
    }
    else{
        if (raspuns1=="da"){
            this->LogareCont();
        }
        else{
            if (raspuns1=="nu"){
                this->CreareCont();
            }
            else {
                cout<<"Te rog alege dintre comenzile da/ nu/ x !"<<endl;
                this->BunVenit();
            }
        }

    }
}

void BibliotecaOnline::AdaugaCarte(string nume_carte, string autor, int nr_pagini){
    Carte carte_de_adaugat(nume_carte,autor,nr_pagini);
    this->bd_carti.push_back(carte_de_adaugat);
}

void BibliotecaOnline::StergeCarte(string nume_carte, string autor){
    //verific daca exista, caut dupa nume
    vector<Carte>::iterator p;
    for(p=this->bd_carti.begin();p < this->bd_carti.end(); p++){
        if ((*p).GetNume()==nume_carte && (*p).GetAutor()==autor)
            this->bd_carti.erase(p);
    }
}


///--------------------------------------------------------------

int main(){

//

    BibliotecaOnline Biblioteca;
    Biblioteca.BunVenit();

//practic ce e mai jos nu se executa niciodata pentru ca la comanda x in meniul programului se apeleaza exit(0);
//dar am adaugat pt a testa comentand ce e mai sus, functionalitatile constructorului BiblioteciiOnline parametrizat, metodele AdaugaCarte si StergeCarte si supraincarcarea operatorului de scriere
    BibliotecaOnline Biblio2("iulia","iulia"); // daca folosesc constructorul parametrizat, imi adauga acest utilizator ca un prim utilizator si bd_carti nu va avea niciun element
    Biblio2.AdaugaCarte("Amintiri din Copilarie","Ion Creanga", 147);
    cout<<Biblio2;
    Biblio2.StergeCarte("Amintiri din Copilarie","Ion Creanga");
    cout<<Biblio2;



    return 0;
}


