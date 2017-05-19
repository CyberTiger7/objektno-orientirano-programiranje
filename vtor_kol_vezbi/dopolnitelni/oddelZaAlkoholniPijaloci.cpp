//
// Created by krstevkoki on 5/19/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Pijalok {
private:
    char naziv[20];
    char sostojka[20];
    float kolicina;
    static int cenaDl;
public:
    Pijalok() {
        kolicina = 0;
        strcpy(naziv, "");
        strcpy(sostojka, "");
    }

    Pijalok(const char *naziv, const char *sostojka, const float kolicina) {
        this->kolicina = kolicina;
        strcpy(this->naziv, naziv);
        strcpy(this->sostojka, sostojka);
    }

    static const void setCenaDl(const int c) { cenaDl = c; }

    static const int getCenaDl() { return cenaDl; }

    const char *getNaziv() const { return naziv; }

    const char *getSostojka() const { return sostojka; }

    virtual const float cena() const {
        return cenaDl * kolicina;
    }

    virtual ~Pijalok() {}
};

int Pijalok::cenaDl = 3;

class AlkoholenPijalok : public Pijalok {
private:
    float stepenAlkohol;
    int godinaProizvodstvo;
public:
    AlkoholenPijalok() : Pijalok() {
        stepenAlkohol = 0;
        godinaProizvodstvo = 0;
    }

    AlkoholenPijalok(const char *naziv, const char *sostojka, const float kolicina,
                     const float stepenAlkohol, const int godinaProizvodstvo)
            : Pijalok(naziv, sostojka, kolicina) {
        this->stepenAlkohol = stepenAlkohol;
        this->godinaProizvodstvo = godinaProizvodstvo;
    }

    const float getStepen() const { return stepenAlkohol; }

    const float cena() const {
        float price = 100;
        if (strcmp(Pijalok::getNaziv(), "Vino") == 0) {
            if (godinaProizvodstvo > 2010)
                return Pijalok::cena() * 10;
            if (godinaProizvodstvo <= 2010)
                return Pijalok::cena() * 15;
        }
        if (strcmp(Pijalok::getSostojka(), "jacmen") == 0) {
            price = 70;
            return Pijalok::cena() + price;
        }
        if (strcmp(Pijalok::getSostojka(), "kompir") == 0) {
            price = 50;
            return Pijalok::cena() + price;
        }
        return Pijalok::cena() + price;
    }

    ~AlkoholenPijalok() {}
};

class AlkoholenOddel {
private:
    AlkoholenPijalok pijaloci[50];
    int broj_pijaloci;
public:
    AlkoholenOddel() {
        broj_pijaloci = 0;
    }

    const int primiAPijalok(const char *naziv, const char *osnovnaSostojka,
                            const float kolicina, const float alkohol, int godina) {
        AlkoholenPijalok a(naziv, osnovnaSostojka, kolicina, alkohol, godina);
        pijaloci[broj_pijaloci++] = a;
        return broj_pijaloci;
    }

    const void pecati(const float alkohol) const {
        cout << "Povisok stepen na alkohol od " << alkohol << " imaat:" << endl;
        for (int i = 0; i < broj_pijaloci; ++i) {
            if (pijaloci[i].getStepen() > alkohol) {
                cout << pijaloci[i].getNaziv() << " " << pijaloci[i].cena() << endl;
            }
        }
    }

    ~AlkoholenOddel() {}
};

int main() {

    int tip, n, novaCena;
    char naziv[20], osnovnaSostojka[20];
    int godina;
    float kolicina, alkohol;
    AlkoholenOddel ao;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tip;
        if (tip == 1) {//Pijalok
            cin >> naziv >> osnovnaSostojka >> kolicina;
            Pijalok p1(naziv, osnovnaSostojka, kolicina);
            cout << "Kreiran e pijalok so naziv: " << p1.getNaziv() << endl;
        } else if (tip == 2) {//cena - Pijalok
            cin >> naziv >> osnovnaSostojka >> kolicina;
            Pijalok p1(naziv, osnovnaSostojka, kolicina);
            cout << "Osnovna cena na pijalokot so naziv " << p1.getNaziv()
                 << " e: " << p1.cena() << endl;
        } else if (tip == 3) {//AlkoholenPijalok
            cin >> naziv >> osnovnaSostojka >> kolicina >> alkohol >> godina;
            AlkoholenPijalok p2(naziv, osnovnaSostojka, kolicina, alkohol, godina);
            cout << "Kreiran e alkoholen pijalog so naziv " << p2.getNaziv()
                 << " i stepen " << p2.getStepen() << endl;
        } else if (tip == 4) {//cena - AlkoholenPijalok
            cin >> naziv >> osnovnaSostojka >> kolicina >> alkohol >> godina;
            AlkoholenPijalok p2(naziv, osnovnaSostojka, kolicina, alkohol, godina);
            cout << "Cenata na alkoholniot pijalog so naziv " << p2.getNaziv()
                 << " e: " << p2.cena() << endl;
        } else if (tip == 5) {//dodadi
            cin >> naziv >> osnovnaSostojka >> kolicina >> alkohol >> godina;
            cout << ao.primiAPijalok(naziv, osnovnaSostojka,
                                     kolicina, alkohol, godina)
                 << endl;
        } else if (tip == 6) {//pecati
            cin >> alkohol;
            ao.pecati(alkohol);
        } else if (tip == 7) {//smeni cena
            cin >> novaCena;
            Pijalok::setCenaDl(novaCena);
            cout << "Nova cena: " << Pijalok::getCenaDl() << endl;

            cin >> naziv >> osnovnaSostojka >> kolicina >> alkohol >> godina;
            AlkoholenPijalok p2(naziv, osnovnaSostojka, kolicina, alkohol, godina);
            cout << "Cenata na alkoholniot pijalog so naziv " << p2.getNaziv()
                 << " e: " << p2.cena() << endl;
        }
    }
    return 0;
}