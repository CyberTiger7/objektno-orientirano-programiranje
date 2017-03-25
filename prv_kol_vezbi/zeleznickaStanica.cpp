//
// Created by krstevkoki on 3/25/17.
//

#include <iostream>
#include <cstring>

using namespace std;

struct Voz {
    char relacija[50];
    float km;
    int num_passengers;
};

struct ZeleznickaStanica {
    char city[20];
    Voz trains[30];
    int num_trains;
};

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
    int index = 0, index_train = 0;
    for (int i = 0; i < n; ++i) {
        float min = zs[i].trains[0].km;
        if (strcmp(zs[i].city, grad) == 0) {
            for (int j = 0; j < zs[i].num_trains; ++j) {
                if (min >= zs[i].trains[j].km) {
                    min = zs[i].trains[j].km;
                    index = i;
                    index_train = j;
                }
            }
        }
    }
        cout << "Najkratka relacija: " << zs[index].trains[index_train].relacija << " ("
             << zs[index].trains[index_train].km
             << " km)";
}

int main() {

    int n;
    cin >> n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[n];
    for (int i = 0; i < n; i++) {
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin >> zStanica[i].city;
        cin >> zStanica[i].num_trains;
        for (int j = 0; j < zStanica[i].num_trains; ++j) {
            cin >> zStanica[i].trains[j].relacija;
            cin >> zStanica[i].trains[j].km;
            cin >> zStanica[i].trains[j].num_passengers;
        }
    }

    char grad[20];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);
    return 0;
}
