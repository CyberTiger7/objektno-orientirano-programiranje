//
// Created by krstevkoki on 4/25/17.
//
#include <iostream>
#include <cstring>
#include <cmath>

#define PI 3.14

using namespace std;


class Igrachka {
public:
    virtual float getVolumen() = 0;

    virtual float getMasa() = 0;

    virtual ~Igrachka() {}
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    // да се имплементираат потребните методи
    Forma(const char *colour, const int density) {
        strcpy(this->boja, colour);
        this->gustina = density;
    }

    virtual ~Forma() {}
};

class Topka : public Forma, public Igrachka {
private:
    int radius;
public:
    Topka(const char *colour, const int density, const int radius)
            : Forma(colour, density) {
        this->radius = radius;
    }

    float getVolumen() {
        return float(4 * PI * pow(radius, 3) / float(3));
    }

    float getMasa() {
        return getVolumen() * gustina;
    }
};

class Kocka : public Forma, public Igrachka {
private:
    int height;
    int width;
    int depth;
public:
    Kocka(const char *colour, const int density, const int height, const int width, const int depth)
            : Forma(colour, density) {
        this->height = height;
        this->width = width;
        this->depth = depth;
    }

    float getVolumen() {
        return height * width * depth;
    }

    float getMasa() {
        return getVolumen() * gustina;
    }
};

bool totalMass(Igrachka **toys, int n, Igrachka &Petra) {
    float totalMass = 0.0;
    for (int i = 0; i < n; ++i) {
        totalMass += toys[i]->getMasa();
    }
    return totalMass > Petra.getMasa();
}

float difference(Igrachka **toys, int n, Igrachka &Petra) {
    Igrachka *max = toys[0];
    for (int i = 1; i < n; ++i) {
        if (max->getVolumen() < toys[i]->getVolumen())
            max = toys[i];
    }
    return abs(max->getVolumen() - Petra.getVolumen());
}

int main() {
    //vnesi informacii za kupche
    char colour[100];
    int density, type, n;
    cin >> n;
    Igrachka **kupche = new Igrachka *[n];

    for (int i = 0; i < n; ++i) {
        cin >> type >> colour >> density;
        if (type == 1) {
            int radius;
            cin >> radius;
            kupche[i] = new Topka(colour, density, radius);
        } else {
            int height, width, depth;
            cin >> height >> width >> depth;
            kupche[i] = new Kocka(colour, density, height, width, depth);
        }
    }

    //vnesi informacii za igrachkata na Petra
    int height, width, depth;
    cin >> colour >> density >> height >> width >> depth;
    Kocka Petra = Kocka(colour, density, height, width, depth);

    //baranje 1
    if (totalMass(kupche, n, Petra))
        cout << "DA" << endl;
    else
        cout << "NE" << endl;

    //baranje 2
    cout << "Razlikata e: " << difference(kupche, n, Petra);

    for (int i = 0; i < n; ++i) {
        delete kupche[i];
    }
    delete[] kupche;

    return 0;
}