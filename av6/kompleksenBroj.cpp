//
// Created by krstevkoki on 3/20/17.
//
#include <iostream>

using namespace std;

class ComplexNumber {
private:
    float real;
    float imaginary;
public:
    ComplexNumber(float real = 0, float imaginary = 1) {
        this->real = real;
        this->imaginary = imaginary;
    }

    void print() {
        if (imaginary >= 0)
            cout << real << "+" << imaginary << "j" << endl;
        else if (imaginary < 0)
            cout << real << imaginary << "j" << endl;
    }

    ComplexNumber operator+(ComplexNumber &b) {
        return ComplexNumber(this->real + b.real, this->imaginary + b.imaginary);

    }

    bool operator==(ComplexNumber &b) {
        return (this->real == b.real) && (this->imaginary == b.imaginary);
    }

    ComplexNumber &operator++() {
        ++this->real;
        ++this->imaginary;
        return *this;
    }

    ComplexNumber operator++(int) {
        ComplexNumber temp(*this);
        ++this->real;
        ++this->imaginary;
        return temp;
    }

    ComplexNumber &operator+=(ComplexNumber &c) {
        this->real += c.real;
        this->imaginary += c.imaginary;
        return *this;
    }

    ComplexNumber &operator+=(float n) {
        this->real += n;
        return *this;
    }

    friend ostream &operator<<(ostream &out, ComplexNumber c) {
        if (c.imaginary >= 0)
            out << c.real << "+" << c.imaginary << "j";
        else if (c.imaginary < 0)
            out << c.real << c.imaginary << "j";
        return out;
    }
};

int main() {
    ComplexNumber c1(1, 5);
    ComplexNumber c2(3, -7);

    //c1.print(); // operator <<
    //c2.print();  // is overloaded
    cout << c1 << endl;
    cout << c2 << endl;

    ComplexNumber c3 = c1 + c2;
    cout << c3 << endl;

    if (c1 == c2)
        cout << c1 << " i " << c2 << " se isti" << endl;
    else
        cout << c1 << " i " << c2 << " ne se isti" << endl;

    cout << ++c1 << " " << c1 << endl;
    cout << c2++ << " " << c2 << endl;
    cout << (c2 += c3) << endl;
    // c2 e promeneto
    cout << c2 << endl;
    cout << (c1 += 12.5) << endl;
    // c1 e promeneto
    cout << c1 << endl;
    return 0;
}
