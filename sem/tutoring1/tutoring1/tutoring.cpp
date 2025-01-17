#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class ExceptieCustom : public exception {
	string mesaj;
public:
	ExceptieCustom() {
		this->mesaj = "Nu stiu ce eroare e";
	}
	ExceptieCustom(string mesaj) {
		this->mesaj = mesaj;
	}
	string afiseazaEroarea() {
		return this->mesaj;
	}
};

class Tema {
private:
	const int idTema;
protected:
	char* materie;
	string tipTema;//doc,pdf,ppt
	float punctaj;
public:
	static int nrTemeTrimise;

	//constructorul fara param/default/implicit
	Tema():idTema(nrTemeTrimise++) {
		this->materie = new char[strlen("Anonim")+1]; //asa alocam memorie pt vector
		strcpy(this->materie, "Anonim");
		this->tipTema = "Nu stiu";
		this->punctaj = 0.0;
	}
	//constructorul cu toti parametri
	Tema(const char* materie, string tipTema, float punctaj):idTema(nrTemeTrimise++) {
		this->materie = new char[strlen(materie) + 1]; //asa alocam memorie pt vector
		strcpy(this->materie, materie);
		this->tipTema = tipTema;
		this->punctaj = punctaj;
	}
	//constructor de copiere
	Tema(const Tema& t) :idTema(t.idTema) {
		this->materie = new char[strlen(t.materie) + 1]; //asa alocam memorie pt vector
		strcpy(this->materie, t.materie);
		this->tipTema = t.tipTema;
		this->punctaj = t.punctaj;
	}

	//destructor
	~Tema() {
		if (this->materie != NULL)
			delete[] this->materie;
	}

	//operatorul este compus din destructor, constructor de copiere si operator de atribuire
	Tema& operator=(const Tema& t) {
		if (this != &t) {
			if (this->materie != NULL) {
				delete[] this->materie;
			}
			this->materie = new char[strlen(t.materie) + 1]; //asa alocam memorie pt vector
			strcpy(this->materie, t.materie);
			this->tipTema = t.tipTema;
			this->punctaj = t.punctaj;
		}
		return *this;
	}

	//cand spune 2 metode accesor facem getter si setter
	//getter -> funcie accesor care permite extragerea valorii 
	float getPunctaj() {
		return this->punctaj;
	}
	const int getIdTema() {
		return this->idTema;
	}
	char* getMaterie() {
		return this->materie;
	}
	//setter -> functie accesor care permite modificarea valorii
	void setPunctaj(float punctaj) {
		if (punctaj >= 0 && punctaj <= 10) {
			this->punctaj = punctaj;
		}
		else throw ExceptieCustom("Valoarea introdusa nu indeplineste anumite criterii!");
	}
	friend ostream& operator <<(ostream& out, Tema t) {
		out << "Id tema: " << t.idTema << endl;
		out << "Materie: " << t.materie << endl;
		out << "Tip tema: " << t.tipTema << endl;
		out << "Punctaj: " << t.punctaj << endl;
		return out;
	}

