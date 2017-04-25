//
// Created by krstevkoki on 4/25/17.
//
#include <iostream>
#include <cstring>

using namespace std;

//вашиот код ставете го тука

class SaksiskoCveke {
protected:
    char name[20];
    char family[20];
    int price;
public:
    SaksiskoCveke(const char *name, const int price, const char *family) {
        strcpy(this->name, name);
        strcpy(this->family, family);
        this->price = price;
    }

    const char *getName() const {
        return name;
    }

    const char *getFamily() const {
        return family;
    }

    const int getPrice() const {
        return price;
    }

    virtual const float priceCalculation() = 0;

    bool operator==(const SaksiskoCveke &sc) {
        return (strcmp(this->family, sc.family) == 0);
    }

    virtual ~SaksiskoCveke() {}
};

class BezCvet : public SaksiskoCveke {
private:
    int age;
public:
    BezCvet(const char *name, const int price, const char *family, const int age)
            : SaksiskoCveke(name, price, family) {
        this->age = age;
    }

    const float priceCalculation() {
        if (age <= 10)
            return price + (20 / float(100)) * price;
        else if (age <= 35)
            return price + (10 / float(100)) * price;
        return price;
    }
};

class SoCvet : public SaksiskoCveke {
private:
    int flourishingFlowers;
public:
    SoCvet(const char *name, const int price, const char *family, const int flourishingFlowers)
            : SaksiskoCveke(name, price, family) {
        this->flourishingFlowers = flourishingFlowers;
    }

    const float priceCalculation() {
        return price + flourishingFlowers;
    }
};

void pecatiMaxCena(SaksiskoCveke **flowers, const int n, const SaksiskoCveke &c) {
    SaksiskoCveke *max = flowers[0];
    for (int i = 0; i < n; ++i) {
        if (*flowers[i] == c)
            if (max->getPrice() < flowers[i]->getPrice())
                max = flowers[i];
    }
    cout << max->getName() << " " << max->getFamily() << " " << max->priceCalculation() << endl;
}

int main() {
    char ime[20], familija[20];
    int tip, starost, broj, cena;
    int n;
    cin >> n;
    SaksiskoCveke **cvekinja;
    cvekinja = new SaksiskoCveke *[n];

    for (int i = 0; i < n; i++) {
        cin >> tip >> ime >> cena >> familija;
        if (tip == 1) {
            cin >> starost;
            cvekinja[i] = new BezCvet(ime, cena, familija, starost);
        } else {
            cin >> broj;
            cvekinja[i] = new SoCvet(ime, cena, familija, broj);
        }
    }

    BezCvet nov("opuntia", 90, "cactus", 10);
    pecatiMaxCena(cvekinja, n, nov);

    for (int i = 0; i < n; i++)
        delete cvekinja[i];
    delete[] cvekinja;

    return 0;
}
