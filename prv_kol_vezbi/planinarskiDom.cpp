//
// Created by krstevkoki on 3/29/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Zichara {
private:
    char *place;
    int price;
public:
    Zichara() {
        this->place = NULL;
        this->price = 0;
    }

    Zichara(char *place, int price) {
        this->price = price;
        this->place = new char[strlen(place) + 1];
        strcpy(this->place, place);
    }

    Zichara(const Zichara &z) {
        this->price = z.price;
        this->place = new char[strlen(z.place) + 1];
        strcpy(this->place, z.place);
    }

    Zichara &operator=(const Zichara &z) {
        if (this != &z) {
            this->price = z.price;
            delete[] this->place;
            this->place = new char[strlen(z.place) + 1];
            strcpy(this->place, z.place);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Zichara &z) {
        out << z.place << endl;
        out << z.price << endl;
        return out;
    }

    ~Zichara() { delete[] place; }

    char *getPlace() {
        return place;
    }

    int getPrice() {
        return price;
    }
};

class PlaninarskiDom {
private:
    char name[15];
    int price_per_season[2];
    char Class;
    bool ima_zicara;
    Zichara *zichara;
public:
    PlaninarskiDom() {
        strcpy(this->name, "");
        for (int i = 0; i < 2; ++i) {
            this->price_per_season[i] = 0;
        }
        this->Class = 'F';
        this->ima_zicara = 1;
        this->zichara = NULL;
    }

    PlaninarskiDom(char *name, int *price_per_season, char Class) {
        strcpy(this->name, name);
        for (int i = 0; i < 2; ++i) {
            this->price_per_season[i] = price_per_season[i];
        }
        this->Class = Class;
        this->ima_zicara = 0;
        this->zichara = NULL;
    }

    PlaninarskiDom(const PlaninarskiDom &pd) {
        strcpy(this->name, pd.name);
        this->Class = pd.Class;
        for (int i = 0; i < 2; ++i) {
            this->price_per_season[i] = pd.price_per_season[i];
        }
        if (pd.zichara == NULL) {
            this->zichara = NULL;
            this->ima_zicara = 0;
        } else {
            this->ima_zicara = 1;
            this->zichara = new Zichara(pd.zichara->getPlace(), pd.zichara->getPrice());
        }
    }

    PlaninarskiDom &operator=(const PlaninarskiDom &pd) {
        if (this != &pd) {
            strcpy(this->name, pd.name);
            this->Class = pd.Class;
            for (int i = 0; i < 2; ++i) {
                this->price_per_season[i] = pd.price_per_season[i];
            }
            delete this->zichara;
            if (pd.zichara == NULL) {
                this->ima_zicara = 0;
                this->zichara = NULL;
            } else {
                this->ima_zicara = 1;
                this->zichara = new Zichara(pd.zichara->getPlace(), pd.zichara->getPrice());
            }
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const PlaninarskiDom &pd) {
        if (pd.ima_zicara) {
            out << pd.name << " klasa:" << pd.Class << " so Zichara" << endl;
        } else
            out << pd.name << " klasa:" << pd.Class << endl;
        return out;
    }

    bool operator<=(const char &character) {
        return Class >= character;
    }

    PlaninarskiDom &operator--() {
        if (this->Class != 'F')
            this->Class++;
        return *this;
    }

    ~PlaninarskiDom() { delete zichara; }


    void setZichara(Zichara &r) {
        this->zichara = new Zichara(r.getPlace(), r.getPrice());
    }

    void presmetajDnevenPrestoj(int &den, int &mesec, int &cena) {
        if ((mesec < 1 || mesec > 12) || (den < 1 || den > 31))
            throw 10;
        else {
            if (mesec < 4 || mesec > 10)
                cena = price_per_season[1] + 20;
            else
                cena = price_per_season[0];
        }
    }
};

int main() {

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++)
        cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    } else {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
    }
    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;
    int cena;
    int den, mesec;
    cin >> den >> mesec;
    try {
        p.presmetajDnevenPrestoj(den, mesec, cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";
        cout << "Cenata za " << den << "." << mesec << " e " << cena; //се печати цената за дадениот ден и месец
    }
    catch (int) {
        cout << "Mesecot ili denot e greshno vnesen!";
    }
    return 0;
}