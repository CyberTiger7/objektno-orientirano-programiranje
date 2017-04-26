//
// Created by krstevkoki on 4/26/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Vleznica {
protected:
    char name[50];
    float price;
public:
    Vleznica(const char *name, const float price) {
        strcpy(this->name, name);
        this->price = price;
    }

    virtual const float calculatePrice() const = 0;

    const char *getName() {
        return name;
    }

    virtual ~Vleznica() {}
};

class VleznicaSedenje : public Vleznica {
private:
    int block;
    int row;
public:
    VleznicaSedenje(const char *name, const float price, const int block, const int row)
            : Vleznica(name, price) {
        this->block = block;
        this->row = row;
    }

    const float calculatePrice() const {
        if (row < 8)
            return price + (40 / float(100)) * price;
        else if (row >= 8 && row <= 15)
            return price + (20 / float(100)) * price;
        return price;
    }
};

class VleznicaStoenje : public Vleznica {
private:
    char stand;
public:
    VleznicaStoenje(const char *name, const float price, const char stand)
            : Vleznica(name, price) {
        this->stand = stand;
    }

    const float calculatePrice() const {
        if (stand == 'S')
            return price + (30 / float(100)) * price;
        return price;
    }
};

void najmalaCena(Vleznica **vleznici, int n) {
    Vleznica *min = vleznici[0];
    for (int i = 0; i < n; ++i) {
        if (min->calculatePrice() > vleznici[i]->calculatePrice())
            min = vleznici[i];
    }
    cout << min->getName() << endl << min->calculatePrice() << endl;
}

int main() {
    int n;
    cin >> n;
    Vleznica **vleznici = new Vleznica *[n];
    for (int i = 0; i < n; ++i) {
        char ime[30];
        float osnovnaCena;
        cin >> ime >> osnovnaCena;
        if (i % 2) {
            int blok, red;
            cin >> blok >> red;
            vleznici[i] = new VleznicaSedenje(ime, osnovnaCena, blok, red);
        } else {
            char tribina;
            cin >> tribina;
            vleznici[i] = new VleznicaStoenje(ime, osnovnaCena, tribina);
        }
    }

    najmalaCena(vleznici, n);

    for (int i = 0; i < n; ++i) {
        delete vleznici[i];
    }
    delete[] vleznici;
    return 0;
}