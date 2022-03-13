#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Carte{
private:
    int nr_pagini;
    int an_aparitie=2022;
    int rating=10;
    int vizualizari=0;
    bool disponibilitate=true;
    string nume_carte;
    string autor;
public:

    ///constructori
    Carte();
    Carte(string nume, string autor, int nr_pagini);
    ///destructor
    //~Carte();

    friend istream& operator >> (istream& stream, Carte& carte);



public:
    void SetNumeCarte(string nume);
    void SetAutorCarte(string autor);
    void SetDisponibilitate(bool disponibilitate);
    string GetNume();
    string GetAutor();
    bool GetDisponibilitate();
    void SetRating(int rating);
    int GetRating();
    int GetVizualizari();
};



class Utilizator{
public:
    string de_citit[100];
    string citite[100];
    vector<Carte*> imprumutate;
    Utilizator(string nume="",string parola_user="");
    //~Utilizator();
    void SetNumeUtilizator(string nume_utilizator);
    string GetNumeUtilizator();
    void SetParola();
    friend istream& operator >> (istream& stream, Utilizator& user);
    bool operator==(const Utilizator& user);
    bool VerificareParola(string parola_introdusa);

private:
    int varsta;
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
    void IesireCont();
    void AdaugaCarte();
    void StergeCarte();
    void IntrareInCont(Utilizator& user);
    void ImprumutaCarte(Utilizator& user);
    void ReturneazaCarte(Utilizator& user);
    void StergeCont(Utilizator& user);
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

Utilizator::Utilizator(string nume, string parola_user){
    this->nume_utilizator= nume;
    this->parola=parola_user;
}

void Utilizator::SetNumeUtilizator(string nume_utilizator){
    this->nume_utilizator= nume_utilizator;
}

string Utilizator::GetNumeUtilizator(){
    return this->nume_utilizator;
}
istream& operator >> (istream& stream, Utilizator& user){
    cout<<"Nume utilizator:"<<endl;
    stream>> user.nume_utilizator;
    cout<<"Parola:"<<endl;
    stream>>user.parola;
    system("cls");
    return stream;
}

bool Utilizator::operator==(const Utilizator& user){
    if (this->nume_utilizator==user.nume_utilizator){
        return true;
    }
    else return false;
}

bool Utilizator::VerificareParola(string parola_introdusa){
    if (this->parola==parola_introdusa)
        return true;
    else
        return false;
}


BibliotecaOnline::BibliotecaOnline(){
    Utilizator admin("admin","admin123");
    this->bd_utilizatori.push_back(admin);
}

void BibliotecaOnline::BunVenit(){
    string raspuns1;
    cout<<"Bine ati venit in Biblioteca Online!"<<endl;
    cout<<"Pentru a avea acces la nenumarate carti, va rugam sa intrati in contul dumneavoastra"<<endl;
    cout<<"Aveti deja cont? da/nu"<<endl;
    cin>>raspuns1;
    if (raspuns1=="da"){
        this->LogareCont();
    }
    else{
        this->CreareCont();
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
cout<<"Bun Venit In Biblioteca Ta Online!"<<endl;
cout<<"Optiuni:"<<endl;
cout<<"1 Imprumuta Carti"<<endl;
cout<<"2 Schimba parola"<<endl;
cout<<"3 Iesi din cont"<<endl;

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


