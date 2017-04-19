//
// Created by krstevkoki on 2/27/17.
//
#include <iostream>

using namespace std;

lass Krug {
private:
    float r;
    const float PI;
public:
    Krug() : PI(3.14) { 
        r = 0;
    }

    Krug(float r) : PI(3.14) { 
        this->r = r;
    }

    ~Krug() {}

    const float perimetar() {
        return 2 * r * PI;
    }

    const float plostina() {
        return r * r * PI;
    }

    bool ednakvi() {
        if (perimetar() == plostina())
            return true;
        return false;
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
