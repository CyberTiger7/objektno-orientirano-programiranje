//
// Created by krstevkoki on 2/20/17.
//
#include <iostream>

using namespace std;

struct vector {
    int x;
    int y;
    int z;
};

float skalaren_proizvod(vector &v1, vector &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector vektorski_proizvod(vector &v1, vector &v2) {
    vector v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

void read(vector &v) {
    cin >> v.x;
    cin >> v.y;
    cin >> v.z;
}

int main() {
    vector v1;
    vector v2;

    read(v1);
    read(v2);

    cout << "Skalarniot proizvod na vektorite e: " << skalaren_proizvod(v1, v2) << endl;
    vector v = vektorski_proizvod(v1, v2);
    cout<<"v1 x v2 = ["<<v.x<<","<<v.y<<","<<v.z<<"]"<<endl;
    return 0;
}