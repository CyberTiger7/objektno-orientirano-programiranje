//
// Created by krstevkoki on 3/6/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac {
    //vasiot kod ovde
private:
    char name[20];
    char surname[20];
    char EMBG[14];
public:
    Potpisuvac() {

    }

    Potpisuvac(char *name, char *surname, char *EMBG) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        strcpy(this->EMBG, EMBG);
    }

    Potpisuvac(const Potpisuvac &signer) {
        strcpy(name, signer.name);
        strcpy(surname, signer.surname);
        strcpy(EMBG, signer.EMBG);
    }

    char const *get_EMBG() {
        return EMBG;
    }
};

class Dogovor {
    //vasiot kod ovde
private:
    int num_deals;
    char category[50];
    Potpisuvac signers[3];
public:
    Dogovor() {

    }

    Dogovor(int num_deals, char *category, Potpisuvac signer[3]) {
        this->num_deals = num_deals;
        strcpy(this->category, category);
        for (int i = 0; i < 3; ++i) {
            signers[i] = signer[i];
        }
    }

    bool proverka() {
        if ((strcmp(signers[0].get_EMBG(), signers[1].get_EMBG())) == 0)
            return true;
        else if ((strcmp(signers[0].get_EMBG(), signers[2].get_EMBG())) == 0)
            return true;
        else if ((strcmp(signers[1].get_EMBG(), signers[2].get_EMBG())) == 0)
            return true;
        else
            return false;
    }
};


int main() {
    char EMBG[14], name[20], surname[20], category[20];
    int broj, n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> EMBG >> name >> surname;
        Potpisuvac p1(name, surname, EMBG);
        cin >> EMBG >> name >> surname;
        Potpisuvac p2(name, surname, EMBG);
        cin >> EMBG >> name >> surname;
        Potpisuvac p3(name, surname, EMBG);
        cin >> broj >> category;
        Potpisuvac p[3];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        Dogovor d(broj, category, p);
        cout << "Dogovor " << i + 1 << ":" << endl;
        if (d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
