//
// Created by krstevkoki on 4/22/17.
//
#include <iostream>

using namespace std;

class Vozilo {
protected:
    float weight;
    int width;
    int height;
public:
    Vozilo(const float weight, const int width, const int height) {
        this->weight = weight;
        this->width = width;
        this->height = height;
    }

    virtual const float getMaxWeight() = 0;

    virtual const float vratiDnevnaCena() = 0;

    virtual const int vehicleType() = 0;

    const float getWeight() {
        return weight;
    }

    const int getWidth() {
        return width;
    }
};

class Avtomobil : public Vozilo {
private:
    int num_doors;
public:
    Avtomobil(const float weight, const int width, const int height, const int num_doors)
            : Vozilo(weight, width, height) {
        this->num_doors = num_doors;
    }

    const float vratiDnevnaCena() {
        if (num_doors >= 5)
            return 130;
        return 100;
    }

    const float getMaxWeight() {
        return 0;
    }

    const int vehicleType() {
        return 1;
    }
};

class Avtobus : public Vozilo {
private:
    int num_passengers;
public:
    Avtobus(const float weight, const int width, const int height, const int num_passengers)
            : Vozilo(weight, width, height) {
        this->num_passengers = num_passengers;
    }

    const float vratiDnevnaCena() {
        return 5 * num_passengers;
    }

    const float getMaxWeight() {
        return 0;
    }

    const int vehicleType() {
        return 2;
    }
};

class Kamion : public Vozilo {
private:
    float max_weight;
public:
    Kamion(const float weight, const int width, const int height, const float max_weight)
            : Vozilo(weight, width, height) {
        this->max_weight = max_weight;
    }

    const float vratiDnevnaCena() {
        return (weight + max_weight) * 0.02;
    }

    const float getWeight() {
        return weight + max_weight;
    }

    const int vehicleType() {
        return 3;
    }

    const float getMaxWeight() {
        return max_weight;
    }
};

class ParkingPlac {
private:
    Vozilo **p;
    int num_vehicles;
public:
    ParkingPlac() {
        this->p = new Vozilo *[100];
        this->num_vehicles = 0;
    }

    ParkingPlac(const ParkingPlac &pp) {
        this->num_vehicles = pp.num_vehicles;
        this->p = new Vozilo *[pp.num_vehicles];
        for (int i = 0; i < pp.num_vehicles; ++i) {
            this->p[i] = pp.p[i];
        }
    }

    ParkingPlac &operator=(const ParkingPlac &pp) {
        if (this != &pp) {
            this->num_vehicles = pp.num_vehicles;
            for (int i = 0; i < num_vehicles; ++i) {
                delete this->p[i];
            }
            delete[] this->p;
            this->p = new Vozilo *[pp.num_vehicles];
            for (int i = 0; i < pp.num_vehicles; ++i) {
                this->p[i] = pp.p[i];
            }
        }
        return *this;
    }

    ParkingPlac &operator+=(Vozilo *v) {
        p[num_vehicles++] = v;
        return *this;
    }

    const float presmetajVkupnaMasa() {
        float total_weigth = 0.0;
        for (int i = 0; i < num_vehicles; ++i) {
            total_weigth += p[i]->getWeight();
        }
        return total_weigth;
    }

    int brojVozilaPoshirokiOd(int l) {
        int counter = 0;
        for (int i = 0; i < num_vehicles; ++i) {
            if (p[i]->getWidth() > l)
                ++counter;
        }
        return counter;
    }

    int pogolemaNosivostOd(Vozilo &v) {
        int counter = 0;
        for (int i = 0; i < num_vehicles; ++i) {
            if (p[i]->getMaxWeight() > v.getWeight())
                ++counter;
        }
        return counter;
    }

    int vratiDnevnaZarabotka() {
        int dailyEarnings = 0;
        for (int i = 0; i < num_vehicles; ++i) {
            dailyEarnings += p[i]->vratiDnevnaCena();
        }
        return dailyEarnings;
    }

    void pecati() {
        int number[3];
        for (int i = 0; i < 3; ++i) {
            number[i] = 0;
        }

        for (int i = 0; i < num_vehicles; ++i) {
            if (p[i]->vehicleType() == 1) {
                ++number[0];
            } else if (p[i]->vehicleType() == 2) {
                ++number[1];
            } else if (p[i]->vehicleType() == 3)
                ++number[2];
        }

        cout << "Brojot na avtomobili e " << number[0] << ", brojot na avtobusi e " << number[1]
             << " i brojot na kamioni e " << number[2] << "." << endl;
    }

    ~ParkingPlac() {
        for (int i = 0; i < num_vehicles; ++i) {
            delete p[i];
        }
        delete[] p;
    }
};


int main() {
    ParkingPlac p;

    int n;
    cin >> n;
    int shirina, visina, broj;
    float masa, nosivost;

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> masa >> shirina >> visina >> broj;
            Avtomobil *a = new Avtomobil(masa, shirina, visina, broj);
            p += a;
        }

        if (type == 2) {
            cin >> masa >> shirina >> visina >> broj;
            p += new Avtobus(masa, shirina, visina, broj);
        }

        if (type == 3) {
            cin >> masa >> shirina >> visina >> nosivost;
            p += new Kamion(masa, shirina, visina, nosivost);
        }
    }

    p.pecati();

    cout << "\nZarabotkata e " << p.vratiDnevnaZarabotka() << endl;
    cout << "Vkupnata masa e " << p.presmetajVkupnaMasa() << endl;
    cout << "Brojot poshiroki od 5 e " << p.brojVozilaPoshirokiOd(5) << endl;
    Avtomobil a(1200, 4, 3, 5);
    cout << "Brojot na kamioni so nosivost pogolema od avtomobilot e " << p.pogolemaNosivostOd(a) << endl;

    return 0;
}