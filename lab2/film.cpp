//
// Created by krstevkoki on 2/27/17.
//
#include <iostream>
#include <cstring>

using namespace std;

// vashiot kod ovde
class Film {
private:
    char name[100];
    char producer[50];
    char genre[50];
    int year;
public:
    Film() {

    }

    Film(char *n, char *p, char *g, int y) {
        strcpy(name, n);
        strcpy(producer, p);
        strcpy(genre, g);
        year = y;
    }

    // set functions
    void set_name(const char *ime) {
        strcpy(name, ime);
    }

    void set_producer(const char *reziser) {
        strcpy(producer, reziser);
    }

    void set_genre(const char *zanr) {
        strcpy(genre, zanr);
    }

    void set_year(const int godina) {
        year = godina;
    }

    // get functions

    char const *get_name() {
        return name;
    }

    char const *get_producer() {
        return producer;
    }

    char const *get_genre() {
        return genre;
    }

    int const get_year() {
        return year;
    }
};

void pecati_po_godina(Film *f, int n, int godina) {
    for (int i = 0; i < n; ++i) {
        if (f[i].get_year() == godina) {
            cout << "Ime: " << f[i].get_name() << endl;
            cout << "Reziser: " << f[i].get_producer() << endl;
            cout << "Zanr: " << f[i].get_genre() << endl;
            cout << "Godina: " << f[i].get_year()<< endl;
        }
    }
}

int main() {
    int n;
    cin >> n;
    //da se inicijalizira niza od objekti od klasata Film
    Film movies[100];
    for (int i = 0; i < n; ++i) {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        //da se kreira soodveten objekt
        movies[i].set_name(ime);
        movies[i].set_producer(reziser);
        movies[i].set_genre(zanr);
        movies[i].set_year(godina);

    }
    int godina;
    cin >> godina;
    //da se povika funkcijata pecati_po_godina
    pecati_po_godina(movies, n, godina);
    return 0;
}
