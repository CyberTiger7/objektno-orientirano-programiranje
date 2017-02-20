//
// Created by krstevkoki on 2/20/17.
//
#include <iostream>

using namespace std;

struct pres {
    char first_name[20];
    char last_name[40];
    char political_view[50];
};

struct capital_city {
    char name[50];
    int population;
};

struct country {
    char name[50];
    pres president;
    capital_city city;
    int population;
} countries[100];

int maxPopulation(country *countries, int n){
    int max_i = 0;
    int max = countries[0].city.population;
    for (int i = 1; i < n; ++i) {
        if (countries[i].city.population > max) {
            max = countries[i].city.population;
            max_i = i;
        }
    }
    return max_i;
}

void read(int n) {
    for (int i = 0; i < n; ++i) {
        cin >> countries[i].name;
        cin >> countries[i].president.first_name;
        cin >> countries[i].president.last_name;
        cin >> countries[i].president.political_view;
        cin >> countries[i].city.name;
        cin >> countries[i].city.population;
        cin >> countries[i].population;
    }
}

void print(int n) {
    for (int i = 0; i < n; ++i) {
        cout << countries[i].name << "\t";
        cout << countries[i].president.first_name << "\t";
        cout << countries[i].president.last_name << "\t";
        cout << countries[i].president.political_view << "\t";
        cout << countries[i].city.name << "\t";
        cout << countries[i].city.population << "\t";
        cout << countries[i].population << endl;
    }
}

int main() {
    int MAX;
    cout<<"Broj na drzavi: ";
    cin >> MAX;
    read(MAX);
    int index = maxPopulation(countries, MAX);
    print(MAX);
    cout<<countries[index].president.first_name<<" "<<countries[index].president.last_name<<endl;
    return 0;
}