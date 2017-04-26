//
// Created by krstevkoki on 4/26/17.
//
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Product {
protected:
    char name[100];
    double price;
public:
    Product(const char *name, const double price) {
        strcpy(this->name, name);
        this->price = price;
    }

    virtual const double getPrice() const {
        return price;
    }

    virtual ~Product() {}
};

class Discount {
private:

public:
    virtual const double calculatePrice() const = 0;

    virtual const double calculateDiscountPrice() const = 0;

    virtual ~Discount() {}
};

class FoodProduct : public Product, public Discount {
private:
    float num_callories;
public:
    FoodProduct(const char *name, const double price, const float num_callories)
            : Product(name, price) {
        this->num_callories = num_callories;
    }

    /* се препокриваат функциите од апстрактната класа */
    const double calculateDiscountPrice() const {
        /* попустот е 20% */
        return calculatePrice() + (20 / double(100)) * calculatePrice();
    }

    /* и двете класи Product и Discount имаат функција getPrice, која се
    препокрива во изведената. Оваа ја користи getPrice од Product */
    const double calculatePrice() const {
        return Product::getPrice();
    }
};

class DigitalProduct : public Product, public Discount {
private:
    float size;
public:
    DigitalProduct(const char *name, const double price, const float size)
            : Product(name, price) {
        this->size = size;
    }

    /* се препокриваат функциите од апстрактната класа */
    const double calculateDiscountPrice() const {
        /* попустот е 10% */
        return calculatePrice() + (10 / double(100)) * calculatePrice();
    }

    /* и двете класи Product и Discount имаат функција getPrice, која се
    препокрива во изведената. Оваа ја користи getPrice од Product */
    const double calculatePrice() const {
        return Product::getPrice();
    }
};

double total_discount(Discount **d, int n) {
    double price = 0.0;
    for (int i = 0; i < n; ++i) {
        price += d[i]->calculatePrice();
    }
    double discount = 0.0;
    for (int i = 0; i < n; ++i) {
        discount += d[i]->calculateDiscountPrice();
    }
    return abs(price - discount);
}

int main() {
    Discount **d = new Discount *[3];
    d[0] = new FoodProduct("Cheese", 450, 1200);
    d[1] = new FoodProduct("Wine", 780, 250);
    d[2] = new DigitalProduct("WOW", 380, 400);
    cout << "Difference: " << total_discount(d, 3) << endl;
    for (int i = 0; i < 3; ++i)
        delete d[i];
    delete[] d;
    return 0;
}