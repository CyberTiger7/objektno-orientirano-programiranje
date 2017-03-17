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

    const char *get_Name() const {
        return name;
    }

    const char *get_Stadium() const {
        return stadium;
    }

    const char *get_City() {
        return city;
    }

    void set_Name(const char *_name) {
        strcpy(name, _name);
    }

    ~Ekipa() {}

};

class Natprevar {
private:
    Ekipa *home;
    Ekipa *away;
    int goals_home;
    int goals_away;
public:
    Natprevar() {}

    Natprevar(const Ekipa &home, const Ekipa &away, int goals_home, int goals_away) {
        this->goals_home = goals_home;
        this->goals_away = goals_away;
        this->home = new Ekipa(home);
        this->away = new Ekipa(away);
    }

    Natprevar(const Natprevar &match) {
        home = new Ekipa(*match.home);
        away = new Ekipa(*match.away);
        goals_home = match.goals_home;
        goals_away = match.goals_away;
    }

    ~Natprevar() {
        delete home;
        delete away;
    }

    const Ekipa *get_Home() {
        return home;
    }

    const Ekipa *get_Away() {
        return away;
    }

    const int get_GoalsHome() {
        return goals_home;
    }

    const int get_GoalsAway() {
        return goals_away;
    }

    friend bool isTip(Natprevar &first, char tip);
};

bool isTip(Natprevar &first, char tip) {
    if ((first.get_GoalsHome() > first.get_GoalsAway()) && (tip == '1'))
        return true;
    else if ((first.get_GoalsHome() < first.get_GoalsAway()) && (tip == '2'))
        return true;
    else if ((first.get_GoalsHome() == first.get_GoalsAway()) && ((tip == 'x') || (tip == 'X')))
        return true;
    else
        return false;
}

int main() {
    Ekipa e1("Real Madrid", "Madrid", "Santiago Bernabeu");
    Ekipa e2("FC Barcelona", "Barcelona", "Camp Nou");

    Natprevar first(e1, e2, 1, 3);

    cout << "Vnesi tip za natprevarot: ";
    cout << first.get_Home()->get_Name(); // get_Name - const funkcija
    cout << " - ";
    cout << first.get_Away()->get_Name();
    cout << endl;

    char tip; //1, 2 ili X
    cin >> tip;

    if (isTip(first, tip)) cout << "Tipot e pogoden";
    else cout << "Tipot ne e pogoden";

    // first.get_Home()->set_Name("RLM"); // ne e mozno: get_Home vrakja konstanten pokazuva
    //first.get_Away()->set_Name("BAR"); // ne e mozno: get_Away vrakja konstanten pokazuvac

    cout << "\nNatprevarot beshe megju: ";
    cout << first.get_Home()->get_Name();
    cout << " - ";
    cout << first.get_Away()->get_Name();
    return 0;
}
