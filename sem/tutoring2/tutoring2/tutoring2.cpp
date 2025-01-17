#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include <map>
using namespace std;

class Petitie {
	const int idPetitie;
	char* denumire;
	string categorie;
	int nrZileDeLaDepunere;
	bool starePetitie; //0 inchis 1 deschis
	static string localitate;
public:
	Petitie():idPetitie(0) {
		this->denumire = new char[strlen("Petitie X") + 1];
		strcpy(this->denumire, "Petitie X");
		this->categorie = "X";
		this->nrZileDeLaDepunere = 0;
		this->starePetitie = 0;
	}
	Petitie(int idPetitie, const char* denumire, string categorie, int nrZileDeLaDepunere, bool starePetitie) :idPetitie(0) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->categorie = categorie;
		this->nrZileDeLaDepunere = nrZileDeLaDepunere;
		this->starePetitie = starePetitie;
	}
	int getNrZileDeLaDepunere() {
		return this->nrZileDeLaDepunere;
	}
	string getCategorie() {
		return this->categorie;
	}
	void setNrZileDeLaDepunere(int nrZileDeLaDepunere) {
		this->nrZileDeLaDepunere = nrZileDeLaDepunere;
	}
	Petitie(const Petitie&p) :idPetitie(p.idPetitie) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->categorie = p.categorie;
		this->nrZileDeLaDepunere = p.nrZileDeLaDepunere;
		this->starePetitie = p.starePetitie;
	}
	~Petitie() {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
	}
	Petitie& operator=(const Petitie& p) {
		if (this != &p) {
			if (this->denumire != NULL) {
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
			this->categorie = p.categorie;
			this->nrZileDeLaDepunere = p.nrZileDeLaDepunere;
			this->starePetitie = p.starePetitie;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Petitie& p) {
		out << "Id petitie: " << p.idPetitie << endl;
		out << "Denumire: " << p.denumire << endl;
		out << "Categorie: " << p.categorie << endl;
		out << "Numar zile de la depunere: " << p.nrZileDeLaDepunere << endl;
		out << "Stare petitie: " << p.starePetitie << endl;
		return out;
	}
	//in operatorul >> nu citim niciodata atribute const/static
	friend istream& operator>>(istream& in, Petitie& p) {
		cout << "Denumire: ";
		//asa citim un char* de la tastatura cu tot cu spatiu
		in >> ws;
		char aux[100];
		in.getline(aux, 99);
		if (p.denumire != NULL) {
			delete[] p.denumire;
		}
		p.denumire = new char[strlen(aux) + 1];
		strcpy(p.denumire, aux);
		//asa citim un string de la tastatura
		cout << "Categorie: ";
		in >> ws;
		getline(in, p.categorie);
		//asa citim un numerice/bool
		cout << "Nr Zile de la depunere: ";
		in >> p.nrZileDeLaDepunere;
		//bool
		cout << "Stare petitie: 1-dechisa, 0-rezolvata: ";
		in >> p.starePetitie;
		return in;
	}
	bool operator!() {
		if (this->starePetitie == true && this->nrZileDeLaDepunere > 30) {
			return true;
		}
		else {
			return false;
		}
	}
	void operator~(){
		if (this->starePetitie == true) {
			this->starePetitie = false;
		}

	}
	bool operator<(Petitie p) const {
		return strcmp(this->denumire, p.denumire) == -1;
		//strcmp(this->denumire, p.denumire == 0 --> sunt identince
		//strcmp(this->denumire, p.denumire == 1 --> sunt in ordine inversa, nu in ordine alfabetica
		//strcmp(this->denumire, p.denumire == -1 --> sunt in ordine alfabetica
	}
	//scriere in fisier txt, o sa avem nevoie de ofstream si ifstream
	// se fac la fel ofstream si ifstream, dar fara texte aditionale si fara const/static
	friend ofstream& operator<<(ofstream& out, const Petitie& p) {
		out << p.idPetitie << endl;
		out << p.denumire << endl;
		out << p.categorie << endl;
		out << p.nrZileDeLaDepunere << endl;
		out << p.starePetitie << endl;
		return out;
	}
	//in operatorul >> nu citim niciodata atribute const/static
	friend ifstream& operator>>(ifstream& in, Petitie& p) {
		//asa citim un char* de la tastatura cu tot cu spatiu
		in >> ws;
		char aux[100];
		in.getline(aux, 99);
		if (p.denumire != NULL) {
			delete[] p.denumire;
		}
		p.denumire = new char[strlen(aux) + 1];
		strcpy(p.denumire, aux);
		//asa citim un string de la tastatura
		in >> ws;
		getline(in, p.categorie);
		//asa citim un numerice/bool
		in >> p.nrZileDeLaDepunere;
		//bool
		in >> p.starePetitie;
		return in;
	}
};
string Petitie::localitate = "Bucuresti";
int main() {
	Petitie p;
	cout << p.getNrZileDeLaDepunere() << endl;
	p.setNrZileDeLaDepunere(11);
	cout << p.getNrZileDeLaDepunere() << endl;

	cout << endl;
	Petitie p1(43, "Salvarea Copacilor Pitici", "Natura", 24, 0);
	cout << p1.getNrZileDeLaDepunere() << endl;

	Petitie p2(143, "Salvarea Aricii Pogonici", "Natura", 32, 1);

	cout << p << endl;
	cout << p1 << endl;
	cout << p2 << endl;

	if (p1 < p2) {
		cout << "Petitia 1 este inaintea petitiei 2" << endl;
	}
	else {
		cout << "Petitia 2 este inaintea petitiei 1" << endl;
	}

	cout << endl;
	//Petitie p2 = p;
	cout << p2.getNrZileDeLaDepunere() << endl;

	cout << endl;
	p2 = p1;
	cout << p2.getNrZileDeLaDepunere() << endl;
	cout << endl << endl;
	cout << p2 << endl;

	cout << endl << endl;
	cout << p1 << endl;

	Petitie p3(143, "Salvarea Aricii Pogonici", "Natura", 32, 1);
	p2 = p3;

	cout << p3 << endl << endl;
	cout << p2 << endl << endl;


	cout << endl;

	cout << !p1 << endl;
	cout << !p2 << endl;

	if (!p1) {
		cout << "Petitia nu a fost rezolvata!" << endl;
	}
	else {
		cout << "Petitia a fost solutionata!" << endl;
	}

	if (!p2) {
		cout << "Petitia nu a fost rezolvata!" << endl;
	}
	else {
		cout << "Petitia a fost solutionata!" << endl;
	}

	~p2;


	if (!p2) {
		cout << "Petitia nu a fost rezolvata!" << endl;
	}
	else {
		cout << "Petitia a fost solutionata!" << endl;
	}


	cout << p << endl<<endl;
	cin >> p;
	cout << endl << endl;
	cout << p << endl<<endl;

	cout << endl << endl << endl;
	cout << p1 << endl << endl;
	cout << p << endl << endl;

	//cum scriem in fisier text
	ofstream f("exempluFis.txt", ios::out);
	f << p1;
	f.close();

	//cum citim din fisier text

	ifstream g("exempluFis.txt", ios::in);
	g >> p;
	g.close(); cout << endl;
	cout << p1 << endl << endl;
	cout << p << endl << endl;

	Petitie p4(15, "Scadearea Inflatiei", "Economic", 32, 1);
	Petitie p5(56, "Cresterea salariului Minim", "Economic", 32, 1);
	Petitie p6(42, "Scaderea poluarii", "Natura", 32, 1);

	map<Petitie, string> mapPetitii;
	mapPetitii.insert(pair<Petitie, string>(p, p.getCategorie()));
	mapPetitii.insert(pair<Petitie, string>(p1, p1.getCategorie()));
	mapPetitii.insert(pair<Petitie, string>(p2, p2.getCategorie()));
	mapPetitii.insert(pair<Petitie, string>(p3, p3.getCategorie()));
	mapPetitii.insert(pair<Petitie, string>(p4, p4.getCategorie()));
	mapPetitii.insert(pair<Petitie, string>(p5, p5.getCategorie()));
	mapPetitii.insert(pair<Petitie, string>(p6, p6.getCategorie()));


	cout << "==================================" << endl;
	map<Petitie, string>::iterator itMap;
	for (itMap = mapPetitii.begin(); itMap != mapPetitii.end(); itMap++) {
		if (itMap->second == "Economic") {
			cout << itMap->first << endl;
		}
	}


}