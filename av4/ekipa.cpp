//
// Created by krstevkoki on 3/13/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
private:
    char name[50];
    char city[100];
    int year;
public:
    Ekipa(char *name = "", char *city = "", int year = 0) {
        strcpy(this->name, name);
        strcpy(this->city, city);
        this->year = year;
    }

    ~Ekipa() {

    }

    const char *get_Name() {
        return name;
    }
};

class Natprevar {
private:
    Ekipa home;
    Ekipa away;
    int goalsHome;
    int goalsAway;
public:
    Natprevar(const Ekipa &_home, const Ekipa &_away, int goalsHome, int goalsAway) {
        home = _home;
        away = _away;
        this->goalsHome = goalsHome;
        this->goalsAway = goalsAway;
    }

    ~Natprevar() {

    }

    Ekipa get_Home() {
        return home;
    }

    Ekipa get_Away() {
        return away;
    }

    int get_GoalsHome() {
        return goalsHome;
    }

    int get_GoalsAway() {
        return goalsAway;
    }
};

bool e_revans(Natprevar match1, Natprevar match2) {
    if (strcmp(match1.get_Home().get_Name(), match2.get_Away().get_Name()) == 0 &&
        strcmp(match1.get_Away().get_Name(), match2.get_Home().get_Name()) == 0) {
        return true;
    } else
        return false;
}

Ekipa duel(Natprevar match1, Natprevar match2) {
    if (e_revans(match1, match2)) {
        if ((match1.get_GoalsHome() + match2.get_GoalsAway()) > (match1.get_GoalsAway() + match2.get_GoalsHome()))
            return match1.get_Home();
        else if ((match1.get_GoalsHome() + match2.get_GoalsAway()) < (match1.get_GoalsAway() + match2.get_GoalsHome()))
            return match1.get_Away();
        else
            return 0;
    } else {
        cout << "Natprevarite ne se sovpagjaat" << endl;
        return 0;
    }
}

int main() {
    Ekipa e1("Real Madrid", "Madrid", 1880);
    Ekipa e2("FC Barcelona", "Barcelona", 1880);

    Natprevar match1(e1, e2, 1, 2);
    Natprevar match2(e2, e1, 1, 0);

    cout << duel(match1, match2).get_Name();

    return 0;
}