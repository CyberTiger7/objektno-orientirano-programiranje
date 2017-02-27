//
// Created by krstevkoki on 2/27/17.
//
#include <iostream>

using namespace std;

class Agol {
private:
    int degrees;
    int minutes;
    int seconds;
public:
    Agol() {
        // constructor
    }

    ~Agol() {
        // destructor
    }

    // set functions
    void set_stepeni(int const deg) {
        degrees = deg;
    }

    void set_minuti(int const min) {
        minutes = min;
    }

    void set_sekundi(int const sec) {
        seconds = sec;
    }

    long int to_sekundi() {
        long int sekundi = 0;
        sekundi = (degrees * 3600) + (minutes * 60) + seconds;
        return sekundi;
    }
};

int proveri(int deg, int min, int sec);

int main() {
    Agol a1;
    //da se instancira objekt od klasata Agol
    int deg, min, sec;
    cin >> deg >> min >> sec;
    if (proveri(deg, min, sec)) {
        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
    } else
        cout << "Nevalidni vrednosti za agol";
    return 0;
}

int proveri(int deg, int min, int sec) {
    if (deg > 360 || deg < 0)
        return 0;
    else if (min > 59 || min < 0)
        return 0;
    else if (sec > 59 || sec < 0)
        return 0;
    else
        return 1;
}
