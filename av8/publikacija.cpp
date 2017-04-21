//
// Created by krstevkoki on 4/21/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Publikacija {
private:
    char name[100];
protected:
    int pub_year;

    const char *getName() {
        return name;
    }

public:
    Publikacija(const char *name, const int pub_year) {
        strcpy(this->name, name);
        this->pub_year = pub_year;
    }

    const int getPubYear() {
        return pub_year;
    }

    const void print() {
        cout << "Publikacija: " << name << " - " << pub_year << endl;
    }
};

class Kniga : public Publikacija { // public изведување
private:
    int num_pages;
public:
    Kniga(const char *name, const int pub_year, const int num_pages)
            : Publikacija(name, pub_year) {
        this->num_pages = num_pages;
    }

    const void printPubYear() {
        cout << pub_year << endl;   // пристап до protected променливата pub_year
    }

    const void printBookName() {
        cout << getName() << endl; // пристап до getName(), name не може да се пристапи затоа што е private
    }

    const void printNumPages() {
        cout << num_pages << endl;
    }
};

class Vesnik : protected Publikacija { // protected изведување
private:
    int number;
public:
    Vesnik(const char *name, const int pub_year, const int number)
            : Publikacija(name, pub_year) {
        this->number = number;
    }

    const void printNewspaperYear() {
        cout << getPubYear() << endl; // пристап до public getPubYear(), која во оваа класа има protected пристап
    }

    const void printNewspaperName() {
        cout << getName() << endl; // пристап до getName(), name не може да се пристапи затоа што е private
    }

    const void printNumber() {
        cout << number << endl;
    }
};

// private изведување
class DnevenVesnik : private Vesnik {
private:
    int day;
    int month;
public:
    DnevenVesnik(const char *name, const int day, const int month, const int pub_year, const int number)
            : Vesnik(name, pub_year, number) {
        this->day = day;
        this->month = month;
    }

    using Vesnik::print; // функцијата print од Publikacija станува public за DnevenVesnik
    using Vesnik::printNumber; // функцијата printNumber од Vesnik станува public за DnevenVesnik
};

int main() {
    Publikacija p("Tabernakul", 1992);
    p.print(); // public - функција

    Kniga *k = new Kniga("ProsvetnoDelo", 1900, 123);
    k->print(); // print e public во Kniga
    cout << "\nNaziv: ";
    k->printBookName(); // public - функција
    cout << "Godina: ";
    k->printPubYear(); // public - функција
    cout << "Br. strani: ";
    k->printNumPages(); // public - функција
    // cout << "\nNaziv: " << k->getName() << endl; грешка! protected - функција

    Vesnik *s = new Vesnik("Tea", 2013, 30);
    // s->print(); грешка! protected - функција
    cout << "\nNaziv: ";
    s->printNewspaperName(); // public - функција
    cout << "Godina: ";
    // cout << s->getPubYear() << endl; грешка! protected - функција
    s->printNewspaperYear(); // public - функција
    cout << "Broj: ";
    s->printNumber(); // public - функција

    DnevenVesnik d("Vest", 2, 3, 2014, 25);
    cout << endl;
    d.print(); //public-функција
    /*cout << "Naziv: ";
    d.printNewspaperName(); грешка! private - функцијата*/
    // cout << "Naziv: " << d.getName(); грешка! private – функција

    delete k;
    delete s;

    return 0;
}