//
// Created by krstevkoki on 2/23/17.
//
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Triangle {
private:
    int a;
    int b;
    int c;
public:
    Triangle(int x = 0, int y = 0, int z = 0) {
        a = x;
        b = y;
        c = z;
    }

    ~Triangle() {

    }

    int perimeter() {
        return a + b + c;
    }

    float area() {
        float s = (a + b + c) / float(2);
        return sqrt(s * (s - a) * (s - b) * (s - b));
    }
};

int main() {
    int x, y, z;
    cout << "Vnesi gi stranite na triagolnikot: ";
    cin >> x >> y >> z;
    if ((x + y) <= z || (x + z) <= y || (y + z) <= x) {
        cout << "Triagolnikot ne mozhe da se konstruira";
        return 0;
    }
    Triangle t1(x, y, z);
    cout << "Perimetarot na triagolnikot e: " << t1.perimeter() << endl;
    cout << "Plostinata na triagolnikot e: " << setprecision(4) << t1.area() << endl;
    return 0;
}