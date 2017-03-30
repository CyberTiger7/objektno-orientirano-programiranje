//
// Created by krstevkoki on 3/29/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Patnik {
private:
    char name[100];
    int carriage_class;
    bool bike;
public:
    Patnik(char *name = "", int carriage_class = 0, bool bike = 0) {
        strcpy(this->name, name);
        this->carriage_class = carriage_class;
        this->bike = bike;
    }

    Patnik(const Patnik &passenger) {
        strcpy(this->name, passenger.name);
        this->carriage_class = passenger.carriage_class;
        this->bike = passenger.bike;
    }

    friend ostream &operator<<(ostream &out, const Patnik &passenger) {
        out << passenger.name << endl;
        out << passenger.carriage_class << endl;
        out << passenger.bike << endl;
        return out;
    }

    const bool getBike() const {
        return bike;
    }

    const int getClass() const {
        return carriage_class;
    }
};

class Voz {
private:
    char destination[100];
    Patnik *passengers;
    int num_passengers;
    int bikes_allowed;
public:
    Voz(char *destination, int bikes_allowed) {
        strcpy(this->destination, destination);
        this->bikes_allowed = bikes_allowed;
        this->passengers = NULL;
        this->num_passengers = 0;
    }

    Voz(const Voz &train) {
        strcpy(this->destination, train.destination);
        this->bikes_allowed = train.bikes_allowed;
        this->num_passengers = train.num_passengers;
        this->passengers = new Patnik[train.num_passengers];
        for (int i = 0; i < train.num_passengers; ++i) {
            this->passengers[i] = train.passengers[i];
        }
    }

    Voz &operator=(const Voz &train) {
        if (this != &train) {
            strcpy(this->destination, train.destination);
            this->bikes_allowed = train.bikes_allowed;
            this->num_passengers = train.num_passengers;
            delete[] this->passengers;
            this->passengers = new Patnik[train.num_passengers];
            for (int i = 0; i < train.num_passengers; ++i) {
                this->passengers[i] = train.passengers[i];
            }
        }
        return *this;
    }

    Voz &operator+=(const Patnik &passenger) {
        if (passenger.getBike()) {
            if (bikes_allowed != 0) {
                Patnik *tmp = new Patnik[num_passengers + 1];
                for (int i = 0; i < num_passengers; ++i) {
                    tmp[i] = passengers[i];
                }
                delete[] passengers;
                passengers = tmp;
                passengers[num_passengers++] = passenger;
                //--bikes_allowed;
            }
        } else {
            Patnik *tmp = new Patnik[num_passengers + 1];
            for (int i = 0; i < num_passengers; ++i) {
                tmp[i] = passengers[i];
            }
            delete[] passengers;
            passengers = tmp;
            passengers[num_passengers++] = passenger;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Voz &train) {
        out << train.destination << endl;
        for (int i = 0; i < train.num_passengers; ++i) {
            cout << train.passengers[i] << endl;
        }
        return out;
    }

    ~Voz() { delete[] passengers; }

    void patniciNemaMesto() {
        int num_passengers_per_class[2];
        num_passengers_per_class[0] = 0;
        num_passengers_per_class[1] = 0;
        for (int i = 0; i < num_passengers; ++i) {
            if (passengers[i].getClass() == 1) {
                if (passengers[i].getBike())
                    num_passengers_per_class[0]++;
            } else {
                if (passengers[i].getBike())
                    num_passengers_per_class[1]++;
            }
        }
        int first_class_left = 0;
        int second_class_left = 0;
        int temp_bikes_allowed = bikes_allowed;
        if (bikes_allowed < num_passengers_per_class[0]) {
            first_class_left = num_passengers_per_class[0] - bikes_allowed;
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << first_class_left << endl;
            temp_bikes_allowed = 0;
        } else {
            first_class_left = 0;
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << first_class_left << endl;
            temp_bikes_allowed -= num_passengers_per_class[0];
        }

        if (temp_bikes_allowed == 0) {
            second_class_left = num_passengers_per_class[1];
            cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << second_class_left << endl;
        } else {
            if (temp_bikes_allowed < num_passengers_per_class[1]) {
                second_class_left = num_passengers_per_class[1] - temp_bikes_allowed;
                cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << second_class_left << endl;
            } else {
                second_class_left = 0;
                cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << second_class_left << endl;
            }
        }
    }
};

int main() {
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++) {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
