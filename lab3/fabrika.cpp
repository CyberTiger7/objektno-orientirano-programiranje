//
// Created by krstevkoki on 3/7/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Rabotnik {
private:
    char name[30];
    char surname[30];
    int salary;
public:
    Rabotnik() {

    }

    Rabotnik(char *name, char *surname, int salary) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->salary = salary;
    }

    int const get_Salary() {
        return salary;
    }

    void const print() {
        cout << name << " " << surname << " " << salary << endl;
    }
};

class Fabrika {
private:
    Rabotnik workers[100];
    int num_employees;
public:
    Fabrika() {

    }

    Fabrika(Rabotnik worker[100], int num_employees) {
        for (int i = 0; i < num_employees; ++i) {
            workers[i] = worker[i];
        }
        this->num_employees = num_employees;
    }

    void const print_Employees() {
        cout << "Site vraboteni:" << endl;
        for (int i = 0; i < num_employees; ++i) {
            workers[i].print();
        }
    }

    void const print_by_salary(int salary) {
        cout << "Vraboteni so plata povisoka od "<< salary << " :" << endl;
        for (int i = 0; i < num_employees; ++i) {
            if(workers[i].get_Salary() > salary)
                workers[i].print();
        }
    }
};

int main() {
    int n;
    cin >> n;
    Rabotnik workers[100];
    for (int i = 0; i < n; ++i) {
        char name[30];
        cin >> name;
        char surname[30];
        cin >> surname;
        int salary;
        cin >> salary;
        workers[i] = Rabotnik(name, surname, salary);
    }
    Fabrika factory(workers, n);
    factory.print_Employees();
    int salary;
    cin >> salary;
    factory.print_by_salary(salary);
    return 0;
}