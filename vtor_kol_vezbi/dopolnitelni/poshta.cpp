//
// Created by krstevkoki on 5/19/17.
//
#include <iostream>
#include <cstring>

using namespace std;

//mesto za vashiot kod
class Pratka {
private:
    int id;
    static int price;
public:
    Pratka() {
        id = 0;
    }

    Pratka(const int id) {
        this->id = id;
    }

    static const void setCenaProcesiranje(const int p) {
        price = p;
    }

    static const int getCenaProcesiranje() {
        return price;
    }

    const int getId() const {
        return id;
    }

    virtual ~Pratka() {}
};

int Pratka::price = 150;

class Pliko : public Pratka {
private:
    int width;
    int height;
    char name[50];
public:
    Pliko() : Pratka() {
        width = 0;
        height = 0;
        strcpy(name, "");
    }

    Pliko(const int id, const char *name, const int width, const int height)
            : Pratka(id) {
        this->width = width;
        this->height = height;
        strcpy(this->name, name);
    }

    const int cena() const {
        return Pratka::getCenaProcesiranje() + (width * height * 0.3);
    }

    const char *getPrimach() const {
        return name;
    }

    ~Pliko() {}
};

class Poshta {
private:
    Pliko plikoa[100];
    int num_plikoa;
public:
    Poshta() {
        num_plikoa = 0;
    }

    const int pratiPliko(const int id, const char *primach, const int d, const int w) {
        Pliko p(id, primach, d, w);
        plikoa[num_plikoa++] = p;
        return p.cena();
    }

    const void pecatiPlikoaDo(const char *primach) const {
        cout << "Za " << primach << " se plikoata so id-a: ";
        for (int i = 0; i < num_plikoa; ++i) {
            if (strcmp(plikoa[i].getPrimach(), primach) == 0) {
                cout << plikoa[i].getId() << " ";
            }
        }
        cout << endl;
    }
};

int main() {

    int tip, n, novaCena, id, visina, shirina;
    char primach[50];

    Poshta p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tip;
        if (tip == 1) {//pratiPliko
            cin >> id >> primach >> shirina >> visina;
            cout << "Cenata za prakjanje na pliko so id " << id << " e:"
                 << p.pratiPliko(id, primach, shirina, visina)
                 << endl;
        } else if (tip == 2) {//pecatiPlikoaDo
            cin >> primach;
            p.pecatiPlikoaDo(primach);
        } else if (tip == 3) {//setCenaProcesiranje
            cin >> novaCena;
            Pratka::setCenaProcesiranje(novaCena);
        } else if (tip == 4) {//Pratka
            cin >> id;
            Pratka p1(id);
            cout << "Kreirana e pratka so ID: " << p1.getId() << endl;
        } else {//Pliko
            cin >> id >> primach >> shirina >> visina;
            Pliko p2(id, primach, shirina, visina);
            cout << "Cena na pratka so ID: " << p2.getId() << " Do: "
                 << p2.getPrimach() << " e: " << p2.cena() << endl;
        }
    }
    return 0;
}