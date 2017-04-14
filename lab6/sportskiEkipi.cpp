//
// Created by krstevkoki on 4/14/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
protected:
    char name[15];
    int wins;
    int losses;
public:
    Ekipa(const char *name = "", int wins = 0, int losses = 0) {
        this->wins = wins;
        this->losses = losses;
        strcpy(this->name, name);
    }

    Ekipa(const Ekipa &t) {
        this->wins = t.wins;
        this->losses = t.losses;
        strcpy(this->name, t.name);
    }

    void pecati() {
        cout << "Ime: " << name << " Pobedi: " << wins << " Porazi: " << losses;
    }
};

class FudbalskaEkipa : public Ekipa {
private:
    int redCards;
    int yellowCards;
    int draws;
public:
    FudbalskaEkipa(const char *name, int wins, int losses, int redCards, int yellowCards, int draws)
            : Ekipa(name, wins, losses) {
        this->redCards = redCards;
        this->yellowCards = yellowCards;
        this->draws = draws;
    }

    void pecati() {
        Ekipa::pecati();
        int points = (3 * wins) + (1 * draws);
        cout << " Nereseni: " << draws << " Poeni: " << points;
    }
};

int main() {
    char ime[15];
    int pob, por, ck, zk, ner;
    cin >> ime >> pob >> por >> ck >> zk >> ner;
    FudbalskaEkipa f1(ime, pob, por, ck, zk, ner);
    f1.pecati();
    return 0;
}