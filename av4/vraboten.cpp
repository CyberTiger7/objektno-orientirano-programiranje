//
// Created by krstevkoki on 3/13/17.
//

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

class Datum {
private:
    int day;
    int month;
    int year;
public:
    Datum(int day = 0, int month = 0, int year = 0) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Datum(const Datum &date) {
        day = date.day;
        month = date.month;
        year = date.year;
    }

    ~Datum() {

    }

    const int get_Day() {
        return day;
    }

    const int get_Month() {
        return month;
    }

    const int get_Year() {
        return year;
    }
};

class Vraboten {
private:
    char name[20];
    int salary;
    Datum date;
public:
    Vraboten() {

    }

    Vraboten(char *name, int salary, Datum date) {
        strcpy(this->name, name);
        this->salary = salary;
        this->date = date;
    }

    Vraboten(const Vraboten &employee) {
        strcpy(name, employee.name);
        salary = employee.salary;
        date = employee.date;
    }

    ~Vraboten() {

    }

    const int get_Salary() {
        return salary;
    }

    const Datum get_Date() {
        return date;
    }

    void print() {
        cout << "Ime: " << name << endl;
        cout << "Plata: " << salary << endl;
        cout << "Datum na ragjanje: " << setw(2) << setfill('0') << date.get_Day() << "." << setw(2) << setfill('0')
             << date.get_Month() << "."
             << date.get_Year() << endl;
    }
};

// 0 (d1 = d2), 1 (d1 < d2), -1 (d1 > d2)
int sporedba(Datum d1, Datum d2) {
    if (d1.get_Year() > d2.get_Year())
        return 1;
    else if (d1.get_Year() < d2.get_Year())
        return -1;
    else {
        if (d1.get_Month() > d1.get_Month())
            return 1;
        else if (d1.get_Month() < d2.get_Month())
            return -1;
        else {
            if (d1.get_Day() > d2.get_Day())
                return 1;
            else if (d1.get_Day() < d2.get_Day())
                return -1;
            else
                return 0;
        }
    }
}

Vraboten najmlad(Vraboten *v, int length) {
    Datum min(v[0].get_Date());
    int index = 0;
    for (int i = 1; i < length; ++i) {
        if (sporedba(v[i].get_Date(), min) == 1) {
            min = v[i].get_Date();
            index = i;
        }
    }
    return v[index];
}

Vraboten najgolemPlata(Vraboten *v, int length) {
    int max = v[0].get_Salary();
    int index = 0;
    for (int i = 1; i < length; ++i) {
        if (v[i].get_Salary() > max) {
            max = v[i].get_Salary();
            index = i;
        }

    }
    return v[index];
}

int main() {
    Datum d1(1, 1, 1980);
    Datum d2(1, 2, 1983);
    Datum d3(11, 12, 1984);

    Vraboten v[3];
    Vraboten v1("Marjan", 40000, d1);
    Vraboten v2("Stefan", 30000, d2);
    Vraboten v3("Marko", 20000, d3);
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;

    cout << "Najmlad vraboten: " << endl;
    najmlad(v, 3).print();

    cout << "Vraboten so najgolema plata: " << endl;
    najgolemPlata(v, 3).print();

    return 0;
}