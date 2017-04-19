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
    Automobile() {
        this->name = NULL;
        this->registration = NULL;
        this->maxSpeed = 0;
    }

    Automobile(const char *name, const int *registration, const int maxSpeed) {
        this->maxSpeed = maxSpeed;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->registration = new int[5];
        for (int i = 0; i < 5; ++i) {
            this->registration[i] = registration[i];
        }
    }

    Automobile(const Automobile &a) {
        this->maxSpeed = a.maxSpeed;
        this->name = new char[strlen(a.name) + 1];
        strcpy(this->name, a.name);
        this->registration = new int[5];
        for (int i = 0; i < 5; ++i) {
            this->registration[i] = a.registration[i];
        }
    }

    Automobile &operator=(const Automobile &a) {
        if (this != &a) {
            this->maxSpeed = a.maxSpeed;
            delete[] this->name;
            this->name = new char[strlen(a.name) + 1];
            strcpy(this->name, a.name);
            delete[] this->registration;
            this->registration = new int[5];
            for (int i = 0; i < 5; ++i) {
                this->registration[i] = a.registration[i];
            }
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Automobile &a) {
        out << "Marka\t" << a.name << "\tRegistracija[ ";
        for (int i = 0; i < 5; ++i) {
            out << a.registration[i] << " ";
        }
        out << "]" << endl;
        return out;
    }

    bool operator==(const Automobile &a) {
        for (int i = 0; i < 5; ++i) {
            if (this->registration[i] != a.registration[i])
                return false;
        }
        return true;
    }

    const int getMaxSpeed() {
        return maxSpeed;
    }

    ~Automobile() {
        delete[] name;
        delete[] registration;
    }
};

class RentACar {
private:
    char name[100];
    Automobile *cars;
    int num_cars;
public:
    RentACar(const char *name) {
        strcpy(this->name, name);
        this->cars = NULL;
        this->num_cars = 0;
    }

    RentACar(const RentACar &agency) {
        this->num_cars = agency.num_cars;
        strcpy(this->name, agency.name);
        this->cars = new Automobile[agency.num_cars];
        for (int i = 0; i < agency.num_cars; ++i) {
            this->cars[i] = agency.cars[i];
        }
    }

    RentACar &operator=(const RentACar &agency) {
        if (this != &agency) {
            this->num_cars = agency.num_cars;
            strcpy(this->name, agency.name);
            delete[] this->cars;
            this->cars = new Automobile[agency.num_cars];
            for (int i = 0; i < agency.num_cars; ++i) {
                this->cars[i] = agency.cars[i];
            }
        }
        return *this;
    }

    RentACar &operator+=(const Automobile &a) {
        Automobile *tmp = new Automobile[num_cars + 1];
        for (int i = 0; i < num_cars; ++i) {
            tmp[i] = cars[i];
        }
        delete[] cars;
        cars = tmp;
        cars[num_cars++] = a;
        return *this;
    }

    RentACar &operator-=(const Automobile &a) {
        int newSize = 0;
        bool flag = true;  // used as an indicator if there is a car that has to be removed.
        for (int i = 0; i < num_cars; ++i) {
            if (!(cars[i] == a))
                flag = false;
            else {
                flag = true;
                break;
            }
        }
        /* if the flag is true, there is a car that has to be removed
         otherwise return the same object. */
        if (flag) {
            Automobile *tmp = new Automobile[num_cars - 1];
            for (int i = 0, j = 0; i < num_cars; ++i) {
                if (!(cars[i] == a)) {
                    tmp[j++] = cars[i];
                    ++newSize;
                }
            }
            delete[] cars;
            cars = tmp;
            num_cars = newSize;
        }
        return *this;
    }

    void pecatiNadBrzina(const int max) {
        cout << name << endl;
        for (int i = 0; i < num_cars; ++i) {
            if (cars[i].getMaxSpeed() > max)
                cout << cars[i];
        }
    }

    ~RentACar() { delete[] cars; }
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