//
// Created by krstevkoki on 5/19/17.
//
#include<iostream>
#include<string.h>

using namespace std;

class NoCourseException {
private:
    char *errorMsg;
public:
    NoCourseException(const char *errorMsg) {
        this->errorMsg = new char[strlen(errorMsg) + 1];
        strcpy(this->errorMsg, errorMsg);
    }

    NoCourseException(const NoCourseException &e) {
        this->errorMsg = new char[strlen(e.errorMsg) + 1];
        strcpy(this->errorMsg, e.errorMsg);
    }

    NoCourseException &operator=(const NoCourseException &e) {
        if (this != &e) {
            this->errorMsg = new char[strlen(e.errorMsg) + 1];
            strcpy(this->errorMsg, e.errorMsg);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const NoCourseException &e) {
        return out << e.errorMsg;
    }

    ~NoCourseException() { delete[] errorMsg; }
};

class Kurs {
private:
    char ime[20];
    int krediti;
public:
    Kurs() {
        strcpy(this->ime, "");
        krediti = 0;
    }

    Kurs(const char *ime, const int krediti) {
        this->krediti = krediti;
        strcpy(this->ime, ime);
    }

    bool operator==(const char *ime) const {
        return strcmp(this->ime, ime) == 0;
    }

    char const *getIme() const { return ime; }

    const void pecati() const { cout << ime << " " << krediti << "ECTS"; }

    ~Kurs() {}
};

class Student {
private:
    int *ocenki;
    int brojOcenki;
protected:
    int indeks;
public:
    Student(const int indeks, const int *ocenki, const int brojOcenki) {
        this->indeks = indeks;
        this->brojOcenki = brojOcenki;
        this->ocenki = new int[brojOcenki];
        for (int i = 0; i < brojOcenki; i++)
            this->ocenki[i] = ocenki[i];
    }

    Student(const Student &k) {
        this->indeks = k.indeks;
        this->brojOcenki = k.brojOcenki;
        this->ocenki = new int[k.brojOcenki];
        for (int i = 0; i < k.brojOcenki; i++)
            this->ocenki[i] = k.ocenki[i];
    }

    Student operator=(const Student &k) {
        if (this != &k) {
            this->indeks = k.indeks;
            this->brojOcenki = k.brojOcenki;
            delete[] ocenki;
            this->ocenki = new int[k.brojOcenki];
            for (int i = 0; i < k.brojOcenki; i++)
                this->ocenki[i] = k.ocenki[i];
        }
        return *this;
    }

    //dopolni ja klasata
    virtual const int getBodovi() const {
        int brojacProlazni = 0;
        for (int i = 0; i < brojOcenki; ++i) {
            if (ocenki[i] > 5)
                ++brojacProlazni;
        }
        return (brojacProlazni / float(brojOcenki)) * 100;
    }

    virtual const void pecati() const { cout << indeks; }

    virtual const bool daliDemonstrator() const { return false; }

    const int getIndeks() const {
        return indeks;
    }

    virtual ~Student() { delete[] ocenki; }
};

class Predavach {
private:
    Kurs kursevi[10];
    int brojKursevi;
protected:
    char *imeIPrezime;
public:
    Predavach(const char *imeIPrezime, Kurs *kursevi, const int brojKursevi) {
        this->brojKursevi = brojKursevi;
        for (int i = 0; i < brojKursevi; i++) this->kursevi[i] = kursevi[i];
        this->imeIPrezime = new char[strlen(imeIPrezime) + 1];
        strcpy(this->imeIPrezime, imeIPrezime);
    }

    Predavach(const Predavach &p) {
        this->brojKursevi = p.brojKursevi;
        for (int i = 0; i < p.brojKursevi; i++) this->kursevi[i] = p.kursevi[i];
        this->imeIPrezime = new char[strlen(p.imeIPrezime) + 1];
        strcpy(this->imeIPrezime, p.imeIPrezime);
    }

    Predavach operator=(const Predavach &p) {
        if (this != &p) {
            this->brojKursevi = p.brojKursevi;
            for (int i = 0; i < p.brojKursevi; i++)
                this->kursevi[i] = p.kursevi[i];
            this->imeIPrezime = new char[strlen(p.imeIPrezime) + 1];
            delete[] imeIPrezime;
            strcpy(this->imeIPrezime, p.imeIPrezime);
        }
        return *this;
    }

    const int getBrojKursevi() const { return brojKursevi; }

    const char *const getImeIPrezime() const { return imeIPrezime; }

    Kurs operator[](int i) const {
        if (i < brojKursevi && i >= 0)
            return kursevi[i];
        else return Kurs();
    }

    const void pecati() const {
        cout << imeIPrezime << " (";
        for (int i = 0; i < brojKursevi; i++) {
            kursevi[i].pecati();
            if (i < brojKursevi - 1)
                cout << ", ";
            else
                cout << ")";
        }
    }

