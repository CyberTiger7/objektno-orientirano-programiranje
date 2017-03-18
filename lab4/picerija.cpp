//
// Created by krstevkoki on 3/18/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Pica {
private:
    char name[15];
    int price;
    char *ingredients;
    int promotion;
public:
    Pica(char *name = "", int price = 0, char *ingredients = "", int promotion = 0) {
        strcpy(this->name, name);
        this->price = price;
        this->promotion = promotion;
        this->ingredients = new char[strlen(ingredients) + 1];
        strcpy(this->ingredients, ingredients);
    }

    Pica(const Pica &p) {
        strcpy(this->name, p.name);
        this->price = p.price;
        this->promotion = p.promotion;
        this->ingredients = new char[strlen(p.ingredients) + 1];
        strcpy(this->ingredients, p.ingredients);
    }

    Pica &operator=(Pica &p) {
        if (this != &p) {
            strcpy(this->name, p.name);
            this->price = p.price;
            this->promotion = p.promotion;
            delete[] this->ingredients;
            this->ingredients = new char[strlen(p.ingredients) + 1];
            strcpy(this->ingredients, p.ingredients);
        }
        return *this;
    }

    ~Pica() {
        delete[] ingredients;
    }

    const void pecati() {
        cout << name << " - " << ingredients << ", " << price;
    }

    bool istiSe(Pica p) {
        if (strcmp(this->ingredients, p.ingredients) == 0)
            return true;
        else
            return false;
    }

    const char *getIme() {
        return name;
    }

    const int getPromotion() {
        return promotion;
    }

    const int getPrice() {
        return price;
    }

    const char *getIngredients() {
        return ingredients;
    }

};

class Picerija {
private:
    char name[15];
    Pica *pizzas;
    int num_pizzas;
public:
    Picerija(char *name = "", Pica *pizzas = 0, int num_pizzas = 0) {
        strcpy(this->name, name);
        this->num_pizzas = num_pizzas;
        this->pizzas = new Pica[num_pizzas];
        for (int i = 0; i < num_pizzas; ++i) {
            this->pizzas[i] = pizzas[i];
        }
    }

    Picerija(const Picerija &p) {
        strcpy(this->name, p.name);
        this->num_pizzas = p.num_pizzas;
        this->pizzas = new Pica[p.num_pizzas];
        for (int i = 0; i < p.num_pizzas; ++i) {
            this->pizzas[i] = p.pizzas[i];
        }
    }

    Picerija &operator=(Picerija &p) {
        if (this != &p) {
            strcpy(this->name, p.name);
            this->num_pizzas = p.num_pizzas;
            delete[] this->pizzas;
            this->pizzas = new Pica[p.num_pizzas];
            for (int i = 0; i < p.num_pizzas; ++i) {
                this->pizzas[i] = p.pizzas[i];
            }
        }
        return *this;
    }

    ~Picerija() {
        delete[] pizzas;
    }

    Picerija &dodadi(Pica p) {
        Pica *temp = new Pica[num_pizzas + 1];
        for (int i = 0; i < num_pizzas; ++i) {
            temp[i] = pizzas[i];
        }
        delete[] pizzas;
        pizzas = temp;
        int flag = 1;
        for (int i = 0; i < num_pizzas; ++i) {
            if (pizzas[i].istiSe(p)) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            pizzas[num_pizzas++] = p;
        }
        return *this;
    }

    const void piciNaPromocija() {
        for (int i = 0; i < num_pizzas; ++i) {
            if (pizzas[i].getPromotion() > 0) {
                float promotion_price =
                        pizzas[i].getPrice() - (((float) pizzas[i].getPromotion() / 100) * pizzas[i].getPrice());
                cout << pizzas[i].getIme() << " - " << pizzas[i].getIngredients() << ", " << pizzas[i].getPrice()
                     << " " << promotion_price << endl;
            }
        }
    }

    void setIme(const char *name) {
        strcpy(this->name, name);
    }

    const char *getIme() {
        return name;
    }
};

int main() {
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2.dodadi(p);
    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();
    return 0;
}