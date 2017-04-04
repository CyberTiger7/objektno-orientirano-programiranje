//
// Created by krstevkoki on 4/4/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class DebitAccount {
private:
    char name[200];
    long acc_num;
    double balance;
public:
    DebitAccount(const char *name = "", const long acc_num = 0, const double balance = 0.0) {
        strcpy(this->name, name);
        this->acc_num = acc_num;
        this->balance = balance;
    }

    DebitAccount(const DebitAccount &dAcc) {
        strcpy(this->name, dAcc.name);
        this->acc_num = dAcc.acc_num;
        this->balance = dAcc.balance;
    }

    DebitAccount &operator=(const DebitAccount &dAcc) {
        if (this != &dAcc) {
            strcpy(this->name, dAcc.name);
            this->acc_num = dAcc.acc_num;
            this->balance = dAcc.balance;
        }
        return *this;
    }

    const void showInfo() {
        cout << name << endl
             << "\t Bank No: " << acc_num << endl
             << "\t Balance: " << balance << endl;
    }

    const void deposit(double amount) {
        if (amount >= 0) {
            this->balance += amount;
        } else
            cout << "You cannot deposit negative amount of money to your balance !!!" << endl;
    }

    const void withdraw(double amount) {
        if (amount < 0) {
            cout << "You cannot withdraw negative amount of money from you balance !!!" << endl;
            return;
        }
        if (amount <= balance) {
            this->balance -= amount;
        } else
            cout << "Insufficient money on your debit card !!!" << endl;
    }

    const double getBalance() {
        return balance;
    }

    ~DebitAccount() {}
};

class CreditAccount : public DebitAccount {
private:
    double limit;
    double interest;
    double minus;
public:
    CreditAccount(const char *name = "", const long acc_num = 0,
                  const double balance = 0, const double limit = 1000,
                  const double interest = 0.05, const double minus = 0) : DebitAccount(name, acc_num, balance) {
        this->limit = limit;
        this->interest = interest;
        this->minus = minus;
    }

    void withdraw(double amount) {
        double balance = getBalance();
        if (amount <= balance) {
            DebitAccount::withdraw(amount);
        } else if (amount <= balance + limit - minus) {
            double advance = amount - balance;
            this->minus += advance * (1.0 + interest);
            cout << "Minus: " << advance << "\n"
                 << "Minus with interest: " << advance * interest << endl;
            deposit(advance);
            DebitAccount::withdraw(amount);
        } else {
            cout << "The bank is not giving you that much money..." << endl;
            this->showInfo();
        }
    }

    void showInfo() {
        DebitAccount::showInfo();
        cout << "\t Limit: " << this->limit << "\n"
             << "\t In minus: " << this->minus << "\n"
             << "\t Interest: " << this->interest << "%\n";
    }

};

int main() {
    DebitAccount d("Pero Perovski", 6, 100000);
    CreditAccount ca("Mitko Mitkovski", 10, 5000, 1000);
    d.showInfo();
    d.deposit(50000);
    d.withdraw(600000);
    d.showInfo();
    ca.showInfo();
    ca.deposit(500);
    ca.showInfo();
    ca.withdraw(6200);
    ca.showInfo();
    return 0;
}
