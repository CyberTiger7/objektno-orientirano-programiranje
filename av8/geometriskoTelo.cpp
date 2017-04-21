//
// Created by krstevkoki on 4/21/17.
//
#include <iostream>
#include <cmath>

using namespace std;

class GeomTelo {
protected:
    float visina;
public:
    GeomTelo(const float visina) {
        this->visina = visina;
    }

    virtual const void pecati() { // виртуелна функција
        cout << visina;
    }

    virtual const float getVolumen() = 0; // чисто виртуелна функција
    virtual const int nemaOsnovaRadius() = 0; // чисто виртуелна функција

    const float getVisina() const {
        return visina;
    }
};

class Cilinder : public GeomTelo {
private:
    float radius;
public:
    Cilinder(const float radius, const float visina)
            : GeomTelo(visina) {
        this->radius = radius;
    }

    // препокривање на функцијата getVolumen()
    const float getVolumen() {
        return float(M_PI * pow(radius, 2) * visina);
    }

    // препокривање на функцијата nemaOsnovaRadius()
    const int nemaOsnovaRadius() {
        return 0;
    }

    // препокривање на функцијата pecati()
    const void pecati() {
        cout << "Cilinder so visina ";
        GeomTelo::pecati();
        cout << " i so radius na osnovata " << radius << endl;
    }

    const float getRadius() {
        return radius;
    }
};

class Konus : public GeomTelo {
private:
    float radius;
public:
    Konus(const float radius, const float visina)
            : GeomTelo(visina) {
        this->radius = radius;
    }

    // препокривање на функциајта getVolumen()
    const float getVolumen() {
        return float(M_PI * pow(radius, 2) * visina) / 3;
    }

    // препокривање на функцијата nemaOsnovaRadius()
    const int nemaOsnovaRadius() {
        return 0;
    }

    // препокривање на функцијата pecati()
    const void pecati() {
        cout << "Konus so visina ";
        GeomTelo::pecati();
        cout << " i radius na osnovata " << radius << endl;
    }

    const float getRadius() {
        return radius;
    }
};

class Kvadar : public GeomTelo {
private:
    float a, b;
public:
    Kvadar(const float a, const float b, const float visina)
            : GeomTelo(visina) {
        this->a = a;
        this->b = b;
    }

    // препокривање на функцијата getVolumen()
    const float getVolumen() {
        return a * b * getVisina();
    }

    // препокривање на функцијата imaRadius()
    const int nemaOsnovaRadius() {
        return 1;
    }

    // препокривање на функцијата pecati()
    const void pecati() {
        cout << "Kvadar so visina ";
        GeomTelo::pecati();
        cout << " i so osnova " << a << " i " << b << endl;
    }
};

void teloSoNajgolemVolumen(GeomTelo **mnozestvoTela, const int n) {
    float max = mnozestvoTela[0]->getVolumen();
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (max < mnozestvoTela[i]->getVolumen()) {
            max = mnozestvoTela[i]->getVolumen();
            maxIndex = i;
        }
    }
    cout << "Teloto so najgolem Volumen e: " << endl;
    mnozestvoTela[maxIndex]->pecati();
}

int main() {
    GeomTelo **mnozestvoTela; // динамички алоцирано поле од покажувачи кон GeomTelo

    int n;
    cin >> n; // број на тела во множеството
    mnozestvoTela = new GeomTelo *[n]; // се алоцира меморија за полето од покажувачи

    for (int i = 0; i < n; ++i) {
        int r, a, b, h, type;

        cout << "Kakvo telo: 1-cilinder 2-konus 3-kvadar " << endl;
        cin >> type;

        if (type == 1) { // ако корисникот внесува цилиндер
            cin >> r >> h;
            mnozestvoTela[i] = new Cilinder(r, h);
        }

        if (type == 2) { // ако корисникот внесува конус
            cin >> r >> h;
            mnozestvoTela[i] = new Konus(r, h);
        }

        if (type == 3) { // ако корисникот внесува квадар
            cin >> a >> b >> h;
            mnozestvoTela[i] = new Kvadar(a, b, h);
        }
    }

    // барање 1
    teloSoNajgolemVolumen(mnozestvoTela, n);
    // барање 2
    int brojac = 0;
    for (int i = 0; i < n; i++)
        brojac += mnozestvoTela[i]->nemaOsnovaRadius();
    cout << "Brojot na tela koi nemaat osnova krug e: " << brojac;

    for (int i = 0; i < n; ++i) {
        delete mnozestvoTela[i];
    }

    delete[] mnozestvoTela;
    return 0;
}
