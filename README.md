# Structuri de Date și Algoritmi — Tema 1 <br> Liste dublu înlănțuite, stive

Soluție realizată de Andrei-Marcel Bădulescu, Universitatea Politehnica București <br>
Dată — 15 aprilie 2025

### Prefață

<p> Soluția respectă standardele impuse prin regulament cu privire la
utilizarea eficientă a memoriei, tratarea eventualelor erori ale funcțiilor
din bibliotecile standard, utilizarea în siguranță a pointerilor și a
fișierilor, dar și la coding style. Antetele, respectiv implementările
funcțiilor sunt plasate în fișiere separate față de programul principal cu
scopul de a asigura un grad de lizibilitate adecvat. De-a lungul implementării
pot fi regăsite comentarii ce însoțesc codul care pot ajuta la înțelegerea
utilității și consecințelor instrucțiunilor folosite. </p>

<p> Fișierele sursă sunt plasate în interiorul folderului „source” pentru a
menține spațiul de lucru ordonat. Fișierul Makefile este configurat să
recunoască comenzile „build”, „run”, „clean” și „pack”; simpla utilizare
a comenzii „make” are același comportament cu „make build”. </p>

<p> Soluția prezentată obține punctajul maxim în testele rulate de către
checker, cât și punctele bonus acordate pentru testarea soluției cu Valgrind.
Aceasta a fost implementată în decursul a aproximativ 20 ore de lucru. </p>

### Implementarea soluției

<p> Programul citește din fișierul de input numărul de pagini, care este mai
apoi folosit pentru a aloca dinamic spațiu pentru vectorul de pagini. Paginile
sunt citite la rândul lor din fișierul de input una câte una, iar cea implicită
este adăugată manual înainte de citire. Browserul este inițializat cu un tab
implicit ce nu poate fi închis, în cadrul căruia este deschisă pagina implicită.
În acest proces este inițializată și lista dublă circulară cu santinelă care
stochează în mod dinamic tab-urile folosite de utilizator. </p>

<p> Din acest punct, începe execuția comenzilor utilizatorului; mai întâi este
citit numărul de comenzi introduse de acesta. Mai întâi este citit un cuvânt
cheie care este asociat unei funcții. Cuvântul este transformat cu ajutorul
unei funcții într-un număr ce reprezintă codificarea unei comenzi. Dacă
cuvântul cheie nu este recunoscut, toată comanda este sărită. În cazul în
care utilizatorul apelează o funcție ce necesită și un parametru, acesta este
citit înainte de executarea comenzii. </p>

<p> La final este eliberată toată memoria alocată dinamic pe heap și sunt
închise fișierele de input, respectiv output. Dacă parametrul sau comanda este
invalidă, funcția asociată va returna codul de eroare 403, care este printat
și în fișierul de output. Dacă de-a lungul execuției apare o eroare a unei
funcții din bibliotecile standard, este încheiată execuția cu codul 1. În cazul
execuției corecte și complete va fi returnat codul 0. </p>

### Structurile de date

- Browserul are un pointer către tab-ul curent și o listă dublă circulară cu
santinelă pentru stocarea tuturor tab-urilor. Lista are ca prim element
santinela.
- Lista de tab-uri este implementată cu ajutorul unui struct care conține
informațiile despre tab-ul respectiv, cât și doi pointeri, unul îndreptat
către elementul anterior și altul către cel următor.
- Unui tab sunt asociate un ID unic alocat automat de program, un pointer
către pagina curentă, dar și stivele backward și forward asociate istoricului
de navigare în acel tab, în care sunt salvați pointeri către paginile respective.
ID-urile sunt date în ordine crescătoare, tab-ul implicit având ID-ul 0. Dacă
un tab este închis, ID-ul acestuia nu poate fi refolosit mai târziu.
- Paginile sunt salvate într-un vector alocat dinamic pe heap. Fiecare pagină
are un ID unic, un URL / link asociat care are maxim 49 de caractere și un
pointer către o descriere stocată dinamic la citire.