//
// Created by krstevkoki on 5/17/17.
//
#include <iostream>
#include <cstring>

using namespace std;

//место за вашиот код

class Delo {
private:
    char name[50];
    int year;
    char country[50];
public:
    Delo(const char *name = "", const int year = 0, const char *country = "") {
        this->year = year;
        strcpy(this->name, name);
        strcpy(this->country, country);
    }

    bool operator==(const Delo &d) {
        return strcmp(this->name, d.name) == 0;
    }

    Delo &operator=(const Delo &d) {
        if (this != &d) {
            this->year = d.year;
            strcpy(this->name, d.name);
            strcpy(this->country, d.country);
        }
        return *this;
    }

    const void setName(const char *name) {
        strcpy(this->name, name);
    }

    const void setYear(const int year) {
        this->year = year;
    }

    const void setCountry(const char *country) {
        strcpy(this->country, country);
    }

    const char *getName() const {
        return name;
    }

    const int getYear() const {
        return year;
    }

    const char *getCountry() const {
        return country;
    }
};

class Pretstava {
private:
    Delo d;
    int num_tickets;
    char date[15];
public:
    Pretstava(const Delo &d, const int num_tickets, const char *date) {
        this->num_tickets = num_tickets;
        strcpy(this->date, date);
        this->d = d;
    }

    virtual const int cena() const {
        int N;
        if (strcmp(d.getCountry(), "Italija") == 0)
            N = 100;
        else if (strcmp(d.getCountry(), "Rusija") == 0)
            N = 150;
        else
            N = 80;

        int M;
        if (d.getYear() >= 1900 && d.getYear() <= 2100)
            M = 50;
        else if (d.getYear() >= 1800 && d.getYear() < 1900)
            M = 75;
        else
            M = 100;
        return M + N;
    }

    const void setDelo(const Delo &d) {
        this->d = d;
    }

    const void setNumTickets(const int num_tickets) {
        this->num_tickets = num_tickets;
    }

    const void setDate(const char *date) {
        strcpy(this->date, date);
    }

    Delo getDelo() const {
        return d;
    }

    const int getNumTickets() const {
        return num_tickets;
    }

    const char *getDate() const {
        return date;
    }

    virtual ~Pretstava() {}
};

class Balet : public Pretstava {
private:
    static int additionalPrice;
public:
    Balet(const Delo &d, const int num_tickets, const char *date)
            : Pretstava(d, num_tickets, date) {}

    const int cena() const {
        return Pretstava::cena() + additionalPrice;
    }

    const static void setAdditionalPrice(const int price) {
        additionalPrice = price;
    }

    ~Balet() {}
};

class Opera : public Pretstava {
public:
    Opera(const Delo &d, const int num_tickets, const char *date)
            : Pretstava(d, num_tickets, date) {}

    const int cena() const {
        return Pretstava::cena();
    }

    ~Opera() {}
};

int Balet::additionalPrice = 150;

//presmetuvanje na prihod
const int prihod(Pretstava **pole, int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        total += (pole[i]->getNumTickets() * pole[i]->cena());
    }
    return total;
}

const int brojPretstaviNaDelo(Pretstava **pole, int n, Delo &d) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (pole[i]->getDelo() == d) {
            ++counter;
        }
    }
    return counter;
}

//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0)
        return new Balet(d, brojProdadeni, data);
    else
        return new Opera(d, brojProdadeni, data);
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1: {
            //Testiranje na klasite Opera i Balet
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getName() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getName() << endl;
        }
            break;
        case 2: {
            //Testiranje na  klasite Opera i Balet so cena
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;
        case 3: {
            //Testiranje na operator ==
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();
            if (f1 == f2)
                cout << "Isti se" << endl;
            else
                cout << "Ne se isti" << endl;
            if (f1 == f3)
                cout << "Isti se" << endl;
            else
                cout << "Ne se isti" << endl;
        }
            break;
        case 4: {
            //testiranje na funkcijata prihod
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
            for (int i = 0; i < n; ++i) {
                delete pole[i];
            }
            delete[] pole;
        }
            break;
        case 5: {
            //testiranje na prihod so izmena na cena za 3d proekcii
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setAdditionalPrice(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
            for (int i = 0; i < n; ++i) {
                delete pole[i];
            }
            delete[] pole;
        }
            break;
        case 6: {
            //testiranje na brojPretstaviNaDelo
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
            for (int i = 0; i < n; ++i) {
                delete pole[i];
            }
            delete[] pole;
        }
            break;
        default:
            break;
    };
    return 0;
}