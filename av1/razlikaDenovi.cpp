//
// Created by krstevkoki on 2/20/17.
//
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct date {
    int day;
    int month;
    int year;
};

/*
 * 1 if d1 > d2
 * 0 if d1 == d2
 * -1 if d1 < d2
 */

int compare(date &d1, date &d2) {
    if (d1.year > d2.year)
        return 1;
    else if (d1.year < d2.year)
        return -1;
    else {
        if (d1.month > d2.month)
            return 1;
        else if (d1.month < d2.month)
            return -1;
        else {
            if (d1.day > d2.day)
                return 1;
            else if (d1.day < d2.day)
                return -1;
            else
                return 0;
        }
    }
}

int difference(date &d1, date &d2) {
    int days = abs(d1.day - d2.day);
    days = days + abs((d1.month - d2.month)) * 30;
    days = days + abs((d1.year - d2.year)) * 365;
    return days;
}

void read(date &dat) {
    cout << "Vnesete go denot: ";
    cin >> dat.day;
    cout << "Vnesete go mesecot: ";
    cin >> dat.month;
    cout << "Vnesete ja godinata: ";
    cin >> dat.year;
}

void print(date &dat) {
    cout << setw(2) << setfill('0') << dat.day << "." << setw(2) << setfill('0') << dat.month << "." << dat.year;
}

int main() {
    date d1, d2;
    read(d1);
    cout << endl;
    read(d2);
    int result = compare(d1, d2);
    cout << endl;
    if (result == 0)
        cout << "Datumite se ednakvi";
    else if (result == -1) {
        print(d1);
        cout << " e pomal od ";
        print(d2);
    } else {
        print(d1);
        cout << " e pogolem od ";
        print(d2);
    }
    int diff = difference(d1, d2);
    if (result == 0)
        cout << "\nNema razlika";
    else
        cout << "\nRazlikata pomegju datumite e: " << diff << " denovi";
    return 0;
}