    virtual ~Predavach() { delete[] imeIPrezime; }
};

//mesto za vashiot kod

class Demonstrator : public Student, public Predavach {
private:
    int brojNaCasovi;
public:
    Demonstrator(const int indeks, const int *ocenki, const int brojOcenki,
                 const char *imeIPrezime, Kurs *kursevi, const int brojKursevi,
                 const int brojNaCasovi)
            : Student(indeks, ocenki, brojOcenki), Predavach(imeIPrezime, kursevi,
                                                             brojKursevi) {
        this->brojNaCasovi = brojNaCasovi;
    }

    const int getBodovi() const {
        if (getBrojKursevi() == 0)
            throw NoCourseException(" ne drzi laboratoriski vezbi\n");
        int bodoviLaboratoriski = (20 * brojNaCasovi) / getBrojKursevi();
        return Student::getBodovi() + bodoviLaboratoriski;
    }

    const void pecati() const {
        Student::pecati();
        cout << ": ";
        Predavach::pecati();
    }

    const bool daliDemonstrator() const {
        return true;
    }

    ~Demonstrator() {}
};

Student &vratiNajdobroRangiran(Student **studenti, int n) {
    Student *max = studenti[0];
    for (int i = 0; i < n; ++i) {
        try {
            if (max->getBodovi() < studenti[i]->getBodovi())
                max = studenti[i];
        } catch (NoCourseException &e) {
            cout << "Demonstratorot so indeks " << studenti[i]->getIndeks() << e;
        }
    }
    return *max;
}

const void pecatiDemonstratoriKurs(const char *kurs, Student **studenti, const int n) {
    for (int i = 0; i < n; ++i) {
        if (studenti[i]->daliDemonstrator()) {
            Demonstrator *d = dynamic_cast<Demonstrator *>(studenti[i]);
            for (int j = 0; j < d->getBrojKursevi(); ++j) {
                if ((*d)[j] == kurs) {
                    d->pecati();
                    cout << endl;
                }
            }
        }
    }
}

int main() {
    Kurs kursevi[10];
    int indeks, brojKursevi, ocenki[20], ocenka, brojOcenki, tip, brojCasovi, krediti;
    char ime[20], imeIPrezime[50];
    cin >> tip;
    if (tip == 1) { //test class Demonstrator
        cout << "-----TEST Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;
        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                       brojCasovi);
        cout << "Objekt od klasata Demonstrator e kreiran";
    } else if (tip == 2) { //funkcija pecati vo Student
        cout << "-----TEST pecati-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }

        Student s(indeks, ocenki, brojOcenki);
        s.pecati();

    } else if (tip == 3) { //funkcija getVkupnaOcenka vo Student
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        Student s(indeks, ocenki, brojOcenki);
        try {
        cout << "Broj na bodovi: " << s.getBodovi() << endl;
        } catch (NoCourseException &e) {
            cout << "Demonstratorot so indeks " << s.getIndeks() << e;
        }

    } else if (tip == 4) { //funkcija getVkupnaOcenka vo Demonstrator
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;
        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                       brojCasovi);
        try {
        cout << "Broj na bodovi: " << d.getBodovi() << endl;
        } catch (NoCourseException &e) {
            cout << "Demonstratorot so indeks " << d.getIndeks() << e;
        }
    } else if (tip == 5) { //funkcija pecati vo Demonstrator
        cout << "-----TEST pecati -----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;
        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                       brojCasovi);
        d.pecati();
    } else if (tip == 6) { //site klasi
        cout << "-----TEST Student i Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;
        Student *s = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi,
                                      brojKursevi, brojCasovi);
        s->pecati();
        try {
            cout << "\nBroj na bodovi: " << s->getBodovi() << endl;
        } catch (NoCourseException &e) {
            cout << "Demonstratorot so indeks " << s->getIndeks() << e;
        }
        delete s;
    } else if (tip == 7) { //funkcija vratiNajdobroRangiran
        cout << "-----TEST vratiNajdobroRangiran-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime,
                                               kursevi, brojKursevi,
                                               brojCasovi);
            }
        }
        Student &najdobar = vratiNajdobroRangiran(studenti, k);
        cout << "Maksimalniot broj na bodovi e:" << najdobar.getBodovi();
        cout << "\nNajdobro rangiran:";
        najdobar.pecati();
        for (int j = 0; j < k; j++)
            delete studenti[j];
        delete[] studenti;
    } else if (tip == 8) { //funkcija pecatiDemonstratoriKurs
        cout << "-----TEST pecatiDemonstratoriKurs-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime,
                                               kursevi, brojKursevi, brojCasovi);
            }
        }
        char kurs[20];
        cin >> kurs;
        cout << "Demonstratori na " << kurs << " se:" << endl;
        pecatiDemonstratoriKurs(kurs, studenti, k);
        for (int j = 0; j < k; j++)
            delete studenti[j];
        delete[] studenti;
    }
    return 0;
}