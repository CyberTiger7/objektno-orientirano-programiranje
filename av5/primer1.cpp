//
// Created by krstevkoki on 3/15/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
private:
    char name[50];
    char stadium[100];
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

    void set_Name(const char *name) {
        strcpy(this->name, name);
    }

};

int main() {
    Ekipa *e3 = new Ekipa("Real Madrid", "Santiago Bernabeu", "Madrid");
    Ekipa *e4 = new Ekipa("Barcelona", "Kamp Nou", "Barcelona");

    cout << "Ekipite se: ";
    cout << e3->get_Name();
    cout << " - ";
    cout << e4->get_Name();

    cout << "\nSe igra na: ";
    cout << e3->get_Stadium();
    cout << " stadionot";

    cout << "\nVo: " << e3->get_City();

    //e3->get_Name()->set_Name("Barselona"); //GRESHKA
    e3->set_Name("Barselona");
    e4->set_Name("Real Madrid");

    cout << "\nPo promenata ekipite se: ";
    cout << e3->get_Name();
    cout << " - ";
    cout << e4->get_Name();

    delete e3;
    delete e4;

    return 0;
}