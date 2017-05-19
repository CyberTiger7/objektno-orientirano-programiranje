//
// Created by krstevkoki on 5/19/17.
//
#include <iostream>
#include <cstring>

using namespace std;

// vasiot kod za klasite ovde

class StockRecord {
private:
    char id[12];
    char company[50];
    double price;
    double newPrice;
    int num_stocks;
public:
    StockRecord() {
        price = 0;
        newPrice = 0;
        num_stocks = 0;
        strcpy(this->id, "");
        strcpy(this->company, "");
    }

    StockRecord(const char *id, const char *company, const double price, const int num_stocks) {
        this->price = price;
        this->num_stocks = num_stocks;
        strcpy(this->id, id);
        strcpy(this->company, company);
    }

    const void setNewPrice(const double price) {
        this->newPrice = price;
    }

    const double value() const { return num_stocks * newPrice; }

    const double profit() const { return num_stocks * (newPrice - price); }

    friend ostream &operator<<(ostream &out, const StockRecord &sr) {
        out << sr.company << " " << sr.num_stocks << " " << sr.price << " " << sr.newPrice
            << " " << sr.profit() << endl;
        return out;
    }

    ~StockRecord() {}
};

class Client {
private:
    char client[60];
    int id;
    StockRecord *companies;
    int num_companies;
public:
    Client(const char *client, const int id) {
        this->id = id;
        this->num_companies = 0;
        strcpy(this->client, client);
        this->companies = NULL;
    }

    Client(const Client &c) {
        this->id = c.id;
        this->num_companies = c.num_companies;
        strcpy(this->client, c.client);
        this->companies = new StockRecord[c.num_companies];
        for (int i = 0; i < c.num_companies; ++i) {
            this->companies[i] = c.companies[i];
        }
    }

    Client &operator=(const Client &c) {
        if (this != &c) {
            this->id = c.id;
            this->num_companies = c.num_companies;
            strcpy(this->client, c.client);
            delete[] this->companies;
            this->companies = new StockRecord[c.num_companies];
            for (int i = 0; i < c.num_companies; ++i) {
                this->companies[i] = c.companies[i];
            }
        }
        return *this;
    }

    Client &operator+=(const StockRecord &sr) {
        StockRecord *tmp = new StockRecord[num_companies + 1];
        for (int i = 0; i < num_companies; ++i) {
            tmp[i] = companies[i];
        }
        delete[] companies;
        companies = tmp;
        companies[num_companies++] = sr;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Client &c) {
        cout << c.id << " " << c.totalValue() << endl;
        for (int i = 0; i < c.num_companies; ++i) {
            cout << c.companies[i];
        }
        return out;
    }

    const double totalValue() const {
        double total = 0.00;
        for (int i = 0; i < num_companies; ++i) {
            total += companies[i].value();
        }
        return total;
    }

    ~Client() { delete[] companies; }
};

// ne menuvaj vo main-ot
int main() {
    int test;
    cin >> test;
    if (test == 1) {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    } else if (test == 2) {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    } else if (test == 3) {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag) {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;
}