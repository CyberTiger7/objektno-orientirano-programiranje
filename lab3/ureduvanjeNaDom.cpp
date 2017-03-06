//
// Created by krstevkoki on 3/6/17.
//
#include <iostream>
#include <cstring>

using namespace std;

//vasiot kod ovde
class Masa {
private:
    int length;
    int width;
public:
    Masa() {

    }

    Masa(int length, int width) {
        this->length = length;
        this->width = width;
    }

    void pecati() {
        cout << " " << "Masa: " << width << " " << length << " " << endl;
    }
};

class Soba {
private:
    Masa table;
    int length;
    int width;
public:
    Soba() {

    }

    Soba(Masa table, int length, int width) {
        this->table = table;
        this->length = length;
        this->width = width;
    }

    void pecati() {
        cout << " " << "Soba: " << width << " " << length;
        table.pecati();
    }
};

class Kukja {
private:
    Soba room;
    char address[50];
public:
    Kukja() {

    }

    Kukja(Soba room, char *address) {
        this->room = room;
        strcpy(this->address, address);
    }

    ~Kukja() {

    }

    void pecati() {
        cout << "Adresa: " << address;
        room.pecati();
    }
};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int masaSirina, masaDolzina;
        cin >> masaSirina;
        cin >> masaDolzina;
        Masa m(masaDolzina, masaSirina);
        int sobaSirina, sobaDolzina;
        cin >> sobaSirina;
        cin >> sobaDolzina;
        Soba s(m, sobaDolzina, sobaSirina);
        char adresa[30];
        cin >> adresa;
        Kukja k(s, adresa);
        k.pecati();
    }
    return 0;
}