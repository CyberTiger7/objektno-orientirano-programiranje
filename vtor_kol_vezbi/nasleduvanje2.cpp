//
// Created by krstevkoki on 4/25/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Ekskurzija {
private:
    char name[50];
    int vehicle;
    int month;
    int duration;
    double price;
    int num_tourists;
public:
    Ekskurzija() {
        strcpy(name, "");
        this->vehicle = 0;
        this->month = 0;
        this->duration = 0;
        this->price = 0.00;
        this->num_tourists = 0;
    }

    Ekskurzija(const char *name, const int vehicle, const int month, const int duration,
               const double price, const int num_tourists) {
        strcpy(this->name, name);
        this->vehicle = vehicle;
        this->month = month;
        this->duration = duration;
        this->price = price;
        this->num_tourists = num_tourists;
    }

    Ekskurzija(const Ekskurzija &e) {
        strcpy(this->name, e.name);
        this->vehicle = e.vehicle;
        this->month = e.month;
        this->duration = e.duration;
        this->price = e.price;
        this->num_tourists = e.num_tourists;
    }

    Ekskurzija &operator=(const Ekskurzija &e) {
        if (this != &e) {
            strcpy(this->name, e.name);
            this->vehicle = e.vehicle;
            this->month = e.month;
            this->duration = e.duration;
            this->price = e.price;
            this->num_tourists = e.num_tourists;
        }
        return *this;
    }

    const int getMonth() {
        return month;
    }

    const int getDuration() {
        return duration;
    }

    const double getPrice() {
        return price;
    }

    const int getNum_Tourists() {
        return num_tourists;
    }

    const int getVehicle() {
        return vehicle;
    }
};

class TuristichkaAgencija {
protected:
    char name[50];
    Ekskurzija trips[5];
    int num_trips;
public:
    TuristichkaAgencija() {
        strcpy(this->name, "");
        this->num_trips = 0;
    }

    TuristichkaAgencija(const char *name, const Ekskurzija *trips, const int num_trips) {
        strcpy(this->name, name);
        this->num_trips = num_trips;
        for (int i = 0; i < num_trips; ++i) {
            this->trips[i] = trips[i];
        }
    }

    virtual const double vkupnaDobivka() = 0;

    virtual ~TuristichkaAgencija() {}
};

class OnlineTuristichkaAgencija : public TuristichkaAgencija {
private:

public:
    OnlineTuristichkaAgencija() : TuristichkaAgencija() {}

    OnlineTuristichkaAgencija(const char *name, const Ekskurzija *trips, const int num_trips)
            : TuristichkaAgencija(name, trips, num_trips) {}

    const double vkupnaDobivka() {
        float price = 0.00;
        for (int i = 0; i < num_trips; ++i) {
            if (trips[i].getMonth() == 6 || trips[i].getMonth() == 7 || trips[i].getMonth() == 8) {
                double k = 2.5;
                price += (trips[i].getDuration() * trips[i].getPrice() * trips[i].getNum_Tourists()) +
                         (20 * k);
            } else {
                if (trips[i].getVehicle()) { // if the vehicle is aeroplane
                    double k = 2.2;
                    price += (trips[i].getDuration() * trips[i].getPrice() * trips[i].getNum_Tourists()) +
                             (20 * k);
                } else { // if the vehicle is something other
                    double k = 1.8;
                    price += (trips[i].getDuration() * trips[i].getPrice() * trips[i].getNum_Tourists()) +
                             (20 * k);
                }
            }
        }
        return price;
    }
};

class TradicionalnaTuristichkaAgencija : public TuristichkaAgencija {
private:

public:
    TradicionalnaTuristichkaAgencija() : TuristichkaAgencija() {}

    TradicionalnaTuristichkaAgencija(const char *name, const Ekskurzija *trips, const int num_trips)
            : TuristichkaAgencija(name, trips, num_trips) {}

    const double vkupnaDobivka() {
        float price = 0.00;
        for (int i = 0; i < num_trips; ++i) {
            if (trips[i].getMonth() == 6 || trips[i].getMonth() == 7 || trips[i].getMonth() == 8) {
                double k = 1.8;
                price += (trips[i].getDuration() * trips[i].getPrice() * trips[i].getNum_Tourists())
                         + (30 * k);
            } else {
                double k = 1.3;
                price += (trips[i].getDuration() * trips[i].getPrice() * trips[i].getNum_Tourists())
                         + (30 * k);
            }
        }
        return price;
    }
};

int main() {
    char agency[50];
    double freq;
    int numOnlineE, numTradE;
    Ekskurzija online[5];
    Ekskurzija traditional[5];
    cin >> numOnlineE >> numTradE;
    for (int i = 0; i < numOnlineE; i++) {
        char name[50];
        int vehicle, month, duration, price, tourists;
        cin >> name >> vehicle >> month >> duration >> price >> tourists;
        Ekskurzija e(name, vehicle, month, duration, price, tourists);
        online[i] = e;
    }
    cin >> agency;
    OnlineTuristichkaAgencija onlineAgency(agency, online, numOnlineE);
    for (int i = 0; i < numTradE; i++) {
        char name[50];
        int vehicle, month, duration, price, tourists;
        cin >> name >> vehicle >> month >> duration >> price >> tourists;
        Ekskurzija e(name, vehicle, month, duration, price, tourists);
        traditional[i] = e;
    }
    cin >> agency;
    TradicionalnaTuristichkaAgencija traditionalAgency(agency, traditional, numTradE);
    cout << onlineAgency.vkupnaDobivka() << endl;
    cout << traditionalAgency.vkupnaDobivka() << endl;
    return 0;
}