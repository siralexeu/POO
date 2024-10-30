#include<iostream>
using namespace std;

class Eveniment {
private:
    int nrPers = 0;
    string locatie = "Anonim";
public:
    Eveniment() {}
    Eveniment(int nrPers, string locatie) {
        this->nrPers = nrPers;
        this->locatie = locatie;
    }
    Eveniment(const Eveniment& e) {
        this->nrPers = e.nrPers;
        this->locatie = e.locatie;
    }
    Eveniment& operator=(const Eveniment& e) {
        this->nrPers = e.nrPers;
        this->locatie = e.locatie;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Eveniment& e) {
        out << "\nNr pers eveniment: " << e.nrPers;
        out << "\nLocatie eveniment: " << e.locatie;
        return out;
    }
};

template<class TIP>
class Colectie {
    TIP* elemente = nullptr;
    int nrElem = 0;
public:
    Colectie() {}
    Colectie(TIP* elemente, int nrElem) {
        if (elemente != nullptr && nrElem > 0)
            this->nrElem = nrElem;
        this->elemente = new TIP[this->nrElem];
        for (int i = 0; i < this->nrElem; i++)
            this->elemente[i] = elemente[i];
    }
    Colectie(const Colectie& c) {
        if (c.elemente != nullptr && c.nrElem > 0)
            this->nrElem = c.nrElem;
        this->elemente = new TIP[this->nrElem];
        for (int i = 0; i < this->nrElem; i++)
            this->elemente[i] = c.elemente[i];
    }
    Colectie& operator=(const Colectie& c) {
        if (this != &c) {
            delete[] this->elemente;
            this->elemente = nullptr;
            if (c.elemente != nullptr && c.nrElem > 0)
                this->nrElem = c.nrElem;
            this->elemente = new TIP[this->nrElem];
            for (int i = 0; i < this->nrElem; i++)
                this->elemente[i] = c.elemente[i];
        }
        else {
            this->elemente = nullptr;
            this->nrElem = 0;
        }
        return *this;
    }
    void sortare() {
        for (int i = 0; i < this->nrElem - 1; i++) {
            for (int j = i + 1; j < this->nrElem; j++) {
                if (this->elemente[i] < this->elemente[j]) {
                    swap(this->elemente[i], this->elemente[j]);
                }
            }
        }
    }
    
    friend ostream& operator<<(ostream& out, const Colectie& c) {
        out << "\nNr elem colectie: " << c.nrElem;
        out << "\nLista elem: ";
        for (int i = 0; i < c.nrElem; i++)
            out << c.elemente[i] << " ";
        return out;
    }
    ~Colectie() {
        delete[] this->elemente;
        this->elemente = nullptr;
    }
    //supraincarcare op functie care prim ca param un nr intreg(n) si returneaza un vector format din top n obiecte din vectorul de elem
    TIP* operator()(int n) {
        if (n > 0 && this->elemente != nullptr && n < this->nrElem) {
            TIP* topElem = new TIP[n];
            this->sortare();
            for (int i = 0;i < n;i++) {
                topElem[i] = this->elemente[i];
            }
            return topElem;
        }
        else
        {
            return nullptr;
        }
    }
};

int main()
{
    int vInt[] = { 10,5,8,9 };
    Colectie<int> cInt(vInt, 4);
    cout << cInt;

    Eveniment e1(2, "Pitesti");
    Eveniment e2(3, "Bucuresti");
    Eveniment vEven[] = { e1, e2 };
    Colectie<Eveniment> cEven(vEven, 2);
    cout << cEven;

    int* topInt = nullptr;
    //topInt = cInt.operator=()(2);
    topInt = cInt(2);
    cout << endl << "Top inturi: ";
    for (int i = 0;i < 2;i++) {
        cout << topInt[i] << ' ';
    }

    delete[] topInt;
    return 0;
}
