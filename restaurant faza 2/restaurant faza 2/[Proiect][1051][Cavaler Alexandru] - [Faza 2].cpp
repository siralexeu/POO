#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <set>
#include <map>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

class IFile { //clasa abstracta
    virtual void saveToFile(fstream& file) = 0; 
    virtual void restoreFromFile(fstream& file) = 0; 
};

class Ingredient { //ingredientele necesare pt un preparat
private:
    int id;
    char* nume = nullptr; //numele ingredientului
    int stoc = 0; //cant de ingredient care se afla in stoc

public:
    Ingredient() : id(0), nume(nullptr), stoc(0) {}
    Ingredient(int id, const char* nume, int stoc)
        : id(id), stoc(stoc) {
        if (nume != nullptr) {
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
        }
    }
    Ingredient(const Ingredient& i)
        : id(i.id), stoc(i.stoc) {
        if (i.nume != nullptr) {
            this->nume = new char[strlen(i.nume) + 1];
            strcpy(this->nume, i.nume);
        }
    }
    Ingredient& operator=(const Ingredient& i) {
        if (this != &i) {
            delete[] this->nume;
            this->nume = nullptr;

            if (i.nume != nullptr) {
                this->nume = new char[strlen(i.nume) + 1];
                strcpy(this->nume, i.nume);
            }
            this->stoc = i.stoc;
        }
        return *this;
    }
    void setNume(const char* newNume) {
        if (newNume != nullptr) {
            delete[] this->nume;
            this->nume = new char[strlen(newNume) + 1];
            strcpy(this->nume, newNume);
        }
        else {
            throw new exception("A fost introdus un nume invalid");
        }
    }
    int getId() const {
        return this->id;
    }
    const char* getNume() const {
        return this->nume;
    }
    int getStoc() const {
        return this->stoc;
    }
    void setStoc(int newStoc) {
        if (newStoc >= 0) {
            this->stoc = newStoc;
        }
        else {
            throw new exception("Stocul nu poate fi negativ");
        }
    }
    void afiseazaDetalii() const {
        cout << "Ingredient (ID " << id << "): " << nume << ", Stoc: " << stoc << "\n";
    }
    bool operator==(const Ingredient& i) const {
        return (id == i.id) && (strcmp(nume, i.nume) == 0) && (stoc == i.stoc);
    }
    bool operator!=(const Ingredient& i) const {
        return !(*this == i);
    }
    ~Ingredient() {
        delete[] nume;
    }
    friend istream& operator>>(istream& in, Ingredient& ing) {
        delete[] ing.nume;
        ing.nume = nullptr;

        cout << "Introduceti numele ingredientului: ";
        char buffer[100];
        in >> buffer;
        ing.nume = new char[strlen(buffer) + 1];
        strcpy(ing.nume, buffer);

        cout << "Introduceti stocul ingredientului: ";
        in >> ing.stoc;

        return in;
    }
    friend ostream& operator<<(ostream& out, const Ingredient& i) {
        out << "Ingredient (ID " << i.getId() << "): " << i.getNume() << ", Stoc: " << i.getStoc() << " unitati\n";
        return out;
    }
    void saveToFile(fstream& file) const {
        file.write((char*)&this->id, sizeof(int));
        int lg = strlen(this->nume) + 1;
        file.write((char*)&lg, sizeof(int));
        file.write(this->nume, lg);
        file.write((char*)&this->stoc, sizeof(int));
    }
    void restoreFromFile(fstream& file) {
        file.read((char*)&id, sizeof(int));
        int lg;
        file.read((char*)&lg, sizeof(int));
        char* buffer = new char[lg];
        file.read(buffer, lg);
        nume = new char[strlen(buffer) + 1];
        strcpy(nume, buffer);
        delete[] buffer;
        file.read((char*)&stoc, sizeof(int));
    }
    /*
    void restoreFromCSV(ifstream& in) {
        string line;
        getline(in, line);
        stringstream dateIng(line);
        string buffer;
        getline(dateIng, buffer, ',');
        this->id = stoi(buffer);
        getline(dateIng, this->nume, ',');

        getline(dateIng, buffer, ',');
        this->stoc = stoi(buffer);

    }*/
    bool operator!() const {
        return (!this->nume || strlen(this->nume) == 0) && this->stoc == 0;
    }
    
    Ingredient& operator++() {    //pre-incrementare
        this->stoc++;
        return *this;
    }
    Ingredient operator++(int) {    //post-incrementare
        Ingredient copie = *this;
        this->stoc++;
        return copie;
    }
    int& operator[](int pozitie) {
        return this->stoc;
    }
    operator string() {    //cast la string   
        return this->nume;
    }
    explicit operator int() {    //cast la int  
        return this->stoc;
    }
    Ingredient operator+(int stocSuplimentar) {
        if (stocSuplimentar > 0) {
            Ingredient rez = *this;
            rez.stoc += stocSuplimentar;
            return rez;
        }
        return *this;
    }


    friend bool operator<(const Ingredient& i1, const Ingredient& i2) {
        return i1.stoc < i2.stoc;
    }
};

class Ingredient2:IFile {
private:
    char* nume = nullptr;
    int stoc = 0;

public:
    Ingredient2() : nume(nullptr), stoc(0) {}
    Ingredient2(const char* nume, int stoc)
        : stoc(stoc) {
        if (nume != nullptr) {
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
        }
    }
    Ingredient2(const Ingredient2& i)
        : stoc(i.stoc) {
        if (i.nume != nullptr) {
            this->nume = new char[strlen(i.nume) + 1];
            strcpy(this->nume, i.nume);
        }
    }
    Ingredient2& operator=(const Ingredient2& i) {
        if (this != &i) {
            delete[] this->nume;
            this->nume = nullptr;

            if (i.nume != nullptr) {
                this->nume = new char[strlen(i.nume) + 1];
                strcpy(this->nume, i.nume);
            }
            this->stoc = i.stoc;
        }
        return *this;
    }

    void setNume(const char* newNume) {
        if (newNume != nullptr) {
            delete[] this->nume;
            this->nume = new char[strlen(newNume) + 1];
            strcpy(this->nume, newNume);
        }
        else {
            throw new exception("A fost introdus un nume invalid");
        }
    }

    const char* getNume() const {
        return this->nume;
    }

    int getStoc() const {
        return this->stoc;
    }

    void setStoc(int newStoc) {
        if (newStoc >= 0) {
            this->stoc = newStoc;
        }
        else {
            throw new exception("Stocul nu poate fi negativ");
        }
    }

    void afiseazaDetalii() const {
        cout << "Ingredient2: " << nume << ", Stoc: " << stoc << "\n";
    }

    bool operator==(const Ingredient2& i) const {
        return (strcmp(nume, i.nume) == 0) && (stoc == i.stoc);
    }

    bool operator!=(const Ingredient2& i) const {
        return !(*this == i);
    }

    ~Ingredient2() {
        delete[] nume;
    }

    friend istream& operator>>(istream& in, Ingredient2& ing) {
        delete[] ing.nume;
        ing.nume = nullptr;

        cout << "Introduceti numele ingredientului: ";
        char buffer[100];
        in >> buffer;
        ing.nume = new char[strlen(buffer) + 1];
        strcpy(ing.nume, buffer);

        cout << "Introduceti stocul ingredientului: ";
        in >> ing.stoc;

        return in;
    }

