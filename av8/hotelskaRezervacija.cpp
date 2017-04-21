//
// Created by krstevkoki on 4/21/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class HotelskaRezervacija {
protected:
    char name[50];
    char surname[50];
    int num_days;
    int num_people;
public:
    HotelskaRezervacija(const char *name, const char *surname, const int num_days, const int num_people) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->num_days = num_days;
        this->num_people = num_people;
    }

    virtual const int vratiCena() {
        return num_days * num_people * 25;
    }

    virtual const int vratiCena(const int uplata) {
        int cena = vratiCena();
        if (uplata >= cena) {
            cout << "REZERVACIJA: " << endl;
            cout << name << " " << surname << endl;
            cout << "Denovi: " << num_days << endl;
            cout << "Lugje: " << num_people << endl;
            return uplata - cena;
        } else {
            cout << "Vi nedostasuvaat " << cena - uplata << " pari za uspesna naplata !" << endl << endl;
            return -1;
        }
    }
};

class PolupansionskaHotelskaRezervacija : public HotelskaRezervacija {
public:
    PolupansionskaHotelskaRezervacija(const char *name, const char *surname, const int num_days,
                                      const int num_people)
            : HotelskaRezervacija(name, surname, num_days, num_people) {}

    const int vratiCena(const int uplata) { // препокривање на vratiCena(int uplata)
        int cena = HotelskaRezervacija::vratiCena() + num_people * 5; // пристап до protected податокот broj_lica
        if (uplata >= cena) {
            cout << "REZERVACIJA: " << endl;
            cout << name << " " << surname << endl;
            cout << "Denovi: " << num_days << endl;
            cout << "Lugje: " << num_people << endl;
            return uplata - cena;
        } else {
            cout << name << " " << surname << ", Vi nedostasuvaat " << cena - uplata
                 << " denari za uspeshna naplata !" << endl << endl;
            return -1;
        }
    }
};

class Hotel {
private:
    char name[50];
    int saldo;
public:
    Hotel(const char *name) {
        strcpy(this->name, name);
        this->saldo = 0;
    }

    // референца кон основната класа може да референцира објекти и кон изведените класи
    const int uplatiZaRezervacija(HotelskaRezervacija &hr, const int uplata) {
        int kusur = hr.vratiCena(uplata); /*полиморфизам
         која дефиниција на vratiCena ќе се повика?
         важно: vratiCena е виртуелна функција*/
        if (kusur != -1)
            saldo += kusur;
        return kusur;
    }
};

int main() {
    Hotel h("Bristol");

    HotelskaRezervacija *hr1 = new HotelskaRezervacija("Petko", "Petkovski", 5, 5);

    int cena = h.uplatiZaRezervacija(*hr1, 1000);
    if (cena != -1) {
        if (cena != 0)
            cout << "Kusur: " << cena << endl;
        cout << "USPESHNO" << endl << endl;
    }

    PolupansionskaHotelskaRezervacija *hr2 = new PolupansionskaHotelskaRezervacija("Risto", "Ristovski", 5, 5);
    cena = h.uplatiZaRezervacija(*hr2, 1000);
    if (cena != -1) {
        if (cena != 0)
            cout << "Kusur: " << cena << endl;
        cout << "USPESHNO" << endl << endl;
    }

    //покажувач кон основна класа покажува кон објект од изведена
    HotelskaRezervacija *hr3 = new PolupansionskaHotelskaRezervacija("Ana", "Anovska", 4, 2);
    cena = h.uplatiZaRezervacija(*hr3, 100);
    if (cena != -1) {
        if (cena != 0)
            cout << "Kusur: " << cena << endl;
        cout << "USPESHNO" << endl << endl;
    }

    PolupansionskaHotelskaRezervacija hr4("Tome", "Tomovski", 5, 3);
    cena = h.uplatiZaRezervacija(hr4, 1000);
    if (cena != -1) {
        if (cena != 0)
            cout << "Kusur: " << cena << endl;
        cout << "USPESHNO" << endl << endl;
    }

    delete hr1, hr2, hr3;

    return 0;
}
