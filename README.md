# oop-first-project

<p align="center"><img src="https://c.tenor.com/Wwq15dXEGskAAAAC/books-books-are-freedom.gif" width="200" height="200" /> <b>BIBLIOTECA ONLINE</b>
<img src="https://bestanimations.com/media/reading/655989980sherlock-holmes-reading-book-animated-gif.gif" width="400" height="200" /></p>

# **Scurta Prezentare**
<i>
Folosind principiile de baza, simple, introductive din programarea orientata pe obiecte, am creat un program interactiv 
care simuleaza un numar modest de functionalitati ale unei biblioteci online.
Programul e construit pe baza a trei clase : BibliotecaOnline, Utilizator si Carte.</br>
Am proiectat aceste clase folosind compunerea astfel: </br>
-BibliotecaOnline are un vector cu obiecte de tip Carte reprezentand cartile disponibile in biblioteca</br>
-BibliotecaOnline are un vector cu obiecte de tip Utilizatori reprezentand utilizatorii inregistrati</br>
-Utilizatorul are un vector cu obiecte de tip Carte reprezentand cartile imprumutate de acesta(sunt copii ale obiectelor din vectorul Bibliotecii) </br>
</i>

# **Functionalitati - Testare functionalitati**

Odata ce rulam programul din orice IDE sau din terminal, apare pagina de start a Bibliotecii Online, unde te poti loga sau iti poti crea cont.

By default exista un utilizator creat care are numele de utilizator:
```admin```  
si parola setata :
```admin123 ``` <br>
Daca ne logam cu un nume care nu exista(incercati orice nume), programul va da eroare, dar si posibilitatea de a incerca din nou sau de a crea un cont nou.<br>
Daca incercam sa creem un cont cu un nume deja existent (admin), programul ne va semnala acest lucru si putem incerca sa creem un cont cu alt nume.
Odata intrati in cont, avem cele 4 optiuni: <br>
```1 Imprumuta carti ``` <br>
```2 Schimba parola ``` <br>
```3 Returneaza carte``` <br>
```4 Iesi din cont``` <br>
Daca introducem altceva decat aceste 4 numere (1/2/3/4), programul ne semnaleaza sa introducem o comanda valida. <br>
Daca vrem sa imprumutam carti, putem imprumuta <b>cate o carte odata</b>, nu mai mult de 3 carti sau mai mult de 1000 de pagini cumulate. <br>
Nu putem imprumuta o carte daca o avem deja. <br>
Pentru a vedea ce carti am imprumutat, putem sa mergem la comanda ```3 Returneaza carte```. <br>
De asemenea, putem returna <b>cate o carte odata.</b> <br>
Putem schimba parola, apoi sa iesim din cont si sa vedem cum parola s-a schimbat, cartile imprumutate sunt salvate si le putem returna pentru a imprumuta altele. <br>

>Future possible functionalities:

Adminul va putea adauga/sterge carti. <br>
Ar trebui implementat ca o clasa Rol cu posibilitatile rol- utilizator si rol-admin si cu permisiuni diferite. <br>
Momentan exista implementate metodele pentru Adaugare/Stergere Carte din Biblioteca, dar trebuie rulate din main. <br>





# **Instructiuni de utilizare**
```

Limbaj de programare utilizat -> C++

```

>Rularea Programului

Programul va fi rula din terminal folosind urmatoarele comenzi:

```
g++ -o main main.cpp
```
