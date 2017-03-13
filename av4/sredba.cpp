//
// Created by krstevkoki on 3/13/17.
//

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Momche {
private:
    char name[50];
    char surname[50];
    int age;
public:
    Momche(char *name = "", char *surname = "", int age = 0) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->age = age;
    }

    Momche(const Momche &boy) {
        strcpy(this->name, boy.name);
        strcpy(this->surname, boy.surname);
        this->age = boy.age;
    }

    ~Momche() {

    }

    const void Show() {
        cout << "Momche: " << name << " " << surname << " " << age << endl;
    }

    int get_Age() {
        return age;
    }
};

class Devojche {
private:
    char name[50];
    char surname[50];
    int age;
public:
    Devojche(char *name = "", char *surname = "", int age = 0) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->age = age;
    }

    Devojche(const Devojche &girl) {
        strcpy(this->name, girl.name);
        strcpy(this->surname, girl.surname);
        this->age = girl.age;
    }

    ~Devojche() {

    }

    void const Show() {
        cout << "Devojche: " << name << " " << surname << " " << age << endl;
    }

    int get_Age() {
        return age;
    }
};

class Sredba {
private:
    Momche boy;
    Devojche girl;
public:
    Sredba() {

    }

    Sredba(const Momche _boy, const Devojche _girl) {
        boy = _boy;
        girl = _girl;
    }

    ~Sredba() {

    }

    void const Show() {
        cout << "Sredba: " << endl;
        boy.Show();
        girl.Show();
    }

    void daliSiOdgovaraat() {
        if (abs(boy.get_Age() - girl.get_Age()) <= 5) {
            cout << "Si odgovaraat" << endl;
        } else
            cout << "Ne si odgovaraat" << endl;
    }
};

int main() {
    int age;
    char name[50];
    char surname[50];

    cout << "Informacii za momche: " << endl;
    cout << "Ime: ";
    cin >> name;
    cout << "Prezime: ";
    cin >> surname;
    cout << "Godini: ";
    cin >> age;
    Momche m(name, surname, age);
    Momche boy(m); // eksplicitno povikuvanje na copy konstruktor za boy

    cout << "Informacii za Devojche: " << endl;
    cout << "Ime: ";
    cin >> name;
    cout << "Prezime: ";
    cin >> surname;
    cout << "Godini: ";
    cin >> age;
    Devojche d(name, surname, age);
    Devojche girl = d; // eksplicitno povikuvanje na copy konstruktor za girl

    Sredba s(boy, girl);
    s.Show();
    s.daliSiOdgovaraat(); // implicitno povikuvanje na copy konstruktor za momche i devojche
    return 0;
}