    friend ostream& operator<<(ostream& out, const Ingredient2& i) {
        out << "Ingredient2: " << i.getNume() << ", Stoc: " << i.getStoc() << " unitati\n";
        return out;
    }

    void saveToFile(fstream& file) const {
        int lg = strlen(this->nume) + 1;
        file.write((char*)&lg, sizeof(int));
        file.write(this->nume, lg);
        file.write((char*)&this->stoc, sizeof(int));
    }

    void restoreFromFile(fstream& file) {
        int lg;
        file.read((char*)&lg, sizeof(int));
        char* buffer = new char[lg];
        file.read(buffer, lg);
        nume = new char[strlen(buffer) + 1];
        strcpy(nume, buffer);
        delete[] buffer;
        file.read((char*)&stoc, sizeof(int));
    }
};

class Preparat { //preparatul care apare in meniu
private:
    string denumire;
    Ingredient* retetar;
    int nrIngrediente = 0; //de cate ingrediente am nevoie pt 1 preparat
    int* cantitatiNecesare = nullptr; //cantitatile necesare prepararii
    float pret = 0;

public:
    Preparat() : retetar(nullptr), nrIngrediente(0), cantitatiNecesare(nullptr), pret(0) {}
    Preparat(const string& denumire, Ingredient* retetar, int nrIngrediente, int* cantitatiNecesare, float pret)
        : denumire(denumire), nrIngrediente(nrIngrediente), pret(pret) {

        this->retetar = new Ingredient[this->nrIngrediente];
        this->cantitatiNecesare = new int[this->nrIngrediente];

        for (int i = 0; i < this->nrIngrediente; i++) {
            this->retetar[i] = retetar[i];
            this->cantitatiNecesare[i] = cantitatiNecesare[i];
        }
    }
    Preparat(const Preparat& p)
        : denumire(p.denumire), nrIngrediente(p.nrIngrediente), pret(p.pret) {

        this->retetar = new Ingredient[this->nrIngrediente];
        this->cantitatiNecesare = new int[this->nrIngrediente];

        for (int i = 0; i < this->nrIngrediente; i++) {
            this->retetar[i] = p.retetar[i];
            this->cantitatiNecesare[i] = p.cantitatiNecesare[i];
        }
    }
    Preparat& operator=(const Preparat& p) {
        if (this != &p) {
            this->denumire = p.denumire;

            delete[] this->retetar;
            this->retetar = nullptr;

            delete[] this->cantitatiNecesare;
            this->cantitatiNecesare = nullptr;

            this->nrIngrediente = p.nrIngrediente;

            this->retetar = new Ingredient[this->nrIngrediente];
            this->cantitatiNecesare = new int[this->nrIngrediente];

            for (int i = 0; i < this->nrIngrediente; i++) {
                this->retetar[i] = p.retetar[i];
                this->cantitatiNecesare[i] = p.cantitatiNecesare[i];
            }

            this->pret = p.pret;
        }
        return *this;
    }
    ~Preparat() {
        delete[] retetar;
        delete[] cantitatiNecesare;
    }
    const string& getDenumire() const {
        return this->denumire;
    }
    void setRetetar(Ingredient* newRetetar) {
        retetar = newRetetar;
    }
    Ingredient* getRetetar() const {
        return this->retetar;
    }
    void setNrIngrediente(int newNrIngrediente) {
        if (newNrIngrediente >= 0) {
            nrIngrediente = newNrIngrediente;
        }
        else {
            throw new exception("Nr de ingrediente nu poate fi negativ");
        }
    }
    int getnrIngrediente() const {
        return this->nrIngrediente;
    }
    const int* getCantitatiNecesare() const {
        return this->cantitatiNecesare;
    }
    void setCantitate(int index, int nouaCantitate) {
        if (index >= 0 && index < nrIngrediente) {
            if (nouaCantitate >= 0)
                cantitatiNecesare[index] = nouaCantitate;
        }
        else {
            throw new exception("Index invalid pentru retetar");
        }
    }
    void setPret(float pret) {
        if (pret >= 0) {
            this->pret = pret;
        }
        else
            throw new exception("Pretul nu poate fi negativ");
    }
    float getPret() const {
        return this->pret;
    }

    friend ostream& operator<<(ostream& out, const Preparat& p) {
        out << "\n" << p.denumire << " " << p.pret << " lei";
        /*
        out << "\nIngrediente: \n";
        for (int i = 0; i < p.nrIngrediente; i++) {
            out << " - " << p.retetar[i].getNume() << ": " << p.retetar[i].getStoc() << " unitati in stoc \n";
        }*/

        return out;
    }
    friend istream& operator>>(istream& in, Preparat& p) {
        delete[] p.retetar;
        p.retetar = nullptr;
        delete[] p.cantitatiNecesare;
        p.cantitatiNecesare = nullptr;

        cout << "\nIntroduceti denumirea preparatului: ";
        in >> p.denumire;

        cout << "Introduceti numarul de ingrediente: ";
        in >> p.nrIngrediente;

        if (p.nrIngrediente > 0) {
            p.retetar = new Ingredient[p.nrIngrediente];
            p.cantitatiNecesare = new int[p.nrIngrediente];

            cout << "Introduceti detalii pentru fiecare ingredient:\n";
            for (int i = 0; i < p.nrIngrediente; i++) {
                cout << "Ingrediente[" << i << "]:\n";
                in >> p.retetar[i];
                cout << "Cantitate necesara pentru ingredientul " << p.retetar[i].getNume() << ": ";
                in >> p.cantitatiNecesare[i];
            }
            cout << "Introduceti pretul preparatului: ";
            in >> p.pret;
        }
        return in;
    }

