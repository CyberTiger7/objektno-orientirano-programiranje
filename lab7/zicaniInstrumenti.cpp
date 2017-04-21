//
// Created by krstevkoki on 4/21/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class ZicanInstrument {
protected:
    char name[20];
    int num_wires;
    float price;
public:
    ZicanInstrument(const char *name, const int num_wires, const float price) {
        strcpy(this->name, name);
        this->num_wires = num_wires;
        this->price = price;
    }

    bool operator==(const ZicanInstrument &zi) {
        return this->num_wires == zi.num_wires;
    }

    virtual const float cena() = 0;
};

class Mandolina : public ZicanInstrument {
private:
    char form[20];
public:
    Mandolina(const char *name, const int num_wires, const float price, const char *form)
            : ZicanInstrument(name, num_wires, price) {
        strcpy(this->form, form);
    }

    friend ostream &operator<<(ostream &out, const Mandolina &m) {
        return out << m.name << " " << m.num_wires << " " << m.price << " " << m.form << endl;
    }

    const float cena() {
        if (strcmp(this->form, "Neapolitan") == 0)
            return price + (float(15) / 100) * price;
        return price;
    }
};

class Violina : public ZicanInstrument {
private:
    float dimension;
public:
    Violina(const char *name, const int num_wires, const float price, const float dimension)
            : ZicanInstrument(name, num_wires, price) {
        this->dimension = dimension;
    }

    friend ostream &operator<<(ostream &out, const Violina &v) {
        return out << v.name << " " << v.num_wires << " " << v.price << v.dimension << endl;
    }

    const float cena() {
        if (this->dimension == 0.25)
            return price + (float(10) / 100) * price;
        else if (this->dimension == 1.00)
            return price + (float(20) / 100) * price;
        return price;
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, const int n) {
    for (int j = 0; j < n; ++j) {
        if (zi == *i[j]) {
            cout << i[j]->cena() << endl;
        }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];

    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);

    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument *[2 * n];

    for (int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }

    for (int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }

    pecatiInstrumenti(m, zi, 2 * n);

    for (int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete[] zi;

    return 0;
}
