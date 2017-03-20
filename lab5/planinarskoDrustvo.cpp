//
// Created by krstevkoki on 3/20/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class PlDrustvo {
private:
    char *name;
    int num_tours;
    int num_members;
public:
    PlDrustvo(char *name = "", int num_tours = 0, int num_members = 0) {
        this->num_tours = num_tours;
        this->num_members = num_members;
        this->name = new char[strlen(name + 1)];
        strcpy(this->name, name);
    }

    PlDrustvo(const PlDrustvo &pd) {
        this->num_tours = pd.num_tours;
        this->num_members = pd.num_members;
        this->name = new char[strlen(pd.name) + 1];
        strcpy(this->name, pd.name);
    }

    PlDrustvo &operator=(const PlDrustvo &pd) {
        if (this != &pd) {
            this->num_tours = pd.num_tours;
            this->num_members = pd.num_members;
            delete[] this->name;
            this->name = new char[strlen(pd.name) + 1];
            strcpy(this->name, pd.name);
        }
        return *this;
    }

    bool operator>(const PlDrustvo &pd) {
        if (this->num_members > pd.num_members)
            return true;
        else
            return false;
    }

    PlDrustvo operator+(const PlDrustvo &pd) {
        PlDrustvo novo;
        novo.num_members = this->num_members + pd.num_members;
        if (*this > pd) {
            novo.num_tours = this->num_tours;
            delete[] novo.name;
            novo.name = new char[strlen(this->name) + 1];
            strcpy(novo.name, this->name);
        } else {
            novo.num_tours = pd.num_tours;
            delete[] novo.name;
            novo.name = new char[strlen(pd.name) + 1];
            strcpy(novo.name, pd.name);
        }
        return novo;
    }

    friend ostream &operator<<(ostream &out, PlDrustvo &pd) {
        out << "Ime: " << pd.name << " Turi: " << pd.num_tours << " Clenovi: " << pd.num_members << endl;
        return out;
    }

    ~PlDrustvo() { delete[] name; }
};

void najmnoguClenovi(PlDrustvo *pd, int num_members) {
    PlDrustvo max = pd[0];
    for (int i = 0; i < num_members; ++i) {
        if (pd[i] > max) {
            max = pd[i];
        }
    }
    cout << "Najmnogu clenovi ima planinarskoto drustvo: " << max;
}

int main() {
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i = 0; i < 3; i++) {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin >> ime;
        cin >> brTuri;
        cin >> brClenovi;
        PlDrustvo p(ime, brTuri, brClenovi);
        drustva[i] = p;
    }

    pl = (drustva[0] + drustva[1]);
    cout << pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