    bool operator!=(const Preparat& p) const {
        return !(*this == p);
    }
    float& operator[](int pozitie) {
        if (pozitie == 0) {
            return this->pret;
        }
        else {
            return this->pret;
        }
    }
    bool operator==(const Preparat& p) const {
        if (this->nrIngrediente != p.nrIngrediente || this->denumire != p.denumire || this->pret != p.pret) {
            return false;
        }
        for (int i = 0; i < this->nrIngrediente; ++i) {
            if (this->retetar[i] != p.retetar[i] || this->cantitatiNecesare[i] != p.cantitatiNecesare[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!() const {
        return this->denumire.empty() || this->nrIngrediente <= 0 || this->pret <= 0;
    }
    bool operator>(const Preparat& p) const {
        return this->pret > p.pret;
    }
    Preparat& operator++() {    // Pre-incrementare
        for (int i = 0; i < this->nrIngrediente; i++) {
            ++(this->retetar[i]);
        }
        return *this;
    }
    Preparat operator++(int) {    // Post-incrementare
        Preparat copie = *this;

        for (int i = 0; i < this->nrIngrediente; i++) {
            this->retetar[i]++;
        }
        return copie;
    }
    operator string() const {
        return this->denumire;
    }
    operator int() const {
        return this->nrIngrediente;
    }
    Preparat& operator+=(int pretSuplimentar) {
        if (pretSuplimentar > 0) {
            this->pret += pretSuplimentar;
        }
        return *this;
    }
    
    void saveToFile(fstream& file) const {
        int lg = this->denumire.length() + 1;
        file.write((char*)&lg, sizeof(int));
        file.write(this->denumire.c_str(), lg);

        file.write((char*)&this->nrIngrediente, sizeof(int));

        for (int i = 0; i < this->nrIngrediente; ++i) {
            this->retetar[i].saveToFile(file);
            file.write((char*)&this->cantitatiNecesare[i], sizeof(int));
        }

        file.write((char*)&this->pret, sizeof(float));
    }

    void restoreFromFile(fstream& file) {
        int lg;
        file.read((char*)&lg, sizeof(int));
        char* buffer = new char[lg];
        file.read(buffer, lg);
        this->denumire = buffer;
        delete[] buffer;

        file.read((char*)&this->nrIngrediente, sizeof(int));

        delete[] this->retetar;
        this->retetar = new Ingredient[this->nrIngrediente];

        delete[] this->cantitatiNecesare;
        this->cantitatiNecesare = new int[this->nrIngrediente];

        for (int i = 0; i < this->nrIngrediente; ++i) {
            this->retetar[i].restoreFromFile(file);
            file.read((char*)&this->cantitatiNecesare[i], sizeof(int));
        }

        file.read((char*)&this->pret, sizeof(float));
    }
    friend bool operator<(const Preparat& p1, const Preparat& p2) {
        return p1.pret < p2.pret;
    }
};

class Preparat2 : public IFile {
private:
    string denumire;
    Ingredient* retetar;
    int nrIngrediente = 0;
    int* cantitatiNecesare = nullptr;
    float pret = 0;

public:
    Preparat2() : retetar(nullptr), nrIngrediente(0), cantitatiNecesare(nullptr), pret(0) {}
    Preparat2(const string& denumire, Ingredient* retetar, int nrIngrediente, int* cantitatiNecesare, float pret)
        : denumire(denumire), nrIngrediente(nrIngrediente), pret(pret) {

        this->retetar = new Ingredient[this->nrIngrediente];
        this->cantitatiNecesare = new int[this->nrIngrediente];

        for (int i = 0; i < this->nrIngrediente; i++) {
            this->retetar[i] = retetar[i];
            this->cantitatiNecesare[i] = cantitatiNecesare[i];
        }
    }
    Preparat2(const Preparat2& p)
        : denumire(p.denumire), nrIngrediente(p.nrIngrediente), pret(p.pret) {

        this->retetar = new Ingredient[this->nrIngrediente];
        this->cantitatiNecesare = new int[this->nrIngrediente];

        for (int i = 0; i < this->nrIngrediente; i++) {
            this->retetar[i] = p.retetar[i];
            this->cantitatiNecesare[i] = p.cantitatiNecesare[i];
        }
    }
    Preparat2& operator=(const Preparat2& p) {
        if (this != &p) {
            this->denumire = p.denumire;

            delete[] this->retetar;
            this->retetar = nullptr;

            delete[] this->cantitatiNecesare;
            this->cantitatiNecesare = nullptr;

            this->nrIngrediente = p.nrIngrediente;

            this->retetar = new Ingredient[this->nrIngrediente];
            this->cantitatiNecesare = new int[this->nrIngrediente];

            for (int i = 0; i < this->nrIngrediente; i++) {
                this->retetar[i] = p.retetar[i];
                this->cantitatiNecesare[i] = p.cantitatiNecesare[i];
            }

            this->pret = p.pret;
        }
        return *this;
    }
    ~Preparat2() {
        delete[] retetar;
        delete[] cantitatiNecesare;
    }
    const string& getDenumire() const {
        return this->denumire;
    }
    void setRetetar(Ingredient* newRetetar) {
        retetar = newRetetar;
    }
    Ingredient* getRetetar() const {
        return this->retetar;
    }
    void setNrIngrediente(int newNrIngrediente) {
        if (newNrIngrediente >= 0) {
            nrIngrediente = newNrIngrediente;
        }
        else {
            throw new exception("Nr de ingrediente nu poate fi negativ");
        }
    }
    int getnrIngrediente() const {
        return this->nrIngrediente;
    }
    const int* getCantitatiNecesare() const {
        return this->cantitatiNecesare;
    }
    void setCantitate(int index, int nouaCantitate) {
        if (index >= 0 && index < nrIngrediente) {
            if (nouaCantitate >= 0)
                cantitatiNecesare[index] = nouaCantitate;
        }
        else {
            throw new exception("Index invalid pentru retetar");
        }
    }
    void setPret(float pret) {
        if (pret >= 0) {
            this->pret = pret;
        }
        else
            throw new exception("Pretul nu poate fi negativ");
    }
    float getPret() const {
        return this->pret;
    }

    friend ostream& operator<<(ostream& out, const Preparat2& p) {
        out << "\n" << p.denumire << " " << p.pret << " lei";

        return out;
    }
    friend istream& operator>>(istream& in, Preparat2& p) {
        delete[] p.retetar;
        p.retetar = nullptr;
        delete[] p.cantitatiNecesare;
        p.cantitatiNecesare = nullptr;

        cout << "\nIntroduceti denumirea preparatului: ";
        in >> p.denumire;

        cout << "Introduceti numarul de ingrediente: ";
        in >> p.nrIngrediente;

        if (p.nrIngrediente > 0) {
            p.retetar = new Ingredient[p.nrIngrediente];
            p.cantitatiNecesare = new int[p.nrIngrediente];

            cout << "Introduceti detalii pentru fiecare ingredient:\n";
            for (int i = 0; i < p.nrIngrediente; i++) {
                cout << "Ingrediente[" << i << "]:\n";
                in >> p.retetar[i];
                cout << "Cantitate necesara pentru ingredientul " << p.retetar[i].getNume() << ": ";
                in >> p.cantitatiNecesare[i];
            }
            cout << "Introduceti pretul preparatului: ";
            in >> p.pret;
        }
        return in;
    }

    bool operator!=(const Preparat2& p) const {
        return !(*this == p);
    }
    float& operator[](int pozitie) {
        if (pozitie == 0) {
            return this->pret;
        }
        else {
            return this->pret;
        }
    }
    bool operator==(const Preparat2& p) const {
        if (this->nrIngrediente != p.nrIngrediente || this->denumire != p.denumire || this->pret != p.pret) {
            return false;
        }
        for (int i = 0; i < this->nrIngrediente; ++i) {
            if (this->retetar[i] != p.retetar[i] || this->cantitatiNecesare[i] != p.cantitatiNecesare[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!() const {
        return this->denumire.empty() || this->nrIngrediente <= 0 || this->pret <= 0;
    }
    bool operator>(const Preparat2& p) const {
        return this->pret > p.pret;
    }
    Preparat2& operator++() {    // Pre-incrementare
        for (int i = 0; i < this->nrIngrediente; i++) {
            ++(this->retetar[i]);
        }
        return *this;
    }

    operator string() const {
        return this->denumire;
    }
    operator int() const {
        return this->nrIngrediente;
    }
    Preparat2& operator+=(int pretSuplimentar) {
        if (pretSuplimentar > 0) {
            this->pret += pretSuplimentar;
        }
        return *this;
    }

    void saveToFile(fstream& file) const {
        int lg = this->denumire.length() + 1;
        file.write((char*)&lg, sizeof(int));
        file.write(this->denumire.c_str(), lg);

        file.write((char*)&this->nrIngrediente, sizeof(int));

        for (int i = 0; i < this->nrIngrediente; ++i) {
            this->retetar[i].saveToFile(file);
            file.write((char*)&this->cantitatiNecesare[i], sizeof(int));
        }

        file.write((char*)&this->pret, sizeof(float));
    }

    void restoreFromFile(fstream& file) {
        int lg;
        file.read((char*)&lg, sizeof(int));
        char* buffer = new char[lg];
        file.read(buffer, lg);
        this->denumire = buffer;
        delete[] buffer;

        file.read((char*)&this->nrIngrediente, sizeof(int));

        delete[] this->retetar;
        this->retetar = new Ingredient[this->nrIngrediente];

        delete[] this->cantitatiNecesare;
        this->cantitatiNecesare = new int[this->nrIngrediente];

        for (int i = 0; i < this->nrIngrediente; ++i) {
            this->retetar[i].restoreFromFile(file);
            file.read((char*)&this->cantitatiNecesare[i], sizeof(int));
        }

        file.read((char*)&this->pret, sizeof(float));
    }

    friend bool operator<(const Preparat2& p1, const Preparat2& p2) {
        return p1.pret < p2.pret;
    }
};

class Meniu { //meniul restaurantului
private:
    Preparat* preparate;
    int nrPreparate;

public:
    Meniu() : preparate(nullptr), nrPreparate(0) {}
    Meniu(Preparat* preparate, int nrPreparate) : nrPreparate(nrPreparate) {
        this->preparate = new Preparat[this->nrPreparate];
        for (int i = 0; i < this->nrPreparate; i++)
            this->preparate[i] = preparate[i];
    }
    Meniu(const Meniu& m) : nrPreparate(m.nrPreparate) {
        this->preparate = new Preparat[this->nrPreparate];
        for (int i = 0; i < this->nrPreparate; i++)
            this->preparate[i] = m.preparate[i];
    }
    Meniu& operator=(const Meniu& m) {
        if (this != &m) {
            delete[] this->preparate;
            this->preparate = nullptr;

            this->nrPreparate = m.nrPreparate;
            this->preparate = new Preparat[this->nrPreparate];
            for (int i = 0; i < this->nrPreparate; i++)
                this->preparate[i] = m.preparate[i];
        }
        return *this;
    }
    void setNrPreparate(int newNrPreparate) {
        if (newNrPreparate >= 0) {
            nrPreparate = newNrPreparate;
        }
        else {
            throw new exception("Nr de preparate nu poate fi negativ");
        }
    }
    int getNrPreparate() const {
        return nrPreparate;
    }
    Preparat* getPreparate() const {
        return preparate;
    }
    void adaugaPreparat(const Preparat& preparat) {
        if (preparat.getnrIngrediente() > 0) {
            Preparat* copiePreparate = new Preparat[nrPreparate + 1];

            for (int i = 0; i < nrPreparate; ++i) {
                copiePreparate[i] = preparate[i];
            }

            delete[] preparate;
            preparate = copiePreparate;
            nrPreparate++;
        }
        else {
            throw new exception("Preparatul trebuie sa aiba un ingredient");
        }

    }
    const Preparat* gasestePreparatDupaNume(const string& nume) const {
        for (int i = 0; i < nrPreparate; i++) {
            if (preparate[i].getDenumire() == nume) {
                return &preparate[i];
            }
        }
        return nullptr;
    }
    ~Meniu() {
        delete[] preparate;
    }
    friend ostream& operator<<(ostream& out, const Meniu& m) {
        out << "\nMeniul contine " << m.nrPreparate << " preparate: \n";
        out << "\nPreparate: ";
        for (int i = 0; i < m.nrPreparate; i++)
            out << m.preparate[i];
        return out;
    }

    friend istream& operator>>(istream& in, Meniu& m) {
        delete[] m.preparate;
        m.preparate = nullptr;

        cout << "Introduceti numarul de preparate din meniu: ";
        in >> m.nrPreparate;

        if (m.nrPreparate > 0) {
            m.preparate = new Preparat[m.nrPreparate];

            cout << "Introduceti detalii pentru fiecare preparat:\n";
            for (int i = 0; i < m.nrPreparate; i++) {
                cout << "Preparatul [" << i << "]:\n";
                in >> m.preparate[i];
            }
        }
        return in;
    }

    void actualizeareStoc(const Preparat& preparat, int cantitate) {
        for (int i = 0; i < preparat.getnrIngrediente(); i++) {
            const Ingredient& ingredient = preparat.getRetetar()[i];
            int cantitateNecesara = preparat.getCantitatiNecesare()[i] * cantitate;
            const_cast<Ingredient&>(ingredient).setStoc(ingredient.getStoc() - cantitateNecesara);
        }
    }
    bool operator==(const Meniu& m) const {
        if (nrPreparate != m.nrPreparate) {
            return false;
        }

        for (int i = 0; i < nrPreparate; ++i) {
            if (preparate[i] != m.preparate[i]) {
                return false;
            }
        }

        return true;
    }
    bool operator!=(const Meniu& m) const {
        return !(*this == m);
    }
    bool operator!() const {
        return (this->nrPreparate == 0 || this->preparate == nullptr);
    }
    bool operator>=(const Meniu& m) const {
        return this->nrPreparate >= m.nrPreparate;
    }
    Preparat& operator[](int k) {
        if (k >= 0 && k < nrPreparate)
            return preparate[k];
    }
    Meniu& operator++() {    // Pre-incrementare
        for (int i = 0; i < this->nrPreparate; i++) {
            ++(this->preparate[i]);
        }
        return *this;
    }
    Meniu operator++(int) {    // Post-incrementare
        Meniu copie = *this;
        for (int i = 0; i < this->nrPreparate; i++) {
            this->preparate[i]++;
        }
        return copie;
    }
    operator int() const {
        return this->nrPreparate;
    }
    
    void saveToFile(fstream& file) const {
        file.write((char*)&this->nrPreparate, sizeof(int));

        for (int i = 0; i < this->nrPreparate; ++i) {
            this->preparate[i].saveToFile(file);
        }
    }
    void restoreFromFile(fstream& file) {
        delete[] this->preparate;
        this->preparate = nullptr;

        file.read((char*)&this->nrPreparate, sizeof(int));

        if (this->nrPreparate > 0) {
            this->preparate = new Preparat[this->nrPreparate];

            for (int i = 0; i < this->nrPreparate; ++i) {
                this->preparate[i].restoreFromFile(file);
            }
        }
    }
    void saveCSV(const string& numeFisier, char separator) const {
        ofstream h(numeFisier);
        if (!h.is_open()) {
            std::cerr << "Nu am putut deschide fisierul " << numeFisier << std::endl;
            return;
        }

        h << "Denumire" << separator << "Pret" << separator << "Nr. ingrediente" << separator << "Ingrediente\n";

        for (int i = 0; i < nrPreparate; ++i) {
            const Preparat& preparat = preparate[i];
            h << preparat.getDenumire() << separator << preparat.getPret() << separator << preparat.getnrIngrediente() << separator;

            for (int j = 0; j < preparat.getnrIngrediente(); ++j) {
                const Ingredient& ingredient = preparat.getRetetar()[j];
                h << ingredient.getNume() << "(" << ingredient.getId() << ")" << ", ";
            }

            h << "\n";
        }

        h.close();
    }
    /*
    void restoreCSV(const string& numeFisier) {
        ifstream h(numeFisier);
        string line;
        getline(h, line);
        while (getline(h, line)) {
            stringstream datePreparat(line);
            string buffer;

            string denumire;
            getline(datePreparat, denumire, ',');

            getline(datePreparat, buffer, ',');
            float pret = stof(buffer);

            getline(datePreparat, buffer, ',');
            int nrIngrediente = stoi(buffer);
        }
        h.close();
    }*/
    friend bool operator<(const Meniu& m1, const Meniu& m2) {
        return m1.nrPreparate < m2.nrPreparate;
    }
};

class Comanda { //comanda introdusa de la tastatura
private:
    Preparat* preparate = nullptr;
    int nrPreparate = 0;
    Meniu meniu; //pt a afisa stocul ramas
    float pretTotal;
    //static int comandaMinima;
public:
    Comanda() : preparate(nullptr), nrPreparate(0) {}
    Comanda(const Comanda& c) : nrPreparate(c.nrPreparate) {
        this->preparate = new Preparat[this->nrPreparate];
        for (int i = 0; i < this->nrPreparate; i++)
            this->preparate[i] = c.preparate[i];
    }
    Comanda& operator=(const Comanda& c) {
        if (this != &c) {
            delete[] this->preparate;
            this->preparate = nullptr;

            this->nrPreparate = c.nrPreparate;
            this->preparate = new Preparat[this->nrPreparate];
            for (int i = 0; i < this->nrPreparate; i++)
                this->preparate[i] = c.preparate[i];
        }
        return *this;
    }
    ~Comanda() {
        delete[] preparate;
    }
    void adaugaPreparat(const Preparat& preparat, int cantitate) {
        if (cantitate > 0) {
            bool preparatExistent = false;
            for (int i = 0; i < nrPreparate; i++) {
                if (preparate[i] == preparat) {
                    preparate[i].setCantitate(0, preparate[i].getCantitatiNecesare()[0] + cantitate);
                    preparatExistent = true;
                    break;
                }
            }

            if (!preparatExistent) {
                Preparat* copie = new Preparat[nrPreparate + 1];
                for (int i = 0; i < nrPreparate; ++i) {
                    copie[i] = preparate[i];
                }
                copie[nrPreparate] = preparat;
                copie[nrPreparate].setCantitate(0, cantitate);
                nrPreparate++;

                delete[] preparate;
                preparate = copie;

                meniu.actualizeareStoc(preparat, cantitate);
                pretTotal += preparat.getPret() * cantitate;
            }
        }
    }
    void setNrPreparate(int newNrPreparate) {
        if (newNrPreparate >= 0) {
            nrPreparate = newNrPreparate;
        }
        else {
            throw new exception("Nr preparatelor nu poate fi negativ");
        }
    }
    int getNrPreparate() const {
        return nrPreparate;
    }
    const Preparat* getPreparate() const {
        return preparate;
    }
    void setPretTotal(float newPretTotal) {
        if (newPretTotal >= 0) {
            pretTotal = newPretTotal;
        }
        else {
            throw new exception("Pretul nu poate fi negativ");
        }
    }
    float getPretTotal() const {
        return pretTotal;
    }
    /*static int getComandaMinima() {
        return comandaMinima;
    }*/
    friend ostream& operator<<(ostream& out, const Comanda& c) {
        out << "Ati comandat " << c.nrPreparate << " preparate:\n";
        for (int i = 0; i < c.nrPreparate; i++) {
            out << "- " << c.preparate[i].getCantitatiNecesare()[0] << " " << c.preparate[i].getDenumire() << "\n";
        }
        out << "\nIn valoare de: " << c.getPretTotal() << " lei\n";
        return out;
    }
    bool verificaStoc(const Preparat& preparat, int cantitate) const {
        for (int i = 0; i < preparat.getnrIngrediente(); i++) {
            const Ingredient& ingredient = preparat.getRetetar()[i];
            int cantitateNecesara = preparat.getCantitatiNecesare()[i] * cantitate;

            if (ingredient.getStoc() < cantitateNecesara) {
                return false;  // stoc insuficient
            }
        }
        return true;
    }
    /*
    void preiaComanda(const Meniu& meniu) { //preiaComanda fara optiune de intoarcere original
        cout << "\nIntroduceti comanda (numele preparatelor se scrie cu virgula intre ele si ENTER pentru a plasa comanda): \n";
        string inputComanda;
        getline(cin, inputComanda);

        // Cauta virgulele in inputComanda si extrage preparatele
        size_t poz = 0;
        string numePreparat;

        while ((poz = inputComanda.find(',')) != string::npos) {
            numePreparat = inputComanda.substr(0, poz);
            inputComanda.erase(0, poz + 1);

            int cantitate;
            cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
            cin >> cantitate;
            cin.ignore();

            const Preparat* preparat = meniu.gasestePreparatDupaNume(numePreparat);
            if (preparat != nullptr) {
                if (verificaStoc(*preparat, cantitate)) {
                    adaugaPreparat(*preparat, cantitate);
                    cout << "Preparat adaugat in comanda\n";
                }
                else {
                    cout << "\nNu exista suficiente ingrediente in stoc pentru " << numePreparat;
                }
            }
            else {
                cout << "Preparatul \"" << numePreparat << "\" nu exista in meniu.\n";
            }
        }

        // Procesam ultimul preparat (fara virgula la sf)
        if (!inputComanda.empty()) {
            numePreparat = inputComanda;
            int cantitate;
            cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
            cin >> cantitate;
            cin.ignore();

            const Preparat* preparat = meniu.gasestePreparatDupaNume(numePreparat);
            if (preparat != nullptr) {
                if (verificaStoc(*preparat, cantitate)) {
                    adaugaPreparat(*preparat, cantitate);
                    cout << "Preparat adaugat in comanda\n";
                }
                else {
                    cout << "Nu exista suficiente ingrediente in stoc pentru " << numePreparat << ".\n";
                }
            }
            else {
                cout << "Preparatul \"" << numePreparat << "\" nu exista in meniu.\n";
            }
        }
    }
    */
    void preiaComanda(const Meniu& meniu) {
        bool refacereComanda = false;

        do {
            // Resetează comanda curentă
            delete[] preparate;
            preparate = nullptr;
            nrPreparate = 0;
            pretTotal = 0;

            cout << "\nIntroduceti comanda (numele preparatelor se scrie cu virgula intre ele si ENTER pentru a plasa comanda): \n";
            string inputComanda;
            getline(cin, inputComanda);

            // Cauta virgulele in inputComanda si extrage preparatele
            size_t poz = 0;
            string numePreparat;

            while ((poz = inputComanda.find(',')) != string::npos) {
                numePreparat = inputComanda.substr(0, poz);
                inputComanda.erase(0, poz + 1);

                int cantitate;
                cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
                cin >> cantitate;
                cin.ignore();

                const Preparat* preparat = meniu.gasestePreparatDupaNume(numePreparat);
                if (preparat != nullptr) {
                    if (verificaStoc(*preparat, cantitate)) {
                        adaugaPreparat(*preparat, cantitate);
                        cout << "Preparat adaugat in comanda\n";
                    }
                    else {
                        cout << "Nu exista suficiente ingrediente in stoc pentru " << numePreparat << ".\n";
                        cout << "Doriti sa anulati comanda sau sa o refaceti de la capat? (A/R): ";
                        char optiune;
                        cin >> optiune;
                        cin.ignore();
                        if (optiune == 'a' || optiune == 'A') {
                            cout << "Comanda anulata.\n";
                            return;
                        }
                        else if (optiune == 'r' || optiune == 'R') {
                            refacereComanda = true;
                            break;  // Ieșim din bucla curentă
                        }
                    }
                }
                else {
                    cout << "Preparatul \"" << numePreparat << "\" nu exista in meniu.\n";
                }
            }

            // Procesam ultimul preparat (fara virgula la sf)
            if (!inputComanda.empty()) {
                numePreparat = inputComanda;
                int cantitate;
                cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
                cin >> cantitate;
                cin.ignore();

                const Preparat* preparat = meniu.gasestePreparatDupaNume(numePreparat);
                if (preparat != nullptr) {
                    if (verificaStoc(*preparat, cantitate)) {
                        adaugaPreparat(*preparat, cantitate);
                        cout << "Preparat adaugat in comanda\n";
                    }
                    else {
                        cout << "Nu exista suficiente ingrediente in stoc pentru " << numePreparat << ".\n";
                        cout << "Doriti sa anulati comanda sau sa o refaceti de la capat? (A/R): ";
                        char optiune;
                        cin >> optiune;
                        cin.ignore();
                        if (optiune == 'a' || optiune == 'A') {
                            cout << "Comanda anulata.\n";
                            refacereComanda = false;
                            return;
                        }
                        else if (optiune == 'r' || optiune == 'R') {
                            preiaComanda(meniu);
                            refacereComanda = true;
                            break;  // Ieșim din bucla curentă
                        }
                    }
                }
                else {
                    cout << "Preparatul \"" << numePreparat << "\" nu exista in meniu.\n";
                }
            }

        } while (refacereComanda);
    }

    friend istream& operator>>(istream& in, Comanda& comanda) {
        cout << "\nIntroduceti comanda (numele preparatelor se scrie cu virgula intre ele si ENTER pentru a plasa comanda): \n";
        string inputComanda;
        getline(in, inputComanda);

        size_t poz = 0; //
        string numePreparat;

        while ((poz = inputComanda.find(',')) != string::npos) {
            numePreparat = inputComanda.substr(0, poz);
            inputComanda.erase(0, poz + 1);

            int cantitate;
            cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
            in >> cantitate;
            in.ignore();

            const Preparat* preparat = comanda.meniu.gasestePreparatDupaNume(numePreparat);
            if (preparat != nullptr) {
                if (comanda.verificaStoc(*preparat, cantitate)) {
                    comanda.adaugaPreparat(*preparat, cantitate);
                    cout << "Preparat adaugat in comanda\n";
                }
                else {
                    cout << "\nNu exista suficiente ingrediente in stoc pentru " << numePreparat;
                }
            }
            else {
                cout << "Preparatul \"" << numePreparat << "\" nu exista in meniu.\n";
            }
        }
        // Procesam ultimul preparat fara virgula la sf
        if (!inputComanda.empty()) {
            numePreparat = inputComanda;
            int cantitate;
            cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
            in >> cantitate;
            in.ignore();

            const Preparat* preparat = comanda.meniu.gasestePreparatDupaNume(numePreparat);
            if (preparat != nullptr) {
                if (comanda.verificaStoc(*preparat, cantitate)) {
                    comanda.adaugaPreparat(*preparat, cantitate);
                    cout << "Preparat adaugat in comanda\n";
                }
                else {
                    cout << "Nu exista suficiente ingrediente in stoc pentru " << numePreparat << ".\n";
                }
            }
            else {
                cout << "Preparatul \"" << numePreparat << "\" nu exista in meniu.\n";
            }
        }

        return in;
    }

    bool operator==(const Comanda& c) const {
        if (this->nrPreparate != c.nrPreparate) {
            return false;
        }

        for (int i = 0; i < this->nrPreparate; ++i) {
            if (this->preparate[i] != c.preparate[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Comanda& c) const {
        return !(*this == c);
    }
    bool operator!() const {
        return (this->nrPreparate == 0 || this->preparate == nullptr);
    }
    bool operator>=(const Comanda& c) const {
        return this->nrPreparate >= c.nrPreparate;
    }
    float& operator[](int) {
        return this->pretTotal;
    }
    Comanda& operator++() {    // Pre-incrementare
        for (int i = 0; i < this->nrPreparate; i++) {
            ++(this->preparate[i]);
        }
        return *this;
    }

    Comanda operator++(int) {    // Post-incrementare
        Comanda copie = *this;
        for (int i = 0; i < this->nrPreparate; i++) {
            this->preparate[i]++;
        }
        return copie;
    }
    operator int() const {
        return this->nrPreparate;
    }
    void saveToFile(fstream& file) const {
        file.write((char*)&this->nrPreparate, sizeof(int));
        file.write((char*)&this->pretTotal, sizeof(float));

        for (int i = 0; i < this->nrPreparate; ++i) {
            this->preparate[i].saveToFile(file);
        }
    }
    void restoreFromFile(fstream& file) {
        delete[] this->preparate;
        this->preparate = nullptr;

        file.read((char*)&this->nrPreparate, sizeof(int));
        file.read((char*)&this->pretTotal, sizeof(float));

        if (this->nrPreparate > 0) {
            this->preparate = new Preparat[this->nrPreparate];

            for (int i = 0; i < this->nrPreparate; ++i) {
                this->preparate[i].restoreFromFile(file);
            }
        }
    }
};

class Restaurant { //afiseaza stocul de ingrediente(materii prime) ramas dupa comanda
private:
    Meniu meniu;
    Comanda comanda;

public:
    Restaurant() {}

    Restaurant(Meniu meniu, Comanda comanda) : meniu(meniu), comanda(comanda) {}

    Restaurant(const Restaurant& r) : meniu(r.meniu), comanda(r.comanda) {}

    Restaurant& operator=(const Restaurant& r) {
        if (this != &r) {
            this->meniu = r.meniu;
            this->comanda = r.comanda;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Restaurant& r) {
        out << "Stocul de ingrediente ramase:\n";
        for (int i = 0; i < r.meniu.getNrPreparate(); ++i) {
            const Preparat& preparat = r.meniu.getPreparate()[i];
            for (int j = 0; j < preparat.getnrIngrediente(); ++j) {
                const Ingredient& ingredient = preparat.getRetetar()[j];
                out << "- " << ingredient.getNume() << ": " << ingredient.getStoc() << " unitati\n";
            }
        }

        return out;
    }
    void preiaComanda() {
        cout << "Introduceti comanda: ";
        string numePreparat;
        int cantitate;

        while (true) {
            cin >> numePreparat;

            if (numePreparat == "0") {
                cout << "Comanda terminata.\n";
                break;
            }
            bool preparatExistent = false;
            for (int i = 0; i < meniu.getNrPreparate(); i++) {
                if (meniu.getPreparate()[i].getDenumire() == numePreparat) {
                    preparatExistent = true;

                    if (verificaStoc(meniu.getPreparate()[i], cantitate)) {
                        comanda.adaugaPreparat(meniu.getPreparate()[i], 1);
                        cout << "\nPreparat adaugat in comanda";
                    }
                    else {
                        cout << "Nu exista suficiente ingrediente in stoc pentru " << numePreparat << ".\n";
                    }
                    break;
                }
            }
            if (!preparatExistent) {
                cout << "Preparatul " << numePreparat << " nu exista in meniu.\n";
            }

            cout << "Introduceti urmatorul preparat (sau 0 pentru a termina): ";
        }
    }
    friend istream& operator>>(istream& in, Restaurant& restaurant) {
        cout << "Introduceti comanda pentru restaurant (introduceti 0 pentru a termina comanda):\n";

        while (true) {
            cout << "Introduceti numele preparatului sau 0 pentru a termina comanda: ";
            string numePreparat;
            in >> numePreparat;

            if (numePreparat == "0") {
                cout << "Comanda terminata.\n";
                break;
            }

            int cantitate;

            cout << "Introduceti cantitatea pentru " << numePreparat << ": ";
            in >> cantitate;

            bool preparatExistent = false;

            for (int i = 0; i < restaurant.meniu.getNrPreparate(); i++) {
                if (restaurant.meniu.getPreparate()[i].getDenumire() == numePreparat) {
                    preparatExistent = true;

                    if (restaurant.verificaStoc(restaurant.meniu.getPreparate()[i], cantitate)) {
                        restaurant.comanda.adaugaPreparat(restaurant.meniu.getPreparate()[i], 1);
                        cout << "\nPreparat adaugat in comanda\n";
                    }
                    else {
                        cout << "Nu exista suficiente ingrediente in stoc pentru " << numePreparat << ".\n";
                    }
                    break;
                }
            }

            if (!preparatExistent) {
                cout << "Preparatul " << numePreparat << " nu exista in meniu.\n";
            }
        }

        return in;
    }

    // Metoda pentru a verifica stocul pentru un anumit preparat și o cantitate
    bool verificaStoc(const Preparat& preparat, int cantitate) const {
        for (int i = 0; i < preparat.getnrIngrediente(); i++) {
            const Ingredient& ingredient = preparat.getRetetar()[i];
            int cantitateNecesara = preparat.getCantitatiNecesare()[i] * cantitate;

            if (ingredient.getStoc() < cantitateNecesara) {
                return false;  // Nu exista suficient stoc pentru ingredient i
            }
        }
        return true;  // Stoc suficient pentru toate ingredentele
    }

    bool operator!() const {
        return !this->comanda;
    }
    bool operator<=(const Restaurant& r) const {
        return this->meniu.getNrPreparate() <= r.meniu.getNrPreparate();
    }
    Preparat& operator[](int poz) {
        if (poz >= 0 && poz < this->meniu.getNrPreparate()) {
            return this->meniu.getPreparate()[poz];
        }
        else
            return this->meniu.getPreparate()[0];
    }
    Restaurant& operator++() {    // Pre-incrementare
        ++(this->meniu);
        ++(this->comanda);
        return *this;
    }

    Restaurant operator++(int) {    // Post-incrementare
        Restaurant copie = *this;
        this->meniu++;
        this->comanda++;
        return copie;
    }
    operator int() const {
        return this->meniu.getNrPreparate();
    }
    void saveToFile(const string& fileName) const {
        fstream file(fileName, ios::out | ios::binary);
        if (!file.is_open()) {
            cerr << "Eroare la deschiderea fisierului pentru scriere.\n";
            return;
        }

        this->meniu.saveToFile(file);
        this->comanda.saveToFile(file);

        file.close();
    }
    void restoreFromFile(const string& fileName) {
        fstream file(fileName, ios::in | ios::binary);
        if (!file.is_open()) {
            cerr << "Eroare la deschiderea fisierului pentru citire.\n";
            return;
        }

        this->meniu.restoreFromFile(file);
        this->comanda.restoreFromFile(file);

        file.close();
    }
};

class WishListPrep {
    Preparat* listaPrep;
    int nrPrep;

    vector<Preparat> vPrep;
};
/*
class PreparatVirtual : public IFile {
    string denumire;
    Preparat preparat;

public:
    PreparatVirtual(const string& denumire) : denumire(denumire) {}

    void saveToFile(fstream& file) const {
        int lg = this->denumire.length() + 1;
        file.write((char*)&lg, sizeof(int));
        file.write(this->denumire.c_str(), lg);
        preparat.saveToFile(file); // Salvare Preparat
    }

    void restoreFromFile(fstream& file) {
        int lg;
        file.read((char*)&lg, sizeof(int));
        char* buffer = new char[lg];
        file.read(buffer, lg);
        this->denumire = buffer;
        delete[] buffer;
        preparat.restoreFromFile(file); // Restaurare Preparat
    }

    const string& getDenumirePreparat() const {
        return preparat.getDenumire();
    }
};
*/
int main(int argc, char* argv[]) {
    string commandArg;
    for (int i = 1; i < argc; i++) {
        commandArg += argv[i];
        if (i < argc - 1)
            commandArg += " ";
    }

    Ingredient toateIngrediente[] = {
      Ingredient(1, "Carne de vita", 10),
      Ingredient(2, "Chifla", 10),
      Ingredient(3, "Salata", 10),
      Ingredient(5, "Sos special", 10),
      Ingredient(6, "Aluat", 10),
      Ingredient(7, "Sos de rosii", 10),
      Ingredient(8, "Mozzarella", 10),
      Ingredient(9, "Busuioc", 10),
      Ingredient(10, "Paste", 10),
      Ingredient(11, "Sos de carne tocat", 10),
      Ingredient(12, "Rosii", 10),
      Ingredient(13, "Busuioc", 10),
      Ingredient(14, "Legume", 10),
      Ingredient(15, "Bulion", 10),
      Ingredient(16, "Condimente", 10),
      Ingredient(17, "Ciocolata", 10),
      Ingredient(18, "Vanilie", 10),
      Ingredient(19, "Faina", 10),
      Ingredient(20, "Zahar", 10),
      Ingredient(21, "Oua", 10),
      Ingredient(22, "Apa de izvor", 10)
    };

    Ingredient ingredienteBurger[4] = {
        Ingredient(1, "Carne de vita", 10),
        Ingredient(2, "Chifla", 10),
        Ingredient(3, "Salata", 10),
        Ingredient(5, "Sos special", 10),
    };

    int* cantitatiNecesareBurger = new int[4] {1, 1, 1, 1};
    Preparat preparatBurger("Burger", ingredienteBurger, 4, cantitatiNecesareBurger, 30.0);

    Ingredient ingredientePizza[4] = {
        Ingredient(6, "Aluat", 10),
        Ingredient(7, "Sos de rosii", 10),
        Ingredient(8, "Mozzarella", 10),
        Ingredient(9, "Busuioc", 10)
    };

    int* cantitatiNecesarePizza = new int[4] {1, 1, 1, 1};
    Preparat preparatPizza("Pizza", ingredientePizza, 4, cantitatiNecesarePizza, 25.0);

    Ingredient ingredientePaste[4] = {
        Ingredient(10, "Paste", 10),
        Ingredient(11, "Sos de carne tocat", 10),
        Ingredient(12, "Rosii", 10),
        Ingredient(13, "Busuioc", 10)
    };

    int* cantitatiNecesarePaste = new int[4] {1, 1, 1, 1};
    Preparat preparatPaste("Paste", ingredientePaste, 4, cantitatiNecesarePaste, 20.0);

    Ingredient ingredienteSupa[3] = {
        Ingredient(14, "Legume", 10),
        Ingredient(15, "Bulion", 10),
        Ingredient(16, "Condimente", 10)
    };

    int* cantitatiNecesareSupa = new int[3] {1, 1, 1};
    Preparat preparatSupa("Supa", ingredienteSupa, 3, cantitatiNecesareSupa, 17.0);

    Ingredient ingredientePrajitura[5] = {
        Ingredient(17, "Ciocolata", 10),
        Ingredient(18, "Vanilie", 10),
        Ingredient(19, "Faina", 10),
        Ingredient(20, "Zahar", 10),
        Ingredient(21, "Oua", 10)
    };

    int* cantitatiNecesarePrajitura = new int[5] {1, 1, 1, 1, 1};
    Preparat preparatPrajitura("Prajitura", ingredientePrajitura, 5, cantitatiNecesarePrajitura, 21.0);

    Ingredient ingredienteApa[1] = {
    Ingredient(22, "Apa de izvor", 10)
    };

    int* cantitatiNecesareApa = new int[1] {1};
    Preparat preparatApa("Apa", ingredienteApa, 1, cantitatiNecesareApa, 6.0);


    Preparat preparateArray[6] = { preparatBurger, preparatPizza, preparatPaste, preparatSupa, preparatPrajitura, preparatApa };
    Meniu meniu(preparateArray, 6);
    //cout << meniu;

    ofstream g("meniu.txt");
    //cout << "\nMeniul contine " << 6 << " preparate: \n";
    //cout << preparatBurger << preparatPizza << preparatPaste << preparatSupa << preparatPrajitura << preparatApa; 
    g << meniu;
    cout << meniu;

    for (int i = 0; i < meniu.getNrPreparate(); i++) {
        const Preparat& preparat = meniu.getPreparate()[i];
        const Ingredient* retetar = preparat.getRetetar();

        for (int j = 0; j < preparat.getnrIngrediente(); j++) {
            g << retetar[j];
        }
    }
    g.close();

    Comanda comanda;
    comanda.preiaComanda(meniu);

    cout << "\n" << comanda << endl;
    Restaurant restaurant(meniu, comanda);

    cout << "Starea finala a restaurantului dupa comanda: \n" << restaurant;


    cout << "Doresti sa afisezi STL-urile? (D/N): ";
    string rasp;
    cin >> rasp;
    if (rasp == "d" || rasp == "D") {
        cout << "\n-------------STL VECTOR----------------------\n";
        vector<int> vInt;
        vInt.push_back(1);
        vInt.push_back(3);
        vInt.push_back(6);
        for (int i = 0; i < vInt.size(); i++)
            cout << vInt[i] << " ";
        vector<int>::iterator it;
        cout << endl;
        for (it = vInt.begin(); it != vInt.end(); it++)
            cout << *it << " ";
        cout << "\n-------------STL LIST----------------------\n";
        list<float> lFloat;
        lFloat.push_back(30);
        lFloat.push_front(25);
        lFloat.push_front(20);
        lFloat.push_front(17);
        lFloat.push_front(21);
        lFloat.push_front(6);
        list<float>::iterator itList;
        for (itList = lFloat.begin(); itList != lFloat.end(); itList++)
            cout << *itList << " ";
        list<float>::reverse_iterator rItList;
        cout << endl;
        for (rItList = lFloat.rbegin(); rItList != lFloat.rend(); rItList++)
            cout << *rItList << " ";
        cout << "\n-------------STL SET----------------------\n";
        set<string> setString;
        setString.insert("Burger");
        setString.insert("Pizza");
        setString.insert("Paste");
        setString.insert("Supa");
        setString.insert("Prajitura");
        setString.insert("Apa");

        set<std::string>::iterator itSet;
        for (itSet = setString.begin(); itSet != setString.end(); itSet++)
            std::cout << *itSet << " ";

        Preparat p1("Burger", ingredienteBurger, 4, cantitatiNecesareBurger, 30.0);
        Preparat p2("Pizza", ingredientePizza, 4, cantitatiNecesarePizza, 25.0);
        Preparat p3("Paste", ingredientePaste, 4, cantitatiNecesarePaste, 20.0);
        Preparat p4("Supa", ingredienteSupa, 3, cantitatiNecesareSupa, 17.0);
        Preparat p5("Prajitura", ingredientePrajitura, 5, cantitatiNecesarePrajitura, 21.0);
        Preparat p6("Apa", ingredienteApa, 1, cantitatiNecesareApa, 6.0);

        set<Preparat> setPrep;
        setPrep.insert(p1);
        setPrep.insert(p2);
        setPrep.insert(p3);
        setPrep.insert(p4);
        setPrep.insert(p5);
        setPrep.insert(p6);

        set<Preparat>::iterator itSet2;
        for (itSet2 = setPrep.begin(); itSet2 != setPrep.end(); itSet2++)
            cout << *itSet2 << " ";

        itSet2 = setPrep.find(p5);
        if (itSet2 != setPrep.end())
            cout << "\nS-a gasit " << *itSet2 << " in set";
        else
            cout << "\nNu s-a gasit " << p2 << " in set";
        cout << "\n-------------STL MAP----------------------\n";
        map<int, Preparat> mapPrep;
        mapPrep[5] = p1;
        mapPrep[10] = p2;
        mapPrep[15] = p3;
        mapPrep[20] = p3;
        map<int, Preparat>::iterator itMap;
        for (itMap = mapPrep.begin(); itMap != mapPrep.end(); itMap++)
            cout << endl << itMap->first << " " << itMap->second;
    }
    else if (rasp == "n" || rasp == "N") {}


    delete[] cantitatiNecesareBurger;
    delete[] cantitatiNecesarePizza;
    delete[] cantitatiNecesarePaste;
    delete[] cantitatiNecesareSupa;
    delete[] cantitatiNecesarePrajitura;
    delete[] cantitatiNecesareApa;

    //IFile file;
    IFile* filePointer;

    /*
    fstream file1("ingredient.bin", ios::out | ios::binary);
    Ingredient ingredient;
    ingredient.saveToFile(file1);
    file1.close();

    fstream file2("preparat.bin", ios::out | ios::binary);
    Preparat preparatRest;
    preparatRest.saveToFile(file2);
    file2.close();

    fstream file3("meniu.bin", ios::out | ios::binary);
    meniu.saveToFile(file3);
    file3.close();

    fstream file4("ingredient.bin", ios::in | ios::binary);
    Ingredient ingredientR;
    ingredientR.restoreFromFile(file4);
    file4.close();

    fstream file5("preparat.bin", ios::out | ios::binary);
    Preparat preparatR;
    preparatR.restoreFromFile(file5);
    file5.close();

    fstream file6("meniu.bin", ios::in | ios::binary);
    Meniu meniuR;
    meniuR.restoreFromFile(file6);
    // cout << meniuRestaurant;
    file6.close();*/

    meniu.saveCSV("meniu.csv", ',');

    /*
    fstream file("preparate_virtuale.bin", ios::out | ios::binary);
    PreparatVirtual prep("Burger", ingredienteBurger, 4, cantitatiNecesareBurger, 30.0);
    prep.saveToFile(file);
    file.close();
    */

    return 0;
}
