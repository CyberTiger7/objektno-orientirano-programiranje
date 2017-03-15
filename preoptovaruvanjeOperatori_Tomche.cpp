#include <iostream>

using namespace std;

class Complex {
private:
    float real, imag;
public:
    Complex(float r, float i) {
        real = r;
        imag = i;
    }

    void print() {
        cout << real << " ";
        if (imag > 0)
            cout << "+";
        cout << imag << "j" << endl;
    }

    friend ostream &operator<<(ostream &out, const Complex &c) {
        out << c.real << " ";
        if (c.imag > 0)
            out << "+";
        out << c.imag << "j" << endl;
        return out;
    }

    Complex operator+(Complex &right) {
        return Complex(real + right.real, imag + right.imag);
    }

    bool operator==(Complex &right) {
        return real == right.real && imag == right.imag;
    }

    bool operator!=(Complex &r) {
        return !(*this == r);
    }

    float operator[](int i) {
        if (i == 0) return real;
        else if (i == 1) return imag;
        else {
            cout << "Index should be 0 or 1" << endl;
            return -1;
        }
    }

    Complex &operator++() {
        ++real;
        ++imag;
        return *this;
    }

    Complex operator++(int) {
        Complex copy(*this);
        ++real;
        ++imag;
        return copy;
    }

    Complex &operator+=(Complex &c) {
        real += c.real;
        imag += c.imag;
        return *this;
    }

    Complex &operator+=(float x) {
        real += x;
        imag += x;
        return *this;
    }
};

int main() {
    Complex c1(1, 5);
    Complex c2(3, -7);

    c1.print();
    c2.print();
    cout << c1;

    Complex c3 = c1 + c2;

    cout << (c1 == c2);
    cout << c1[0];
    cout << ++c1 << c1;
    cout << c2++ << c2;
    cout << (c1 += c2);
    cout << (c1 += 12.5);

    return 0;
}