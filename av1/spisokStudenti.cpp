//
// Created by krstevkoki on 2/20/17.
//
#include <iostream>

using namespace std;

struct student {
    char first_name[20];
    char last_name[40];
    int index;
    int points;
};

void sort(student students[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (students[j].points < students[j + 1].points) {
                student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }

        }
    }
}

void first_uppercase(char *string) {
    *string = toupper(*string);
    while (*(++string) != '\0')
        *string = tolower(*string);

}

void read(student *students, int MAX) {
    cout << "First Name, Last Name, Index, Points [4 Exercises]" << endl;
    for (int i = 0; i < MAX; ++i) {
        cin >> students[i].first_name;
        cin >> students[i].last_name;
        cin >> students[i].index;
        students[i].points = 0;
        for (int j = 0; j < 4; ++j) {
            int exercise_points;
            cin >> exercise_points;
            students[i].points += exercise_points;
        }
    }
}

void print(student *students, int MAX) {
    cout << "La_Na \t Fi_Na \t Index \t Points" << endl;
    for (int i = 0; i < MAX; ++i) {
        cout << students[i].last_name << " \t";
        cout << students[i].first_name << " \t";
        cout << students[i].index << " \t";
        cout << students[i].points << endl;
    }
}

int main() {
    int MAX;
    cout << "No. students: ";
    cin >> MAX;
    if (MAX > 100) {
        cout << "Povekje od 100 studenti ne se dozvoleni";
        return 0;
    }
    student students[MAX];
    read(students, MAX);
    for (int i = 0; i < MAX; ++i) {
        first_uppercase(students[i].first_name);
        first_uppercase(students[i].last_name);
    }
    sort(students, MAX);
    print(students, MAX);
    return 0;
}
