//
// Created by krstevkoki on 5/2/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Kartichka {
protected:
    char id[16];
    double balance;
public:
    Kartichka(const char *id, const double balance) {
        strcpy(this->id, id);
        this->balance = balance;
    }

    virtual const void uplati(double amount) {
        this->balance += amount;
    }

    virtual const void prikaziSaldo() const {
        cout << id << ": " << balance << endl;
    }

    virtual const double isplati(double amount) = 0;

    virtual ~Kartichka() {}
};


class Maestro : public Kartichka {
private:
    static const double discount; //static clen na klasa
    char password[10];
public:
    Maestro(const char *password, const char *id, const double balance)
            : Kartichka(id, balance) {
        strcpy(this->password, password);
    }

    static const double getDiscount() { //static funkcija koja raboti so static clen
        return Maestro::discount;
    }

    const double isplati(double amount) {
        // non-static funkcii moze da gi koristat static podatocnite elementi
        amount = amount * (1 - discount);
        if (amount <= balance) {
            balance -= amount;
            return amount;
        } else
            return 0;
    }
};

const double Maestro::discount = 0.05; // inicijaliziranje na static clen

class Master : public Kartichka {
private:
    double limit;
    static const double discount1; // fiksen popust
    static double discount2; // popust koj sto moze da se promeni
public:
    Master(const double limit, const char *id, const double balance)
            : Kartichka(id, balance) {
        this->limit = limit;
    }

    static const double getDiscount1() {
        return Master::discount1;
    }

    static const double getDiscount2() {
        return Master::discount2;
    }

    static const void setDiscount2(const double discount2) {
        Master::discount2 = discount2;
        /* ne smeeme da go napravime ova:
        static const void setPopust1 (const double  popust1) const {
                Master::popust1 = popust1;
        }
        poradi toa sto stanuva zbor za konstanta
        */
    }

    const double isplati(double amount) {
        if (limit < 6000) {
            amount = amount * (1 - discount1);
            if (amount <= balance + limit) {
                balance -= amount;
                return amount;
            }
        } else {
            amount = amount * (1 - discount2);
            if (amount <= balance + limit) {
                balance -= amount;
                return amount;
            }
        }
        return 0;
    }
};

const double Master::discount1 = 0.03;
double Master::discount2 = 0.1;

class Kasa {
private:
    double sumaVoKasa;
    double sumaOdKartichka;
    int day;
    int month;
    int year;
public:
    Kasa(const double sumaVoKasa, const int day, const int month, const int year) {
        this->sumaVoKasa = sumaVoKasa;
        this->sumaOdKartichka = 0.00;
        this->day = day;
        this->month = month;
        this->year = year;
    }

    const void kasaPrimi(double bill) {
        this->sumaVoKasa += bill;
    }

    const void kasaPrimi(double bill, Kartichka &k) {
        this->sumaOdKartichka += k.isplati(bill);
    }

    const void prikaziKasa() const {
        cout << "Den: " << day << endl;
        cout << "Mesec: " << month << endl;
        cout << "Godina: " << year << endl;
        cout << "Prihod-karticki: " << sumaOdKartichka << endl;
        cout << "Prihod-kesh: " << sumaVoKasa << endl;
        cout << "Vkupno prihod: " << vratiPrihod() << endl;
        cout << endl;
    }

    const double vratiPrihod() const {
        return sumaOdKartichka + sumaVoKasa;
    }
};

int main() {
    Kasa deneshna(10000, 22, 4, 2014);
    Kartichka *k;
    deneshna.prikaziKasa();

    cout << "Primam vo gotovo!" << endl;
    deneshna.kasaPrimi(5000);
    deneshna.prikaziKasa();

    k = new Master(10000.00, "1234567890123456", 54000.00);
    cout << "Primam so kartichka!" << endl;
    deneshna.kasaPrimi(10000.00, *k);
    deneshna.prikaziKasa();

    k = new Maestro("lozinka", "1234567890123456", 54000.00);
    cout << "Primam so kartichka!" << endl;
    deneshna.kasaPrimi(10000, *k);
    deneshna.prikaziKasa();

    Master::setDiscount2(0.07);
    k = new Master(10000.00, "4567891234567890", 3000);
    cout << "Primam so kartichka!" << endl;
    deneshna.kasaPrimi(10000, *k);
    deneshna.prikaziKasa();

    delete k;
    return 0;
}