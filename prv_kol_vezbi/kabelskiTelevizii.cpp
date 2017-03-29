//
// Created by krstevkoki on 3/29/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class TV {
private:
    char name[100];
    bool type;
    int category;
    float rating;
public:
    TV(char *name = "", bool type = 0, int category = 0, float rating = 0.0) {
        this->type = type;
        this->category = category;
        this->rating = rating;
        strcpy(this->name, name);
    }

    TV(const TV &tv) {
        this->type = tv.type;
        this->category = tv.category;
        this->rating = tv.rating;
        strcpy(this->name, tv.name);
    }

    TV &operator=(const TV &tv) {
        this->type = tv.type;
        this->category = tv.category;
        this->rating = tv.rating;
        strcpy(this->name, tv.name);
        return *this;
    }

    friend ostream &operator<<(ostream &out, const TV &tv) {
        if (tv.type == 1) {
            out << tv.name << endl;
            out << "D" << endl;
            out << tv.category << endl;
            out << tv.rating << endl;
        } else {
            out << tv.name << endl;
            out << "A" << endl;
            out << tv.category << endl;
            out << tv.rating << endl;
        }
        return out;
    }

    TV &operator++() {
        this->rating += 0.5;
        return *this;
    }

    bool operator==(const TV &tv) {
        if (strcmp(this->name, tv.name) == 0)
            if (this->category == tv.category)
                return true;
        return false;
    }

    const float getRating() {
        return rating;
    }
};

class KabelskiOperator {
private:
    char name[100];
    TV *televisions;
    int num_televisions;
public:
    KabelskiOperator(char *name) {
        strcpy(this->name, name);
        this->televisions = NULL;
        this->num_televisions = 0;
    }

    KabelskiOperator(const KabelskiOperator &ko) {
        strcpy(this->name, ko.name);
        this->num_televisions = ko.num_televisions;
        this->televisions = new TV[ko.num_televisions];
        for (int i = 0; i < ko.num_televisions; ++i) {
            this->televisions[i] = ko.televisions[i];
        }
    }

    KabelskiOperator &operator=(const KabelskiOperator &ko) {
        if (this != &ko) {
            strcpy(this->name, ko.name);
            this->num_televisions = ko.num_televisions;
            delete[] this->televisions;
            this->televisions = new TV[ko.num_televisions];
            for (int i = 0; i < ko.num_televisions; ++i) {
                this->televisions[i] = ko.televisions[i];
            }
        }
        return *this;
    }

    KabelskiOperator &operator+=(TV &tv) {
        if (tv.getRating() > float(5)) {
            TV *tmp = new TV[num_televisions + 1];
            for (int i = 0; i < num_televisions; ++i) {
                tmp[i] = televisions[i];
            }
            delete[] televisions;
            televisions = tmp;
            televisions[num_televisions++] = tv;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const KabelskiOperator &ko) {
        out << ko.name << endl;
        for (int i = 0; i < ko.num_televisions; ++i) {
            out << ko.televisions[i] << endl;
        }
        return out;
    }

    void zgolemi(const TV &tv) {
        for (int i = 0; i < num_televisions; ++i) {
            if (televisions[i] == tv) {
                ++televisions[i];
            }
        }
    }

    ~KabelskiOperator() { delete[] televisions; }
};

int main() {
    int n, x;
    cin >> n >> x;
    char name[100];
    cin >> name;
    KabelskiOperator ko(name);
    TV t;
    for (int i = 0; i < n; ++i) {
        char name1[100];
        bool digital;
        int category;
        float rating;
        cin >> name1 >> digital >> category >> rating;
        TV tv(name1, digital, category, rating);
        ko += tv;
        if (i == x) {
            t = tv;
        }
    }

    cout << ko;
    cout << "=== ZGOLEMI ===" << endl;
    cout << t;
    ko.zgolemi(t);
    cout << ko;
    return 0;
}
