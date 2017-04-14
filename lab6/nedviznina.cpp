//
// Created by krstevkoki on 4/14/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Nedviznina {
protected:
    char *address;
    int squareSurface;
    int price;
public:
    Nedviznina(const char *address = "", int squareSurface = 0, int price = 0) {
        this->squareSurface = squareSurface;
        this->price = price;
        this->address = new char[strlen(address) + 1];
        strcpy(this->address, address);
    }

    Nedviznina(const Nedviznina &n) {
        this->squareSurface = n.squareSurface;
        this->price = n.price;
        this->address = new char[strlen(n.address) + 1];
        strcpy(this->address, n.address);
    }

    Nedviznina &operator=(const Nedviznina &n) {
        if (this != &n) {
            this->squareSurface = n.squareSurface;
            this->price = n.price;
            delete[] this->address;
            this->address = new char[strlen(n.address) + 1];
            strcpy(this->address, n.address);
        }
        return *this;
    }

    friend istream &operator>>(istream &in, Nedviznina &n) {
        in >> n.address;
        in >> n.squareSurface;
        in >> n.price;
        return in;
    }

    void pecati() {
        cout << address << ", Kvadratura: " << squareSurface << ", Cena po Kvadrat: " << price << endl;
    }

    int cena() {
        return squareSurface * price;
    }

    float danokNaImot() {
        return (5 / float(100)) * cena();
    }

    const char *getAdresa() {
        return address;
    }

    ~Nedviznina() { delete[] address; }

};

class Vila : public Nedviznina {
private:
    int luxuryCustom;
public:
    Vila(const char *address = "", int squareSurface = 0, int price = 0, int luxuryCustom = 0)
            : Nedviznina(address, squareSurface, price) {
        this->luxuryCustom = luxuryCustom;
    }

    friend istream &operator>>(istream &in, Vila &v) {
        in >> v.address;
        in >> v.squareSurface;
        in >> v.price;
        in >> v.luxuryCustom;
        return in;
    }

    void pecati() {
        cout << address << ", Kvadratura: " << squareSurface << ", Cena po Kvadrat: "
             << price << ", Danok na luksuz: " << luxuryCustom << endl;
    }

    float danokNaImot() {
        return (luxuryCustom / float(100)) * cena() + Nedviznina::danokNaImot();
    }
};

int main() {
    Nedviznina n;
    Vila v;
    cin >> n;
    cin >> v;
    n.pecati();
    cout << "Danok za: " << n.getAdresa() << ", e: " << n.danokNaImot() << endl;
    v.pecati();
    cout << "Danok za: " << v.getAdresa() << ", e: " << v.danokNaImot() << endl;
    return 0;
}
