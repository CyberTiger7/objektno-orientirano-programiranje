//
// Created by krstevkoki on 3/29/17.
//

#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik {
private:
    char *name;
    bool sex;
    int age;
public:
    Ucesnik(char *name = "", bool sex = 0, int age = 0) {
        this->sex = sex;
        this->age = age;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Ucesnik(const Ucesnik &participant) {
        this->sex = participant.sex;
        this->age = participant.age;
        this->name = new char[strlen(participant.name) + 1];
        strcpy(this->name, participant.name);
    }

    Ucesnik &operator=(const Ucesnik &participant) {
        if (this != &participant) {
            this->sex = participant.sex;
            this->age = participant.age;
            delete[] this->name;
            this->name = new char[strlen(participant.name) + 1];
            strcpy(this->name, participant.name);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Ucesnik &participant) {
        if (participant.sex == 0) {
            out << participant.name << endl;
            out << "zhenski" << endl;
            out << participant.age;
        } else {
            out << participant.name << endl;
            out << "mashki" << endl;
            out << participant.age;
        }
        return out;
    }

    bool operator>(const Ucesnik &participant) {
        return this->age > participant.age;
    }

    const int getAge() {
        return age;
    }

    ~Ucesnik() { delete name; }
};

class Maraton {
private:
    char location[100];
    Ucesnik *participants;
    int num_participants;
public:
    Maraton(char *location) {
        strcpy(this->location, location);
        this->participants = NULL;
        this->num_participants = 0;
    }

    Maraton(const Maraton &m) {
        strcpy(this->location, m.location);
        this->num_participants = m.num_participants;
        this->participants = new Ucesnik[m.num_participants];
        for (int i = 0; i < m.num_participants; ++i) {
            this->participants[i] = m.participants[i];
        }
    }

    Maraton &operator=(const Maraton &m) {
        if (this != &m) {
            strcpy(this->location, m.location);
            this->num_participants = m.num_participants;
            delete[] this->participants;
            this->participants = new Ucesnik[m.num_participants];
            for (int i = 0; i < m.num_participants; ++i) {
                this->participants[i] = m.participants[i];
            }
        }
        return *this;
    }

    Maraton &operator+=(Ucesnik &participant) {
        Ucesnik *tmp = new Ucesnik[num_participants + 1];
        for (int i = 0; i < num_participants; ++i) {
            tmp[i] = participants[i];
        }
        delete[] participants;
        participants = tmp;
        participants[num_participants++] = participant;
        return *this;
    }

    float prosecnoVozrast() {
        float average = 0.0;
        for (int i = 0; i < num_participants; ++i) {
            average += participants[i].getAge();
        }
        average /= float(num_participants);
        return average;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < num_participants; ++i) {
            if (participants[i].getAge() < u.getAge()) {
                cout << participants[i] << endl;
            }
        }
    }

    ~Maraton() { delete[] participants; }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast();
    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete[] u;
    return 0;
}