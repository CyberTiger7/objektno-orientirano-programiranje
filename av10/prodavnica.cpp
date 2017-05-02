//
// Created by krstevkoki on 5/2/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class NegativeValueException : public exception {
private:
    char *errorName;
public:
    NegativeValueException(const char *errorName) : exception() {
        this->errorName = new char[strlen(errorName) + 1];
        strcpy(this->errorName, errorName);
    }

    NegativeValueException(const NegativeValueException &nve) {
        this->errorName = new char[strlen(nve.errorName) + 1];
        strcpy(this->errorName, nve.errorName);
    }

    NegativeValueException &operator=(const NegativeValueException &nve) {
        if (this != &nve) {
            delete[] this->errorName;
            this->errorName = new char[strlen(nve.errorName) + 1];
            strcpy(this->errorName, nve.errorName);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const NegativeValueException &nve) {
        out << nve.errorName;
        return out;
    }

    ~NegativeValueException() { delete[] errorName; }
};

class Discount {
protected:
    static float euro;
    static float dollar;
public:
    virtual const float discount_price() const = 0;

    virtual const float price() const = 0;

    virtual const void print_rule() const = 0;

    virtual ~Discount() {}
};

float Discount::euro = 61.7;
float Discount::dollar = 44.5;

class Product {
protected:
    char name[100];
    float price;
public:
    Product(const char *name, const float price) {
        strcpy(this->name, name);
        this->price = price;
    }

    const float getPrice() const {
        return price;
    }

    const void print() const {
        cout << "Product{ name = " << name << ", price = " << price << "}" << endl;
    }

    const void changePrice(const float price) {
        if (price < 0)
            throw NegativeValueException("Vnesena e negativna vrednost za cena!\n");
        this->price = price;
    }

    virtual ~Product() {}
};

class Cosmetics : public Product, public Discount {
private:
    int weight;
public:
    Cosmetics(const char *name, const float price, const int weight)
            : Product(name, price) {
        this->weight = weight;
    }

    const float discount_price() const {
        if ((getPrice() / Discount::dollar) > 20)
            return float((1 - 0.14) * getPrice());
        else if ((getPrice() / Discount::euro) > 5)
            return float((1 - 0.12) * getPrice());
        return getPrice();
    }

    const float price() const {
        return getPrice();
    }

    const void print_rule() const {
        cout << "Site kozmeticki proizvodi poskapi od 5 evra imaat popust od 12%, "
                "dodeka pak onie koi se poskapi od 20 dolari imaat popust 14%" << endl;
    }
};

class FoodProduct : public Product, public Discount {
private:
    float callories;
public:
    FoodProduct(const char *name, const float price, const float callories)
            : Product(name, price) {
        this->callories = callories;
    }

    const float discount_price() const {
        return getPrice();
    }

    const float price() const {
        return getPrice();
    }

    const void print_rule() const {
        cout << "Nema popust za proizvodite od tip na hrana" << endl;
    }
};

class Drinks : public Product, public Discount {
private:
    char brand[100];
    bool alcoholic;
public:
    Drinks(const char *name, const float price, const char *brand, const bool alcoholic)
            : Product(name, price) {
        strcpy(this->brand, brand);
        this->alcoholic = alcoholic;
    }

    const float discount_price() const {
        if (alcoholic && ((getPrice() / Discount::euro) > 20))
            return float((1 - 0.05) * getPrice());
        if (!alcoholic && (strcmp(this->brand, "Coca-Cola") == 0))
            return float((1 - 0.1) * getPrice());
        return getPrice();
    }

    const float price() const {
        return getPrice();
    }

    const void print_rule() const {
        cout << "Site alkoholni pijaloci poskapi od 20 evra imaat popust od 5%, "
                "dodeka pak nealkoholnite od brendot Coca-Cola imaat popust od 10% " << endl;
    }
};

float total_discount(Discount **d, int n) {
    float discount = 0;
    for (int i = 0; i < n; ++i) {
        discount += d[i]->discount_price();
    }
    return discount;
}

int main() {
    int n = 0;
    float newPrice;
    Discount **d = new Discount *[10];
    d[n++] = new FoodProduct("leb", 30, 10);
    d[n++] = new Drinks("viski", 1350, "Jack Daniel's", true);
    d[n++] = new FoodProduct("sirenje", 390, 105);
    d[n++] = new Drinks("votka", 850, "Finlandia", true);
    d[n++] = new Cosmetics("krema", 720, 100);
    d[n++] = new Drinks("sok", 50, "Coca-Cola", false);
    d[n++] = new Cosmetics("parfem", 3500, 50);

    for (int i = 0; i < n; ++i) {
        cout << "Prvicna cena: " << d[i]->price() << endl;
        cout << "So popust: " << d[i]->discount_price() << endl;
        d[i]->print_rule();
    }

    cout << "Vkupnata cena na site proizvodi e: " << total_discount(d, n) << endl;

    //se menuva cenata na site Kozmeticki proizvodi
    cout << "Promena na cenata na kozmetickite proizvodi " << endl;
    for (int i = 0; i < n; ++i) {
        Cosmetics *c = dynamic_cast<Cosmetics *>(d[i]);
        if (c != 0) {
            c->print();
            cin >> newPrice;
            try {
                c->changePrice(newPrice);
                cout << "Smeneta cena: " << c->price() << endl;
                cout << "So popust: " << c->discount_price() << endl;
            }
            catch (NegativeValueException e) {
                cout << e;
            }
        }
    }


    for (int i = 0; i < n; ++i)
        delete d[i];
    delete[] d;

    return 0;
}