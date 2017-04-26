//
// Created by krstevkoki on 4/26/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class TimRakomet {
protected:
    char name[30];
    float averageGoals;
public:
    TimRakomet(const char *name, const float averageGoals) {
        strcpy(this->name, name);
        this->averageGoals = averageGoals;
    }

    virtual const float dostignuvanje() const = 0;

    const char *getName() const {
        return name;
    }

    virtual ~TimRakomet() {}
};

class Klub : public TimRakomet {
private:
    int num_trophies;
public:
    Klub(const char *name, const float averageGoals, const int num_trophies)
            : TimRakomet(name, averageGoals) {
        this->num_trophies = num_trophies;
    }

    const float dostignuvanje() const {
        return (averageGoals * 5) + (num_trophies * 50);
    }
};

class Reprezentacija : public TimRakomet {
private:
    int rank[3];
public:
    Reprezentacija(const char *name, const float averageGoals, const int *rank)
            : TimRakomet(name, averageGoals) {
        for (int i = 0; i < 3; ++i) {
            this->rank[i] = rank[i];
        }
    }

    const float dostignuvanje() const {
        float price = 0.0;
        for (int i = 0; i < 3; ++i) {
            if (rank[i] == 1)
                price += 60;
            else if (rank[i] == 2)
                price += 40;
            else
                price += 20;
        }
        return price + (5 * averageGoals);
    }
};

void najdobar(TimRakomet **timovi, int n) {
    TimRakomet *max = timovi[0];
    for (int i = 1; i < n; ++i) {
        if (max->dostignuvanje() < timovi[i]->dostignuvanje())
            max = timovi[i];
    }
    cout << max->getName() << endl << max->dostignuvanje() << endl;
}

int main() {
    int n;
    cin >> n;
    TimRakomet **timovi = new TimRakomet *[n];
    for (int i = 0; i < n; ++i) {
        char ime[30];
        float prosekGolovi;
        cin >> ime >> prosekGolovi;
        if (i % 2) {
            int tituli;
            cin >> tituli;
            timovi[i] = new Klub(ime, prosekGolovi, tituli);
        } else {
            int rank[] = {0, 0, 0};
            cin >> rank[0] >> rank[1] >> rank[2];
            timovi[i] = new Reprezentacija(ime, prosekGolovi, rank);
        }
    }

    najdobar(timovi, n);

    for (int i = 0; i < n; ++i) {
        delete timovi[i];
    }
    delete[] timovi;
    return 0;
}
