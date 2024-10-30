#include<iostream>
using namespace std;

class Cadou {
private:
    string denumire = "Anonim";
    float pret = 0;
    static int nrCadouri; // Ne numara cate obiecte se vor construi de-a lungul constructorilor
    const int cod;

public:
    Cadou() : cod(Cadou::nrCadouri++)
    {
    }

    Cadou(string denumire, float pret) : cod(Cadou::nrCadouri++)
    {
        this->denumire = denumire;
        this->pret = pret;
    }

    Cadou(const Cadou& c) : cod(Cadou::nrCadouri++)
    {
        this->denumire = c.denumire;
        this->pret = c.pret;
    }

    Cadou& operator=(const Cadou& c)
    {
        this->denumire = c.denumire;
        this->pret = c.pret;
        return *this;
    }

    ~Cadou() {
        //Cadou::nrCadouri--; (optional daca nu vrem atunci cand copiem sa se incrementeze)
    }

    friend ostream& operator<<(ostream& out, const Cadou& c)
    {
        out << "\nCod: " << c.cod << "\nDenumire: " << c.denumire << ", pret: " << c.pret;
        return out;
    }
    friend istream& operator>>(istream& in, Cadou& c) // CUM PUTEM OFERI MECANISM DE GENERARE NOU COD UNIC IN ISTREAM DE DOCUMENTAT
    {
        cout << "Introduceti denumire: ";
        in >> c.denumire;
        cout << "Introduceti pret: ";
        in >> c.pret;
        return in;
    }
};

class WishList {

    string posesorLista;
    int nrCadouri;
    Cadou listaCadouri[100];

};
class WishList2 {

    string posesorLista;
    int nrCadouri;
    Cadou* listaCadouri; // Vector alocat dinamic daca vrem cu obiecte ce stocheaza de tip cadou

};
class WishList3 {

    string posesorLista;
    int nrCadouri;
    Cadou* listaCadouri[100]; // Vector alocat static de pointeri la obiect de tip cadou ( e mai light partea de transfer )
};
class WishList4 {

    string posesorLista;
    int nrCadouri;
    Cadou** listaCadouri; // vector dinamic de pointeri

public:
    WishList4() {}

    WishList4(string posesorLista, int nrCadouri, Cadou** listaCadouri) {
        this->posesorLista = posesorLista;
        if (nrCadouri > 0 && listaCadouri != nullptr) {
            this->nrCadouri = nrCadouri;
            // this->listaCadouri = listaCadouri NU E BINE ERA TOTAL SHALLOW COPY SUPERFICIAL
            this->listaCadouri = new Cadou * [this->nrCadouri]; // stocheaza pointeri la cadouri acest vector alocat dinamic
            //lucrand cu un pointer la obiect cadou nu avem nevoie de constructor fara parametrii
            for (int i = 0; i < this->nrCadouri; i++)
                this->listaCadouri[i] = new Cadou(*listaCadouri[i]); // Apeleaza constructor de copiere , dereferentiem adresa cu *
        }

    }

    WishList4(const WishList4& w) {
        this->posesorLista = w.posesorLista;
        if (nrCadouri > 0 && w.listaCadouri != nullptr) {
            this->nrCadouri = w.nrCadouri;
            this->listaCadouri = new Cadou * [this->nrCadouri];

            for (int i = 0; i < this->nrCadouri; i++)
                this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
        }
    }


    ~WishList4() {
        for (int i = 0; i < this->nrCadouri; i++)
        {
            delete this->listaCadouri[i];
            this->listaCadouri[i] = nullptr;
        }
        delete[] this->listaCadouri;
        this->listaCadouri = nullptr;
    }

    WishList4& operator=(const WishList4& w)
    {
        if (this != &w)
        {
            for (int i = 0; i < this->nrCadouri; i++)
            {
                delete this->listaCadouri[i];
                this->listaCadouri[i] = nullptr;
            }
            delete[] this->listaCadouri;
            this->listaCadouri = nullptr;
            this->posesorLista = w.posesorLista;
            if (nrCadouri > 0 && w.listaCadouri != nullptr) {
                this->nrCadouri = w.nrCadouri;
                this->listaCadouri = new Cadou * [this->nrCadouri];

                for (int i = 0; i < this->nrCadouri; i++)
                    this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
            }
            return *this;
        }
    }

    friend ostream& operator<<(ostream& out, const WishList4& w)
    {
        out << "\nPosesorLista: " << w.posesorLista;
        out << "\nNr cadouri: " << w.nrCadouri;
        out << " \nLista cadouri: ";
        for (int i = 0; i < w.nrCadouri; i++)
            out << *w.listaCadouri[i];
        return out;
    }
};
// relatie 1 la multi de la 1 - 4 wishlists



class WishList5 {

    string posesorLista;
    Cadou* cadou; // pointer la un obiect de tip cadou nu mai este vector deoarece nu am dimensiunea
    // este relatie 1 la 1
};

class WishList6 {   //TEMA PENTRU ACASA

    string posesorLista;
    int nrPrieteni;
    int* nrCadouriPrieteni;
    Cadou** listaCadouri;
};

int Cadou::nrCadouri = 0;

int main()
{
    Cadou c1;
    Cadou c2("Stilou", 1000);
    cout << c1 << c2;

    Cadou c3 = c2;
    cout << c3;

    WishList4 w1;


    return 0;
}
