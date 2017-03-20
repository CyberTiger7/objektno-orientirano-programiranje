//
// Created by krstevkoki on 3/20/17.
//
#include <iostream>
#include <cstring>

using namespace std;


class Ucenik {
private:
    int school_year;
    float GPA; // grade point average
    char *name;
public:
    Ucenik(char *name = "", float GPA = 0.0, int school_year = 1) {
        this->school_year = school_year;
        this->GPA = GPA;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Ucenik(const Ucenik &s) {
        this->school_year = s.school_year;
        this->GPA = s.GPA;
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
    }

    Ucenik &operator=(const Ucenik &s) {
        if (this != &s) {
            this->school_year = s.school_year;
            this->GPA = s.GPA;
            delete[] this->name;
            this->name = new char[strlen(s.name) + 1];
            strcpy(this->name, s.name);
        }
        return *this;
    }

    Ucenik operator++(int) {
        Ucenik copy(*this);
        ++this->school_year;
        return copy;
    }

    bool operator>(Ucenik &s) {
        return (this->GPA > s.GPA);
    }

    friend ostream &operator<<(ostream &out, Ucenik &s) {
        out << "Ime: " << s.name << "\nProsek: " << s.GPA << "\nGodina: " << s.school_year << endl;
        return out;
    }


    ~Ucenik() { delete[] name; }

    const float getGPA() {
        return GPA;
    }
};

class Paralelka {
private:
    Ucenik *students;
    int num_students;
public:
    Paralelka(Ucenik *students = 0, int num_students = 0) {
        this->num_students = num_students;
        this->students = new Ucenik[num_students];
        for (int i = 0; i < num_students; ++i) {
            this->students[i] = students[i];
        }
    }

    Paralelka(const Paralelka &p) {
        this->num_students = p.num_students;
        this->students = new Ucenik[p.num_students];
        for (int i = 0; i < p.num_students; ++i) {
            this->students[i] = p.students[i];
        }
    }

    Paralelka &operator=(Paralelka &p) {
        if (this != &p) {
            this->num_students = p.num_students;
            delete[] this->students;
            this->students = new Ucenik[p.num_students];
            for (int i = 0; i < p.num_students; ++i) {
                this->students[i] = p.students[i];
            }
        }
        return *this;
    }

    Paralelka &operator+=(Ucenik &s) {
        Ucenik *temp = new Ucenik[num_students + 1];
        for (int i = 0; i < num_students; ++i) {
            temp[i] = students[i];
        }
        delete[] students;
        students = temp;
        students[num_students++] = s;
        return *this;
    }

    Paralelka operator++(int) {
        Paralelka copy(*this);
        for (int i = 0; i < num_students; ++i) {
            students[i]++;
        }
        return copy;
    }

    friend ostream &operator<<(ostream &out, Paralelka &p) {
        for (int i = 0; i < p.num_students; ++i) {
            cout << p.students[i];
        }
        return out;
    }

    ~Paralelka() { delete[] students; }

    void nagradi() {
        for (int i = 0; i < num_students; ++i) {
            if (students[i].getGPA() == 10.0) {
                cout << students[i];
            }
        }
    }

    void najvisokProsek() {
        Ucenik max = students[0];
        for (int i = 1; i < num_students ; ++i) {
            if (students[i] > max)
                max = students[i];
        }
        cout << "Najvisok prosek vo paralelkata: " << max.getGPA() << endl;
    }

};

int main() {
    Ucenik u1("Martina Martinovska", 9.5, 3);
    Ucenik u2("Darko Darkoski", 7.3, 2);
    Ucenik u3("Angela Angelovska", 10, 3);

    Paralelka p;
    p += u1;
    p += u2;
    p += u3;

    cout << p;

    cout << endl;

    cout << "Nagradeni:" << endl;
    p.nagradi();

    cout << endl;
    p.najvisokProsek();

    cout << endl;

    u2++;
    cout << p;
    cout << endl;

    p++;
    cout << p;

    return 0;
}