	//operator += (valoare)
	Tema& operator +=(float valoare) {
		//this->puncat +=valoare;
		this->punctaj = punctaj + valoare;
		return *this;
	}
	// Operator !
	bool operator!() {
		if (this->punctaj > 5) {
			return true;
		}
		else {
			return false;
		}
	}
	// Operator ~
	void operator~() {
		if (this->punctaj == true) {
			this->punctaj = false;
		}
	}
	// Operator ==
	bool operator==(const Tema& t) const {
		return (/*this->idTema == t.idTema &&
			strcmp(this->materie, t.materie) == 0 &&
			this->tipTema == t.tipTema &&*/
			this->punctaj == t.punctaj);
	}
	// Operator *= (Exemplu simplificat)
	Tema& operator*=(int factor) {
		this->punctaj *= factor;
		return *this;
	}
	// Operator []
	char operator[](int index) const {
		if (index >= 0 && index < strlen(this->materie)) {
			return this->materie[index];
		}
		return 0;
	}
	// Operator >=
	bool operator>=(const Tema& t) const {
		return this->punctaj >= t.punctaj;
	}
	// Operator -=
	Tema& operator-=(float valoare) {
		this->punctaj -= valoare;
		return *this;
	}
	// Operator --
	Tema& operator--() { // Preincrementare
		--this->punctaj;
		return *this;
	}
	Tema operator--(int) { // Postincrementare
		Tema temp(*this);
		this->punctaj--;
		return temp;
	}
	// Operator ++
	Tema& operator++() { // Preincrementare
		++this->punctaj;
		return *this;
	}
	Tema operator++(int) { 	// Post-incrementare
		Tema temp(*this);
		this->punctaj++;
		return temp;
	}
	bool operator<(Tema t) const {
		return strcmp(this->materie, t.materie) == -1;
		//strcmp(this->materie, p.materie == 0 --> sunt identince
		//strcmp(this->materie, p.materie == 1 --> sunt in ordine inversa, nu in ordine alfabetica
		//strcmp(this->materie, p.materie == -1 --> sunt in ordine alfabetica
	}
	//in orice tip de fisier(text, binar, altceva) nu cititm/scriem atributele statice/constante
	void scriereInBinar(string numeFisier) {
		//serializare -> repr procesul de transformare a unui obiect intr-o secventa de biti
		ofstream f(numeFisier, ios::out | ios::binary);
		//asa scriem char*
		int dim = strlen(this->materie);
		f.write((char*)&dim, sizeof(dim));
		f.write(this->materie, dim + 1);

		//asa scriem string
		int dimS = this->tipTema.size();
		f.write((char*)&dimS, sizeof(dimS));
		f.write(this->tipTema.c_str(), dimS + 1);

		//asa scriem int/float/double/bool
		f.write((char*)&this->punctaj, sizeof(this->punctaj));
		f.close();
	}
	void citesteDinBinar(string numeFisier) {
		ifstream f(numeFisier, ios::in | ios::binary);
		if (f.is_open()) {
			//asa scriem char*
			delete[] this->materie;
			int dim = 0;
			f.read((char*)&dim, sizeof(dim));
			this->materie = new char[dim + 1];
			f.read(this->materie, dim + 1);

			//asa scriem string
			int dimS = 0;
			f.read((char*)&dimS, sizeof(dimS));
			char* aux = new char[dimS + 1];
			f.read(aux, dimS + 1);
			this->tipTema = aux;
			delete[] aux;

			//asa scriem int/float/double/bool
			f.read((char*)&this->punctaj, sizeof(this->punctaj));
			f.close();
		}
		else {
			cout << "Fisierul nu s-a putut deschide" << endl;
		}
	}

};
int Tema::nrTemeTrimise = 0;
int main(){
	//obiect construit pe baza constructorului fara param
	Tema t;
	cout << t.getPunctaj() << endl;
	t.setPunctaj(7.7);
	try {
		t.setPunctaj(15.2);
	}
	/*catch (exception ex) {
		cout << ex.what() << endl;
	}*/
	catch (ExceptieCustom exC) {
		cout << exC.afiseazaEroarea() << endl;
	}
	cout << t.getPunctaj() << endl;

	Tema t1("ATP", "PPT", 8.6);
	Tema t2("ALGEBRA", "DOC", 9.6);
	Tema t3("BPC", "CPP", 4.1);

	cout << t1 << endl;
	cout << t2 << endl;
	cout << t3 << endl;

	/*t3 += 1.5;
	cout << "noul punctaj:" << endl;
	cout << t3 << endl;

	cout << !t1 << endl;
	cout << !t2 << endl;
	cout << !t3 << endl;*/

	/*~t1;
	cout << t1 << endl;

	if (t1 == t2) {
		cout << "notele sunt egale" << endl;
	}
	else{
		cout << "notele nu sunt egale" << endl;
	}*/

	////t1 *= 2;
	//cout << t1 << endl;

	//cout << t1[0] << endl;

	//if (t1 >= t2) {
	//	cout << "t1 are nota mai mare sau egala decat t2" << endl;
	//}
	//else {
	//	cout << "t1 are nota mai mica decat t2" << endl;
	//}
	/*t1.operator-= (2.5);
	cout << t1 << endl;*/

	/*--t1;
	cout << t1 << endl;
	t1.operator++();
	cout << t1 << endl;*/

	if (t2 < t3) {
		cout << "Tema 2 este inaintea temei 3" << endl;
	}
	else {
		cout << "Tema 3 este inaintea temei 2" << endl;
	}

	/*cout << endl << endl;
	Tema t1("ATP","PPT", 8.6);
	cout << t1.getIdTema() << endl;
	cout << t1.getMaterie() << endl;
	cout << t1.getPunctaj() << endl;	
	t1 += 2.5;
	cout << "noul punctaj:" << endl;
	cout << t1.getPunctaj() << endl;

	cout << endl << "scriere binar:"<<endl;
	t1.scriereInBinar("exemplu.bin");
	Tema tBinar;
	cout << tBinar << endl;
	cout << "citire binar:" << endl;
	tBinar.citesteDinBinar("exemplu.bin");
	cout << tBinar << endl;*/

}

