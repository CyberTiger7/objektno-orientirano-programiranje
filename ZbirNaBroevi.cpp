//
// Created by krstevkoki on 2/14/17.
//
#include <iostream>

using namespace std;

int main() {
    int zbir = 0;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        zbir = zbir + i;
    }
    cout << "Zbirot na prvite " << n << " broevi e: " << zbir << endl;
    return 0;
}
