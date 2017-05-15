//
// Created by krstevkoki on 4/23/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Transport {
protected:
    char destination[20];
    int price;
    int destination_length;
public:
    Transport(const char *destination, const int price, const int destination_length) {
        strcpy(this->destination, destination);
        this->price = price;
        this->destination_length = destination_length;
    }

    virtual const int cenaTransport() const = 0;

    bool operator<(const Transport &t) {
        return destination_length < t.destination_length;
    }

    const int getPrice() const {
        return price;
    }

    const char *getDestination() const {
        return destination;
    }

    const int getDestinationLength() const {
        return destination_length;
    }

    virtual ~Transport() {}
};

class AvtomobilTransport : public Transport {
private:
    bool paidDriver;
public:
    AvtomobilTransport(const char *destination, const int price, const int destination_length,
                       const bool paidDriver)
            : Transport(destination, price, destination_length) {
        this->paidDriver = paidDriver;
    }

    const int cenaTransport() const {
        if (paidDriver)
            return price + (20 / float(100)) * price;
        return price;
    }
};

class KombeTransport : public Transport {
private:
    int num_people;
public:
    KombeTransport(const char *destination, const int price, const int destination_length,
                   const int num_people)
            : Transport(destination, price, destination_length) {
        this->num_people = num_people;
    }

    const int cenaTransport() const {
        return price - (num_people * 200);
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &t) {
    Transport *tmp[n];
    int newLength = 0;
    for (int i = 0, j = 0; i < n; ++i) {
        if (ponudi[i]->cenaTransport() > t.cenaTransport()) {
            tmp[j++] = ponudi[i];
            ++newLength;
        }
    }
    n = newLength;
    Transport *temporary[n];
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!(*tmp[j] < *tmp[j + 1])) {
                temporary[j] = tmp[j];
                tmp[j] = tmp[j + 1];
                tmp[j + 1] = temporary[j];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << tmp[i]->getDestination() << " " << tmp[i]->getDestinationLength() << " " <<
             tmp[i]->cenaTransport() << endl;
    }
}

int main() {
    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {
        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }
    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++)
        delete ponudi[i];
    delete[] ponudi;

    return 0;
}