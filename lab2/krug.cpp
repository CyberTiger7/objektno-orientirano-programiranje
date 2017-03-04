//
// Created by krstevkoki on 2/27/17.
//
#include <iostream>

using namespace std;

class Krug {
private:
    float radius;
    const float Pi = 3.14;
public:
    Krug() {
        radius = 0;
    }

    Krug(float r) {
        radius = r;
    }

    ~Krug() {

    }

    float const perimetar() {
        return 2 * radius * Pi;
    }

    float const plostina() {
        return radius * radius * Pi;
    }

    int ednakvi() {
        if (perimetar() == plostina())
            return 1;
        else
            return 0;
    }
};

int main() {
    float r;
    cin >> r;
    if (r >= 0.0) {
        //instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
        Krug k(r);
        cout << k.perimetar() << endl;
        cout << k.plostina() << endl;
        cout << k.ednakvi() << endl;
    } else
        cout << "Nevalidna vrednost za radius";
    //instanciraj objekt od klasata Krug cij radius ne e definiran
    Krug k1;
    return 0;
}
