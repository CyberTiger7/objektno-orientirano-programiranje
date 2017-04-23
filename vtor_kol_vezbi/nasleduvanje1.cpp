//
// Created by krstevkoki on 4/23/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Nedviznost {
protected:
    char address[100];
    char city[30];
    float landSquareMeters;
public:
    Nedviznost(const char *address, const char *city, const float landSquareMeters) {
        strcpy(this->address, address);
        strcpy(this->city, city);
        this->landSquareMeters = landSquareMeters;
    }

    virtual const float estimatedPrice() const = 0;

    bool operator<(const Nedviznost &n) {
        return this->estimatedPrice() < n.estimatedPrice();
    }

    friend ostream &operator<<(ostream &out, const Nedviznost &n) {
        out << "Adresa: " << n.address << endl;
        out << "Grad: " << n.city << endl;
        out << n.landSquareMeters << " kvadrati" << endl;
        out << "Cena: " << n.estimatedPrice() << endl;
        return out;
    }

    virtual ~Nedviznost() {}
};

class Kukja : public Nedviznost {
private:
    int num_floors;
    float floorSquareMeters;
    bool haveAttic;
public:
    Kukja(const char *address, const char *city, const float landSquareMeters, const int num_floors,
          const float floorSquareMeters, const bool haveAttic)
            : Nedviznost(address, city, landSquareMeters) {
        this->num_floors = num_floors;
        this->floorSquareMeters = floorSquareMeters;
        this->haveAttic = haveAttic;
    }

    const float estimatedPrice() const {
        float price = (num_floors * floorSquareMeters) * 700 + (landSquareMeters - floorSquareMeters) * 200;
        if (haveAttic)
            return price + (floorSquareMeters * 450);
        return price;
    }
};

class Zgrada : public Nedviznost {
private:
    float flatSquareMeters;
    int num_flats;
public:
    Zgrada(const char *address, const char *city, const float landSquareMeters,
           const int num_flats, const float flatSquareMeters)
            : Nedviznost(address, city, landSquareMeters) {
        this->flatSquareMeters = flatSquareMeters;
        this->num_flats = num_flats;
    }

    const float estimatedPrice() const {
        return (flatSquareMeters * 800) * num_flats + (num_flats * 500);
    }
};

class Stovariste : public Nedviznost {
private:
    float yardSquareMeters;
    bool haveOffice;
public:
    Stovariste(const char *address, const char *city, const float landSquareMeters,
               const float yardSquareMeters, const bool haveOffice)
            : Nedviznost(address, city, landSquareMeters) {
        this->yardSquareMeters = yardSquareMeters;
        this->haveOffice = haveOffice;
    }

    const float estimatedPrice() const {
        float price = (yardSquareMeters * 250) + (landSquareMeters - yardSquareMeters) * 100;
        if (haveOffice) {
            return price + (10 / float(100)) * price;
        }
        return price;
    }
};

Nedviznost &najskap_imot(Nedviznost **ned, int n) {
    Nedviznost *max = ned[0];
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (*max < *ned[i]) {
            max = ned[i];
            maxIndex = i;
        }
    }
    return *ned[maxIndex];
}

int main() {
    int n; // Broj na nedviznosti

    int tip_nedviznost; // Tip na nedviznost (1-kukja, 2-zgrada, 3-stovariste)

    cin >> n;

    Nedviznost **ned = new Nedviznost *[n];
    char adresa[100];
    char grad[30];
    float kvadratura;
    for (int i = 0; i < n; ++i) {
        cin >> tip_nedviznost >> adresa >> grad >> kvadratura;
        if (tip_nedviznost == 1) {
            int br_kat;
            float kvadrat_kat;
            bool potkrovje;
            cin >> br_kat >> kvadrat_kat >> potkrovje;
            ned[i] = new Kukja(adresa, grad, kvadratura, br_kat, kvadrat_kat, potkrovje);
        } else if (tip_nedviznost == 2) {
            int br_stanovi;
            float kvadrat_na_stan;
            cin >> br_stanovi >> kvadrat_na_stan;

            ned[i] = new Zgrada(adresa, grad, kvadratura, br_stanovi, kvadrat_na_stan);
        } else if (tip_nedviznost == 3) {
            float kvadrati_pokrien_del;
            bool kancelarija;
            cin >> kvadrati_pokrien_del >> kancelarija;

            ned[i] = new Stovariste(adresa, grad, kvadratura, kvadrati_pokrien_del, kancelarija);
        }
    }

    cout << "== IMOTI ==" << endl;
    for (int i = 0; i < n; i++) {
        cout << *(ned[i]) << endl;
    }

    cout << "=== NAJSKAP IMOT ===" << endl;
    cout << najskap_imot(ned, n);

    return 0;
}
