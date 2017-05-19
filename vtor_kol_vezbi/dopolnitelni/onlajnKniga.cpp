//
// Created by krstevkoki on 5/19/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class NoGradeException {
private:
    char *errorMsg;
public:
    NoGradeException(const char *errorMsg) {
        this->errorMsg = new char[strlen(errorMsg) + 1];
        strcpy(this->errorMsg, errorMsg);
    }

    NoGradeException(const NoGradeException &e) {
        this->errorMsg = new char[strlen(e.errorMsg) + 1];
        strcpy(this->errorMsg, e.errorMsg);
    }

    NoGradeException &operator=(const NoGradeException &e) {
        if (this != &e) {
            this->errorMsg = new char[strlen(e.errorMsg) + 1];
            strcpy(this->errorMsg, e.errorMsg);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const NoGradeException &e) {
        return out << e.errorMsg;
    }

    ~NoGradeException() { delete[] errorMsg; }
};

class Lice {
private:
    char ime[20];
    char drzava[20];
public:
    Lice() {
        strcpy(this->ime, "");
        strcpy(this->drzava, "");
    }

    Lice(const char *ime, const char *drzava) {
        strcpy(this->ime, ime);
        strcpy(this->drzava, drzava);
    }

    bool operator==(char *ime) { return strcmp(this->ime, ime) == 0; }

    char const *getIme() const { return ime; }

    void pecati() const { cout << ime << " (" << drzava << ")" << endl; }
};

class Kniga {
private:
    Lice avtori[10];
    int brojAvtori;
    int *ocenki;
    int brojOcenki;
protected:
    char naziv[30];
public:
    Kniga(const char *naziv, Lice *avtori, const int brojAvtori,
          const int *ocenki, const int brojOcenki) {
        this->brojAvtori = brojAvtori;
        this->brojOcenki = brojOcenki;
        strcpy(this->naziv, naziv);
        for (int i = 0; i < brojAvtori; i++)
            this->avtori[i] = avtori[i];
        this->ocenki = new int[brojOcenki];
        for (int i = 0; i < brojOcenki; i++)
            this->ocenki[i] = ocenki[i];
    }

    Kniga(const Kniga &k) {
        this->brojAvtori = k.brojAvtori;
        this->brojOcenki = k.brojOcenki;
        strcpy(this->naziv, k.naziv);
        for (int i = 0; i < k.brojAvtori; i++)
            this->avtori[i] = k.avtori[i];
        for (int i = 0; i < k.brojOcenki; i++)
            this->ocenki[i] = k.ocenki[i];
        this->ocenki = new int[k.brojOcenki];
    }

    Kniga &operator=(const Kniga &k) {
        if (this != &k) {
            this->brojAvtori = k.brojAvtori;
            this->brojOcenki = k.brojOcenki;
            strcpy(this->naziv, k.naziv);
            for (int i = 0; i < k.brojAvtori; i++)
                this->avtori[i] = k.avtori[i];
            delete[] this->ocenki;
            this->ocenki = new int[k.brojOcenki];
            for (int i = 0; i < k.brojOcenki; i++)
                this->ocenki[i] = k.ocenki[i];
        }
        return *this;
    }

    Lice operator[](int i) const {
        if (i < brojAvtori && i >= 0)
            return avtori[i];
        else
            return Lice();
    }

    const Lice getAvtori(int i) const {
        return avtori[i];
    }

    const int getBrojAvtori() const { return brojAvtori; }

    const char *getNaziv() const { return naziv; }

    //dopolni ja klasata
    virtual const double getVkupnaOcenka() const {
        if (brojOcenki == 0)
            throw NoGradeException(" nema ocenki od chitatelite\n");
        double average = 0;
        for (int i = 0; i < brojOcenki; ++i) {
            average += ocenki[i];
        }
        return average / double(brojOcenki);
    }

    virtual const void pecati() const {
        cout << naziv << endl;
        cout << "Avtori:" << endl;
        for (int i = 0; i < brojAvtori; ++i) {
            avtori[i].pecati();
        }
    }

    virtual const int getBookType() const { return 1; }

    virtual ~Kniga() { delete[] ocenki; }
};

class VebStranica {
private:
    char *url;
protected:
    int brojPristapuvanja;
public:
    VebStranica(const char *url, const int brojPristapuvanja) {
        this->brojPristapuvanja = brojPristapuvanja;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    VebStranica(const VebStranica &v) {
        this->brojPristapuvanja = v.brojPristapuvanja;
        this->url = new char[strlen(v.url) + 1];
        strcpy(this->url, v.url);
    }

    VebStranica &operator=(const VebStranica &v) {
        if (this != &v) {
            this->brojPristapuvanja = v.brojPristapuvanja;
            delete[] this->url;
            this->url = new char[strlen(v.url) + 1];
            strcpy(this->url, v.url);
        }
        return *this;
    }

    const void pecati() const { cout << "url: " << url << endl; }

    virtual ~VebStranica() { delete[] url; }
};

//vashiot kod
class OnlajnKniga : public Kniga, public VebStranica {
private:
    int brojSimnuvanja;
public:
    OnlajnKniga(const char *naziv, Lice *avtori, const int brojAvtori,
                const int *ocenki, const int brojOcenki, const char *url,
                const int brojPristapuvanja, const int brojSimnuvanja)
            : Kniga(naziv, avtori, brojAvtori, ocenki, brojOcenki),
              VebStranica(url, brojPristapuvanja) {
        this->brojSimnuvanja = brojSimnuvanja;
    }

    const void pecati() const {
        Kniga::pecati();
        VebStranica::pecati();
    }

    const double getVkupnaOcenka() const {
        return Kniga::getVkupnaOcenka() * (brojSimnuvanja / double(brojPristapuvanja));
    }

