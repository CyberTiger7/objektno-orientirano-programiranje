//
// Created by krstevkoki on 3/17/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
private:
    char name[50];
    char stadium[50];
    char city[50];
public:
    Ekipa() {}

    Ekipa(char *name, char *stadium, char *city) {
        strcpy(this->name, name);
        strcpy(this->stadium, stadium);
        strcpy(this->city, city);
    }

    Ekipa(const Ekipa &team) {
        strcpy(name, team.name);
        strcpy(stadium, team.stadium);
        strcpy(city, team.city);
    }

    ~Ekipa() {}

    const char *get_Name() {
        return name;
    }

    const char *get_Stadium() {
        return stadium;
    }

    const char *get_City() {
        return city;
    }

    void set_Name(const char *ime) {
        strcpy(this->name, name);
    }
};

int main() {
    int n;
    cout << "Br. na ekipi: ";
    cin >> n;

    Ekipa *e1 = new Ekipa[n];

    char name[50], stadium[50], city[50];

    for (int i = 0; i < n; ++i) {
        cout << (i + 1) << " ekipa" << endl;

        cout << "Ime: ";
        cin >> name;

        cout << "Stadion: ";
        cin >> stadium;

        cout << "Grad: ";
        cin >> city;

        e1[i] = Ekipa(name, stadium, city);
    }

    for (int i = 0; i < n; ++i) {
        cout << e1[i].get_Name() << "\t";
        cout << e1[i].get_Stadium() << "\t";
        cout << e1[i].get_City() << endl;
    }

    delete [] e1;
    return 0;
}