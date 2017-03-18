//
// Created by krstevkoki on 3/17/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class ParkingPlac {
private:
    char address[20];
    char *ID;
    int price;
    int earning;
public:
    ParkingPlac(char *address = "", char *ID = "", int price = 0, int earning = 0) {
        strcpy(this->address, address);
        this->price = price;
        this->earning = earning;
        this->ID = new char[strlen(ID) + 1];
        strcpy(this->ID, ID);
    }

    ParkingPlac(const ParkingPlac &pp) {
        strcpy(this->address, pp.address);
        this->price = pp.price;
        this->earning = pp.earning;
        this->ID = new char[strlen(pp.ID) + 1];
        strcpy(this->ID, pp.ID);
    }

    ParkingPlac &operator=(ParkingPlac &pp) {
        if (this != &pp) {
            strcpy(this->address, pp.address);
            this->price = pp.price;
            this->earning = pp.earning;
            delete[] this->ID;
            this->ID = new char[strlen(pp.ID) + 1];
            strcpy(this->ID, pp.ID);
        }
        return *this;
    }

    ~ParkingPlac() {
        delete[] ID;
    }

    const char *getId() {
        return ID;
    }

    const void pecati() {
        if (earning != 0) {
            cout << ID << " " << address << " - " << earning << " denari" << endl;
        } else
            cout << ID << " " << address << endl;
    }

    void platiCasovi(int hours) {
        earning = earning + (hours * price);
    }

    bool daliIstaAdresa(ParkingPlac p) {
        if (strcmp(this->address, p.address) == 0)
            return true;
        else
            return false;
    }
};

int main() {
    ParkingPlac p[100];
    int n, m;
    char adresa[50], id[50];
    int brojcasovi, cenacas;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin.get();
        cin.getline(adresa, 50);
        cin >> id >> cenacas;

        ParkingPlac edna(adresa, id, cenacas);

        //povik na operatorot =
        p[i] = edna;
    }

    //plakjanje
    cin >> m;
    for (int i = 0; i < m; i++) {

        cin >> id >> brojcasovi;

        int findId = false;
        for (int j = 0; j < n; j++) {
            if (strcmp(p[j].getId(), id) == 0) {
                p[j].platiCasovi(brojcasovi);
                findId = true;
            }
        }
        if (!findId)
            cout << "Ne e platen parking. Greshen ID." << endl;
    }

    cout << "=========" << endl;
    ParkingPlac pCentar("Cvetan Dimov", "C10", 80);
    for (int i = 0; i < n; i++)
        if (p[i].daliIstaAdresa(pCentar))
            p[i].pecati();
    return 0;
}