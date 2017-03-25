//
// Created by krstevkoki on 3/25/17.
//
#include <iostream>
#include <cstring>

using namespace std;
// vashiot kod ovde

class IceCream {
private:
    char *name;
    char ingredients[100];
    float price;
    int discount;
public:
    IceCream(char *name = "", char *ingredients = "", float price = 0) {
        strcpy(this->ingredients, ingredients);
        this->price = price;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->discount = 0;
    }

    IceCream(const IceCream &ic) {
        this->price = ic.price;
        this->discount = ic.discount;
        strcpy(this->ingredients, ic.ingredients);
        this->name = new char[strlen(ic.name) + 1];
        strcpy(this->name, ic.name);
    }

    IceCream &operator=(const IceCream &ic) {
        if (this != &ic) {
            this->price = ic.price;
            this->discount = ic.discount;
            strcpy(this->ingredients, ic.ingredients);
            delete[] this->name;
            this->name = new char[strlen(ic.name) + 1];
            strcpy(this->name, ic.name);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, IceCream &ic) {
        if (ic.discount == 0)
            out << ic.name << ": " << ic.ingredients << " " << ic.price << " ";
        else
            out << ic.name << ": " << ic.ingredients << " " << ic.price << " "
                << "(" << (ic.price - ((float(ic.discount) / 100) * ic.price)) << ")";
        return out;
    }

    IceCream &operator++() {
        this->discount += 5;
        return *this;
    }

    IceCream &operator+(char *name) {
        char *temp = new char[strlen(this->name) + strlen(name) + 3];
        strncpy(temp, this->name, strlen(this->name));
        temp[strlen(this->name)] = ' ';
        temp[strlen(this->name) + 1] = '+';
        temp[strlen(this->name) + 2] = ' ';
        strcat(temp, name);
        delete[] this->name;
        this->name = temp;
        this->price += 10;
        return *this;
    }

    ~IceCream() { delete[] name; }

    void setDiscount(const int discount) {
        if (discount >= 0 || discount <= 100) {
            this->discount = discount;
        }
    }

    void setName(char *name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
};

class IceCreamShop {
private:
    char name[50];
    IceCream *ic;
    int num_icecreams;
public:
    IceCreamShop(char *name) {
        strcpy(this->name, name);
        ic = NULL;
        num_icecreams = 0;
    }

    IceCreamShop(const IceCreamShop &ics) {
        strcpy(this->name, ics.name);
        this->num_icecreams = ics.num_icecreams;
        this->ic = new IceCream[ics.num_icecreams];
        for (int i = 0; i < ics.num_icecreams; ++i) {
            this->ic[i] = ics.ic[i];
        }
    }

    IceCreamShop &operator=(const IceCreamShop &ics) {
        if (this != &ics) {
            this->num_icecreams = ics.num_icecreams;
            strcpy(this->name, ics.name);
            delete[] ic;
            this->ic = new IceCream[ics.num_icecreams];
            for (int i = 0; i < ics.num_icecreams; ++i) {
                this->ic[i] = ics.ic[i];
            }
        }
        return *this;
    }

    ~IceCreamShop() { delete[] ic; }

    friend ostream &operator<<(ostream &out, IceCreamShop &ics) {
        out << ics.name << endl;
        for (int i = 0; i < ics.num_icecreams; ++i) {
            cout << ics.ic[i] << endl;
        }
        return out;
    }

    IceCreamShop &operator+=(const IceCream &ic) {
        IceCream *temp = new IceCream[num_icecreams + 1];
        for (int i = 0; i < num_icecreams; ++i) {
            temp[i] = this->ic[i];
        }
        delete[] this->ic;
        this->ic = temp;
        this->ic[num_icecreams++] = ic;
        return *this;
    }
};

// zabraneto e menuvanje na main funkcijata, osven dodavanje na kodot za spravuvanje so iskluchokot na soodvetno mesto

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}