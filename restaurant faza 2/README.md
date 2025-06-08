# Proiect
Proiectul implementează un modul de gestiune a unui restaurant din prisma stocului materiilor prime din bucătărie. Clienții au posibilitatea de a consulta un meniu care conține toate preparatele pe care acesta le poate comanda. Fiecare preparat deține un rețetar format din materiile prime și cantitățile necesare preparării. Un client poate adăuga într-o comandă mai multe produse din meniu. Programul verifică disponibilitatea materiilor prime și lansează în sistem sau nu comenzile. Întreg fluxul este gestionat pe baza unor comenzi la consolă definite de voi într-o legendă.

Copierea proiectului in proportie mai mare de 30% conduce la anularea intregului punctaj (lucrare + proiect) de la seminar  si la notificarea Decanatului.
Conditii generale privind realizarea proiectului:
-	proiectul reprezinta o aplicatie executabila care testeaza conceptele C++ implementate;
-	proiectul trebuie sa ruleze si sa nu genereze exceptii de executie (atentie la memory-leaks si la valori gestionate prin mai multi pointeri);
-	codul sursa al proiectul trebuie sa fie scris fara erori de compilare;
-	proiectul este dezvoltat in Visual Studio 2019;
-	proiectul se realizeaza individual;
-	proiectul implementeaza clase diferite intre care exista relatii de tip is-a sau has-a; 
-	NU se folosesc variabile globale sau functii globale.

# Cerinte proiect faza I
-	Definirea a minim 5 clase care au legatura cu cerinta proiectului
-	Fiecare clasa trebuie sa contina minim un camp definit dinamic;
-	In solutie trebuie sa existe minin o clasa ce defineste un camp static, minim o clasa ce defineste un camp constant, minim o clasă ce abordează șiruri de caractere alocate dinamic sau static;
-	Toate atributele se definesc pe zona privata a clasei
-	Pentru fiecare atribut se defineste o interfata publica (functii accesor) ce permite citirea si scrierea valorii; functiile de modificare trebuie sa contina minim o regula de validare a valorii
-	Fiecare clasa contine minim 2 metode generice de prelucrare/afisare a atributelor
-	Fiecare clasa contine minim 2 constructori cu parametri, constructor de copiere, destructor si forma supraincarcata a operatorului =
-	Pentru fiecare clasa se supraincarca obligatoriu >> si <<
-	În cadrul celor cinci clase, trebuie să existe supraincărcarea următorilor operatori:
-	operatorul pentru idexare []
-	minim un operator matematic (+,-,* sau /)
-	++ sau -- (cu cele 2 forme)
-	operatorul cast (catre orice tip) explicit sau implicit
-	operatorul pentru negatie !
-	un operator conditional (<.>,=<,>=)
-	operatorul pentru testarea egalitatii dintre 2 obiecte ==

# Cerinte proiect faza II
-	Se implementeaza un modul prin care aplicatia primeste fisiere de intrare (de tip text) prin argumentele functiei main (exemplu: daca aplicatia se numeste proiectPOO.exe atunci ea este lansata in executie cu comanda proiectPOO.exe facturi.txt cheltuieli.txt; pot fi folosite doar fisiere text). Fisierele sunt folosite pentru a popuna stocul initial din bucatarie precum si meniul restaurantului alaturi de preparatele sale.
-	Se implementeaza un modul prin care utilizatorul poate salva datele aplicatiei in fisiere binare. Datele aplicatiei se considera a fi acele date obtinute din fisierele text primite ca argumente pentru main sau date incarcate de utilizatori in timpul sesiunii de lucru. Daca aplicatia nu primeste argumente prin functia main (se lanseaza in executie cu proiectPOO.exe) atunci va accesa fisiere binare aflate la locatii cunoscute de progamator. Fisirele binare permit salvarea tuturor datelor care au fost incarcate in aplicatie prin diferite metode.
-	Se implementeaza modulul prin care utilizatorul are posibilitatea sa genereze diferite rapoarte pentru toate datele (de ex. lista utilizatori, lista intrebari dintr-o anumita categorie, ierarhii utilizatori, raspunsuri pentru o intrebare, etc ) care sa fie afisate la consola dar si in fisiere text (minim 3 rapoarte)
-	Aplicatia permite incarcarea de date din fisiere CSV (comma separated values);  simbolul ales pentru a separa valorile este ales de programator si este folosit pentru toate fisierele CSV;
-	Se implementeaza conceptul de virtualizare in citirea si scrierea in fisiere binare a unor obiecte ce fac parte dintr-o familie de clasa. Implementarea trebuie sa utilizeze minim 2 metode virtuale, o clasa abstracta/interfata si o clasa tip compunere ce gestioneaza obiecte sau pointeri de obiecte din cadrul familiei de clase anterior enuntata.
-	Aplicatia trebuie sa permita generarea de diferite rapoarte care sa analizeze activitatea utilizatorilor (data mining in seturile de date pentru a extrage informatii cu privire la activitatea utilizatorilor): minim 2 rapoarte.
-	Sa se implementeze din libraria STL cel putin un vector, un set, o lista si un map pentru a gestiona datele aplicatiei. Acestea pot fi adaugate in clasele existente ce tin de faza 2 a proiectului.
-	Aplicatia trebuie sa ruleze "la cheie" fara a genera erori la executie.


Proiectul este predat in format arhivat (.zip) sau intr-un singur fisier sursa (.cpp) pana la data 14.01.2024. Arhiva contine fisierele sursa al programului. Denumirea fiecarui fisier urmareste sablonul [Proiect][grupa][Nume_prenume]_Denumire_particulara_fisier (de. ex. [Proiect][1038][Popescu_Alex]_Clasa_Student.cpp)
Denumirea arhivei/fisierului sursa are forma: [Proiect][grupa][Nume_prenume] - [Faza proiect] (Exemplu: [Proiect][1066][Popescu Alexandru] - [Faza 1]). 
Depunerea proiectelor se face prin intermediul unei platforme virtuale ce va face si o verificare anti-plagiarism a codului sursa. Conturile de utilizator vor fi comunicate la seminar.




