//
// Created by krstevkoki on 2/23/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Person {
private:
    char name[100];
    int sallary;
    char position[20];
public:
    Person() {
        // Constructor
    }

    ~Person() {
        // Destructor
    }

    // set functions
    void setName(char const *n) {
        strcpy(name, n);
    }

    void setSalary(int const s) {
        sallary = s;
    }

    void setPosition(char const *p) {
        strcpy(position, p);
    }

    // get functions
    char const *getName() {
        return name;
    }

    int const getSallary() {
        return sallary;
    }

    char const *getPosition() {
        return position;
    }
} employees[100];

void read(int &n) {
    cout<<"Vnesete podatoci za vrabotenite (ime, plata, pozicija): \n";
    char name[100];
    char position[20];
    int salary;
    for (int i = 0; i < n; ++i) {
        cin >> name >> salary >> position;
        employees[i].setName(name);
        employees[i].setSalary(salary);
        employees[i].setPosition(position);
    }

}

void sort(int &n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (employees[j].getSallary() < employees[j + 1].getSallary()) {
                Person temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void print(int &n) {
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ". " << employees[i].getName() << " " << employees[i].getSallary() << " "
             << employees[i].getPosition()
             << endl;
    }
}

int main() {
    int n;

    cout << "Vnesete broj na vraboteni: ";
    cin >> n;

    read(n);
    sort(n);
    print(n);

    return 0;
}