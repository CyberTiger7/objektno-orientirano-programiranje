//
// Created by krstevkoki on 4/23/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char name[100];
    int age;
    int num_races;
    bool veteran;
public:
    Vozac(const char *name, const int age, const int num_races, const bool veteran) {
        strcpy(this->name, name);
        this->age = age;
        this->num_races = num_races;
        this->veteran = veteran;
    }

    friend ostream &operator<<(ostream &out, const Vozac &v) {
        if (v.veteran) {
            out << v.name << endl;
            out << v.age << endl;
            out << v.num_races << endl;
            out << "VETERAN" << endl;
        } else {
            out << v.name << endl;
            out << v.age << endl;
            out << v.num_races << endl;
        }
        return out;
    }

    virtual const float earningPerRace() const = 0;

    virtual const float customPerDriver() = 0;

    bool operator==(const Vozac &v) {
        return this->earningPerRace() == v.earningPerRace();
    }

    virtual ~Vozac() {}
};

class Avtomobilist : public Vozac {
private:
    float carPrice;
public:
    Avtomobilist(const char *name, const int age, const int num_races, const bool veteran,
                 const float carPrice)
            : Vozac(name, age, num_races, veteran) {
        this->carPrice = carPrice;
    }

    const float earningPerRace() const {
        return carPrice / float(5);
    }

    const float customPerDriver() {
        if (num_races >= 10)
            return (float(15) / 100) * earningPerRace();
        return (float(10) / 100) * earningPerRace();
    }
};

class Motociklist : public Vozac {
private:
    int enginePower;
public:
    Motociklist(const char *name, const int age, const int num_races, const bool veteran,
                const int enginePower)
            : Vozac(name, age, num_races, veteran) {
        this->enginePower = enginePower;
    }

    const float earningPerRace() const {
        return enginePower * 20;
    }

    const float customPerDriver() {
        if (veteran) {
            return (float(25) / 100) * earningPerRace();
        }
        return (float(20) / 100) * earningPerRace();
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx) {
    int counter = 0;

    for (int i = 0; i < n; ++i) {
        if (*v[i] == *vx)
            ++counter;
    }

    return counter;
}

int main() {
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    int n, x;

    cin >> n >> x;
    Vozac **v = new Vozac *[n];

    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }

    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->customPerDriver() << endl;
    }

    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;

    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);

    for (int i = 0; i < n; ++i)
        delete v[i];
    delete[] v;
    delete vx;

    return 0;
}
