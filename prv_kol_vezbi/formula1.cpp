//
// Created by krstevkoki on 3/29/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class F1Trka {
private:
    char race_name[30];
    char *driver_name;
    float time;
    float record_time;
public:

    F1Trka(char *race_name = "", char *driver_name = "", float time = 0.0, float record_time = 0.0) {
        strcpy(this->race_name, race_name);
        this->time = time;
        this->record_time = record_time;
        this->driver_name = new char[strlen(driver_name) + 1];
        strcpy(this->driver_name, driver_name);
    }

    F1Trka(const F1Trka &trka) {
        strcpy(this->race_name, trka.race_name);
        this->time = trka.time;
        this->record_time = trka.record_time;
        this->driver_name = new char[strlen(trka.driver_name) + 1];
        strcpy(this->driver_name, trka.driver_name);
    }

    F1Trka &operator=(const F1Trka &trka) {
        if (this != &trka) {
            strcpy(this->race_name, trka.race_name);
            this->time = trka.time;
            this->record_time = trka.record_time;
            delete[] this->driver_name;
            this->driver_name = new char[strlen(trka.driver_name) + 1];
            strcpy(this->driver_name, trka.driver_name);
        }
        return *this;
    }

    ~F1Trka() { delete[] driver_name; }

    void pecati() {
        cout << race_name << ", " << driver_name << " " << time << endl;
    }

    const float getTime() {
        return time;
    }

    const float getRecordTime() {
        return record_time;
    }
};

class F1Shampionat {
private:
    int year;
    F1Trka *races;
    int num_races;
public:
    F1Shampionat(int year) {
        this->year = year;
        this->races = NULL;
        this->num_races = 0;
    }

    F1Shampionat(const F1Shampionat &f1s) {
        this->year = f1s.year;
        this->num_races = f1s.num_races;
        this->races = new F1Trka[f1s.num_races];
        for (int i = 0; i < f1s.num_races; ++i) {
            this->races[i] = f1s.races[i];
        }
    }

    F1Shampionat &operator=(const F1Shampionat &f1s) {
        if (this != &f1s) {
            this->year = f1s.year;
            this->num_races = f1s.num_races;
            delete[] this->races;
            this->races = new F1Trka[f1s.num_races];
            for (int i = 0; i < f1s.num_races; ++i) {
                this->races[i] = f1s.races[i];
            }
        }
        return *this;
    }

    ~F1Shampionat() { delete[] races; }

    void dodadiTrka(F1Trka T) {
        F1Trka *tmp = new F1Trka[num_races + 1];
        for (int i = 0; i < num_races; ++i) {
            tmp[i] = races[i];
        }
        delete[] races;
        races = tmp;
        races[num_races++] = T;
    }

    void noviRekordi() {
        for (int i = 0; i < num_races; ++i) {
            if (races[i].getTime() < races[i].getRecordTime())
                races[i].pecati();
        }
    }
};

int main() {
    F1Shampionat f1(2015);
    int n;
    float vr, re;
    char ime[30];
    char pobednik[40];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> pobednik;
        cin >> vr;
        cin >> re;
        F1Trka t(ime, pobednik, vr, re);
        f1.dodadiTrka(t);
    }
    f1.noviRekordi();
    return 0;
}