    const int getBookType() const { return 2; }

    ~OnlajnKniga() {}
};

const void pecatiOnlajnKnigi(Kniga **knigi, const int n) {
    for (int i = 0; i < n; ++i) {
        if (knigi[i]->getBookType() == 2)
            knigi[i]->pecati();
    }
}

const double prosechnaOcenka(const char *avtor, Kniga **knigi, const int n) {
    float average = 0;
    int knigiNaAvtorot = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < knigi[i]->getBrojAvtori(); ++j) {
            if (strcmp((*knigi[i])[j].getIme(), avtor) == 0) {
                ++knigiNaAvtorot;
                try {
                    average += knigi[i]->getVkupnaOcenka();
                }
                catch (NoGradeException &e) {
                    cout << "Knigata " << knigi[i]->getNaziv() << e;
                }
            }
        }
    }
    return average / double(knigiNaAvtorot);
}

int main() {
    Lice avtori[10];
    int brojAvtori, ocenki[20], ocenka, brojOcenki, tip, brojPristapi, brojSimnuvanja;
    char naslov[20], ime[40], drzava[20], url[50];
    cin >> tip;
    if (tip == 1) { //test class OnlajnKniga
        cout << "-----TEST OnlajnKniga-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i < brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> url >> brojPristapi >> brojSimnuvanja;
        OnlajnKniga ok(naslov, avtori, brojAvtori, ocenki, brojOcenki, url,
                       brojPristapi, brojSimnuvanja);
        cout << "Objekt od klasata OnlajnKniga e kreiran";
    } else if (tip == 2) { //funkcija pecati vo kniga
        cout << "-----TEST pecati-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i < brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        Kniga k(naslov, avtori, brojAvtori, ocenki, brojOcenki);
        k.pecati();
    } else if (tip == 3) { //funkcija getVkupnaOcenka vo kniga
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i < brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        Kniga k(naslov, avtori, brojAvtori, ocenki, brojOcenki);
        try {
            cout << "Vkupna ocenka: " << k.getVkupnaOcenka() << endl;
        } catch (NoGradeException &e) {
            cout << "Knigata " << k.getNaziv() << e;
        }
    } else if (tip == 4) { //funkcija getVkupnaOcenka vo OnlajnKniga
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i < brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> url >> brojPristapi >> brojSimnuvanja;

        OnlajnKniga ok(naslov, avtori, brojAvtori, ocenki, brojOcenki, url,
                       brojPristapi, brojSimnuvanja);
        try {
            cout << "Vkupna ocenka: " << ok.getVkupnaOcenka() << endl;
        } catch (NoGradeException &e) {
            cout << "Knigata " << ok.getNaziv() << e;
        }
    } else if (tip == 5) { //funkcija pecati vo OnlajnKniga
        cout << "-----TEST pecati -----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i < brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> url >> brojPristapi >> brojSimnuvanja;

        OnlajnKniga ok(naslov, avtori, brojAvtori, ocenki, brojOcenki, url,
                       brojPristapi, brojSimnuvanja);
        ok.pecati();
    } else if (tip == 6) { //site klasi
        cout << "-----TEST Kniga i OnlajnKniga-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i < brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> url >> brojPristapi >> brojSimnuvanja;
        Kniga *k = new OnlajnKniga(naslov, avtori, brojAvtori,
                                   ocenki, brojOcenki, url,
                                   brojPristapi, brojSimnuvanja);
        k->pecati();
        try {
            cout << "Vkupna ocenka: " << k->getVkupnaOcenka() << endl;
        } catch (NoGradeException &e) {
            cout << "Knigata " << k->getNaziv() << e;
        }
        delete k;
    } else if (tip == 7) { //funkcija prosechnaOcenka
        cout << "-----TEST prosechnaOcenka-----" << endl;
        int k, opt;
        cin >> k;
        Kniga **knigi = new Kniga *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 kniga 2 onlajnkniga
            cin >> naslov >> brojAvtori;
            for (int i = 0; i < brojAvtori; i++) {
                cin >> ime >> drzava;
                avtori[i] = Lice(ime, drzava);
            }
            cin >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                knigi[j] = new Kniga(naslov, avtori, brojAvtori, ocenki, brojOcenki);
            } else {
                cin >> url >> brojPristapi >> brojSimnuvanja;
                knigi[j] = new OnlajnKniga(naslov, avtori, brojAvtori,
                                           ocenki, brojOcenki, url, brojPristapi,
                                           brojSimnuvanja);
            }
        }
        cin >> ime;
        double prosecna = prosechnaOcenka(ime, knigi, k);
        cout << "Prosecna ocenka e za knigite na " << ime << " e " << prosecna;
        for (int j = 0; j < k; j++) delete knigi[j];
        delete[] knigi;
    } else if (tip == 8) { //funkcija pecatiOnlajnKnigi
        cout << "-----TEST pecatiOnlajnKnigi-----" << endl;
        int k, opt;
        cin >> k;
        Kniga **knigi = new Kniga *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 kniga 2 onlajnkniga
            cin >> naslov >> brojAvtori;
            for (int i = 0; i < brojAvtori; i++) {
                cin >> ime >> drzava;
                avtori[i] = Lice(ime, drzava);
            }
            cin >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                knigi[j] = new Kniga(naslov, avtori, brojAvtori, ocenki, brojOcenki);
            } else {
                cin >> url >> brojPristapi >> brojSimnuvanja;
                knigi[j] = new OnlajnKniga(naslov, avtori, brojAvtori,
                                           ocenki, brojOcenki, url, brojPristapi,
                                           brojSimnuvanja);
            }
        }
        pecatiOnlajnKnigi(knigi, k);
        for (int j = 0; j < k; j++) delete knigi[j];
        delete[] knigi;

    }
    return 0;
}