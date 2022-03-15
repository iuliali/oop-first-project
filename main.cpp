#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Carte{
public:
    ///constructori
    Carte();
    Carte(string nume, string autor, int nr_pagini);
    ///destructor
    //~Carte();

    friend istream& operator >> (istream& stream, Carte& carte);
    friend ostream& operator << (ostream& o, Carte const &carte);
    int operator+( Carte const &carte);

    void SetNumeCarte(string nume);
    void SetAutorCarte(string autor);
    void SetDisponibilitate(bool disponibilitate);
    string GetNume();
    string GetAutor();
    bool GetDisponibilitate();
    void SetRating(int rating);
    int GetRating();
    int GetNrPagini();

private:
    int an_aparitie=2022;
    int rating=10;
    int vizualizari=0;
    int nr_pagini;
    bool disponibilitate=true;
    string nume_carte;
    string autor;

};



class Utilizator{
public:
    string citite[100];
    vector<Carte> carti_imprumutate;
    Utilizator(string nume="",string parola_user="");
    //~Utilizator();
    void SetNumeUtilizator(string nume_utilizator);
    string GetNumeUtilizator();
    void SetParola(string noua_parola);
    Carte* GetListaCartiImprumutate();
    friend istream& operator >> (istream& stream, Utilizator& user);
    friend ostream& operator << (ostream& o, Utilizator const &user);
    bool operator==( Utilizator& user);
    bool VerificareParola(string parola_introdusa);
    void SchimbaParola();


private:
    string nume_utilizator;
    string parola;

};

class BibliotecaOnline{
public:
    void BunVenit();
    void LogareCont();
    void CreareCont();
    Utilizator* ExistaNumeUser(string nume);
    void DateGresite();
    void IesireDinCont();
    void AdaugaCarte();
    void StergeCarte();
    void IntrareInCont(Utilizator& user);
    void AfisareCartiPentruImprumut();
    void ReturneazaCarte(Utilizator& user);
    void StergeCont(Utilizator& user);
    void ImprumutaCarte(Utilizator& user);
    BibliotecaOnline();
private:
    vector<Utilizator> bd_utilizatori{};
    vector<Carte> bd_carti;


};

Carte::Carte(string nume, string autor, int nr_pagini=100){
    this->nume_carte = nume;
    this->autor = autor;
    this->nr_pagini = nr_pagini;
}

istream& operator >> (istream& stream, Carte& carte){
    stream>> carte.nume_carte>> carte.autor>> carte.nr_pagini;
    return stream;
}

ostream& operator << (ostream& o, Carte carte){
    o<< carte.GetNume()<<" scrisa de "<< carte.GetAutor();
    return o;
}


void Carte::SetNumeCarte(string nume){
    this->nume_carte= nume;
}

void Carte::SetAutorCarte(string autor){
    this->autor= autor;
}

void Carte::SetRating(int rating){
    this->rating= rating;
}

string Carte::GetNume(){
    return this->nume_carte;
}

string Carte::GetAutor(){
    return this->autor;
}

int Carte::GetRating(){
    return this->rating;
}

int Carte::GetNrPagini(){
    return this->nr_pagini;
}


int Carte::operator+( Carte& carte){
    return this->GetNrPagini()+ carte.GetNrPagini();
}


Utilizator::Utilizator(string nume, string parola_user){
    this->nume_utilizator= nume;
    this->parola=parola_user;
}

void Utilizator::SetNumeUtilizator(string nume_utilizator){
    this->nume_utilizator = nume_utilizator;
}

void Utilizator::SetParola(string noua_parola){
    this->parola = noua_parola;
}

string Utilizator::GetNumeUtilizator(){
    return this->nume_utilizator;
}
istream& operator >> (istream& stream, Utilizator& user){
    cout<<"Nume utilizator:"<<endl;
    stream>> user.nume_utilizator;
    cout<<"Parola:"<<endl;
    stream>>user.parola;
    stream.get();
    system("cls");
    return stream;
}

ostream& operator << (ostream& o, Utilizator const &user){
    ///todo
}

bool Utilizator::operator==( Utilizator& user){
    if (this->GetNumeUtilizator()==user.GetNumeUtilizator()){
        return true;
    }
    else
        return false;
}

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
    //system("cls");
    cout<< "Parola schimbata cu succes! "<<endl;

}

void BibliotecaOnline::ImprumutaCarte(Utilizator& user){
    int nr_carte;
    cout<<"Alege nr. cartii pe care vrei sa o imprumuti: "<<endl;
    cin>> nr_carte;
    nr_carte --;
    user.carti_imprumutate.push_back(this->bd_carti[nr_carte]);
    cout<<"Felicitari! Ai imprumutat cartea ";
    cout<< this->bd_carti[nr_carte];
    cout<<endl;
    cout<<"Lectura placuta !"<<endl;
    //system("cls");
    this->IntrareInCont(user);

}


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
            this->CreareCont();
        }

    }
}

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
    system("cls");
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
    int raspuns;
    cout<<"Bun Venit In Biblioteca Ta Online!"<<endl;
    cout<<"Optiuni:"<<endl;
    cout<<"1 Imprumuta Carti"<<endl;
    cout<<"2 Schimba parola"<<endl;
    cout<<"3 Iesi din cont"<<endl;
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
                this->BunVenit();
            }
            else {
                cout<<"Va rog introduceti o comanda valida!"<<endl;
                this->IntrareInCont(user);
            }
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
    }
    else
    {   cout<<"Contul a fost creat!";
        this->IntrareInCont(*p);
    }
}


int main(){
/*Carte book("Mara","Slavici",88);
cout<<book.GetNume()<<endl;
book.SetNumeCarte("Ion");
cout<<book.GetNume()<<endl;
Carte book2("Poezii","Iulia",90);
cin>>book2;
//cout<<book.GetRating()<<endl;
//book.SetAutorCarte("Eminescu");
cout<<book2.GetNume()<<endl;
cout<<book2.GetAutor()<<endl;


Utilizator user1("iulia","parola123");
cout<<user1.GetNumeUtilizator();
cin>>user1;
cout<<user1.GetNumeUtilizator();
*/

    BibliotecaOnline Biblioteca;
    Biblioteca.BunVenit();


    return 0;
}


