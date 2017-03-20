//
// Created by krstevkoki on 3/20/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Automobile {
private:
    char *name;
    int *registration;
    int maxSpeed;
public:
    Automobile(char *name = "", const int *registration = 0, int maxSpeed = 0) {
        this->maxSpeed = maxSpeed;
        this->registration = new int[5];
        if (registration == 0) {
            for (int i = 0; i < 5; ++i) {
                this->registration[i] = 0;
            }
        } else {
            for (int i = 0; i < 5; ++i) {
                this->registration[i] = registration[i];
            }
        }
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Automobile(const Automobile &a) {
        this->maxSpeed = a.maxSpeed;
        this->registration = new int[5];
        for (int i = 0; i < 5; ++i) {
            this->registration[i] = a.registration[i];
        }
        this->name = new char[strlen(a.name) + 1];
        strcpy(this->name, a.name);
    }

    Automobile &operator=(const Automobile &a) {
        if (this != &a) {
            this->maxSpeed = a.maxSpeed;
            delete[] this->registration;
            this->registration = new int[5];
            for (int i = 0; i < 5; ++i) {
                this->registration[i] = a.registration[i];
            }
            delete[] this->name;
            this->name = new char[strlen(a.name) + 1];
            strcpy(this->name, a.name);
        }
        return *this;
    }

    bool operator==(const Automobile &a) {
        for (int i = 0; i < 5; ++i) {
            if (this->registration[i] != a.registration[i])
                return false;
        }
        return true;
    }

    friend ostream &operator<<(ostream &out, const Automobile &a) {

        out << "Marka\t" << a.name << "\tRegistracija[ ";
        for (int i = 0; i < 5; ++i) {
            out << a.registration[i] << " ";
        }
        out << "]" << endl;
        return out;
    }

    ~Automobile() {
        delete[] name;
        delete[] registration;
    }

    const int getMaxSpeed() {
        return maxSpeed;
    }
};

class RentACar {
private:
    char name[100];
    Automobile *car;
    int num_cars;
public:
    RentACar(char *name) {
        strcpy(this->name, name);
        this->num_cars = 0;
        this->car = new Automobile[this->num_cars];
    }

    RentACar(const RentACar &agency) {
        strcpy(this->name, agency.name);
        this->num_cars = agency.num_cars;
        this->car = new Automobile[agency.num_cars];
        for (int i = 0; i < agency.num_cars; ++i) {
            this->car[i] = agency.car[i];
        }
    }

    RentACar &operator=(const RentACar &agency) {
        if (this != &agency) {
            strcpy(this->name, agency.name);
            this->num_cars = agency.num_cars;
            delete[] this->car;
            this->car = new Automobile[agency.num_cars];
            for (int i = 0; i < agency.num_cars; ++i) {
                this->car[i] = agency.car[i];
            }
        }
        return *this;
    }

    RentACar &operator+=(const Automobile &a) {
        Automobile *temp = new Automobile[num_cars + 1];
        for (int i = 0; i < num_cars; ++i) {
            temp[i] = car[i];
        }
        delete[] car;
        car = temp;
        car[num_cars++] = a;
        return *this;
    }

    RentACar &operator-=(Automobile &a) {
        int newLength = 0;
        Automobile *tmp = new Automobile[num_cars - 1];
        for (int i = 0, j = 0; i < num_cars; ++i) {
            if (!(this->car[i] == a)) {
                tmp[j++] = this->car[i];
                newLength++;
            }
        }
        delete[] this->car;
        this->car = tmp;
        num_cars = newLength;
        return *this;
    }

    ~RentACar() { delete[] car; }

    void pecatiNadBrzina(int max) {
        cout << name << endl;
        for (int i = 0; i < num_cars; ++i) {
            if (car[i].getMaxSpeed() > max)
                cout << car[i];
        }
    }
};

int main() {
    RentACar agencija("FINKI-Car");
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char marka[100];
        int registracija[5];
        int maximumBrzina;

        cin >> marka;

        for (int j = 0; j < 5; ++j)
            cin >> registracija[j];

        cin >> maximumBrzina;

        Automobile nov = Automobile(marka, registracija, maximumBrzina);
        //dodavanje na avtomobil
        agencija += nov;
    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin >> marka;
    for (int i = 0; i < 5; i++)
        cin >> regisracija[i];
    cin >> maximumBrzina;

    Automobile greshka = Automobile(marka, regisracija, maximumBrzina);

    //brishenje na avtomobil
    agencija -= greshka;

    agencija.pecatiNadBrzina(150);
    return 0;
}