//
// Created by krstevkoki on 3/17/17.
//

#include <iostream>

using namespace std;

class Array {
private:
    int *pole;
    int capacity;
    int size;
public:
    Array(int capacity = 5) {
        this->capacity = capacity;
        size = 0;
        pole = new int[capacity];
    }

    Array(const Array &p) {
        size = p.size;
        capacity = p.capacity;
        pole = new int[capacity];
        for (int i = 0; i < size; ++i) {
            pole[i] = p.pole[i];
        }
    }

    ~Array() {
        delete[] pole;
    }

    Array &operator=(const Array &p) {
        if (this != &p) {
            this->size = p.size;
            this->capacity = p.capacity;
            delete[] pole;
            pole = new int[capacity];
            for (int i = 0; i < size; ++i) {
                pole[i] = p.pole[i];
            }
        }
        return *this;

    }

    void add(int n) {
        if (size == capacity) {
            capacity = capacity * 2;
            int *pole2 = new int[capacity];
            for (int i = 0; i < size; ++i) {
                pole2[i] = pole[i];
            }
            delete[] pole;
            pole = pole2;
        }
        pole[size] = n;
        ++size;
    }

    void print() {
        cout << "Kapacitet: " << capacity << endl;
        cout << "Broj na elementi: " << size << endl;
        for (int i = 0; i < size; ++i) {
            cout << pole[i] << " ";
        }
        cout << endl;
    }

    void change(int a, int b) {
        for (int i = 0; i < size; ++i) {
            if (pole[i] == a) {
                pole[i] = b;
            }
        }
    }

    void deleteAll(int num) {
        int newSize = 0;
        for (int i = 0, j = 0; i < size; ++i) {
            if (pole[i] != num) {
                pole[j++] = pole[i];
                ++newSize;
            }
        }
        size = newSize;
    }

};

int main() {
    Array a;
    a.add(6);
    a.add(4);
    a.add(3);
    a.add(2);
    a.add(1);
    //a.print();

    Array b(a);
    //b.print();

    b.add(2);
    b.change(2, 6);
    //b.print();

    Array c;
    c = b;
    c.print();

    c.deleteAll(6);
    c.print();
    return 0;
}