//
// Created by krstevkoki on 3/29/17.
//

#include <iostream>
#include <cstring>

using namespace std;

struct Tanc {
    char dance_name[15];
    char country_of_origin[15];
};

struct Tancer {
    char name[20];
    char surname[20];
    Tanc dances[5];
};

void tancuvanje(Tancer *t, int n, char *country) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (strcmp(t[i].dances[j].country_of_origin, country) == 0) {
                cout << t[i].name << " ";
                cout << t[i].surname << ", ";
                cout << t[i].dances[j].dance_name << endl;
                break;
            }
        }
    }
}

int main() {
    int n;
    char country[11];
    Tancer dancers[5];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> dancers[i].name;
        cin >> dancers[i].surname;
        for (int j = 0; j < 3; j++) {
            cin >> dancers[i].dances[j].dance_name;
            cin >> dancers[i].dances[j].country_of_origin;
        }
    }
    cin >> country;
    tancuvanje(dancers, n, country);
    return 0;
}