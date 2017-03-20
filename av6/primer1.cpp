//
// Created by krstevkoki on 3/20/17.
//

#include <iostream>

using namespace std;

class Array {
private:
    int capacity;
    int num_elements;
    int *array;
public:
    Array(const int capacity = 5) {
        this->capacity = capacity;
        this->num_elements = 0;
        this->array = new int[capacity];
    }

    Array(const Array &a) {
        this->capacity = a.capacity;
        this->num_elements = a.num_elements;
        this->array = new int[a.capacity];
        for (int i = 0; i < a.num_elements; ++i) {
            this->array[i] = a.array[i];
        }
    }

    Array &operator=(Array &a) {
        if (this != &a) {
            this->capacity = a.capacity;
            this->num_elements = a.num_elements;
            delete[] this->array;
            this->array = new int[a.capacity];
            for (int i = 0; i < a.num_elements; ++i) {
                this->array[i] = a.array[i];
            }
        }
        return *this;
    }

    Array &operator-=(int a) {
        int new_numElements = 0;
        for (int i = 0, j = 0; i < num_elements; ++i) {
            if (array[i] != a) {
                array[j++] = array[i];
                new_numElements++;
            }
        }
        num_elements = new_numElements;
        return *this;
    }

    Array &operator+=(int a) {
        if (num_elements == capacity) {
            int *temp = new int[2 * capacity];
            for (int i = 0; i < num_elements; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacity *= 2;
        }
        array[num_elements++] = a;
        return *this;
    }

    friend ostream &operator<<(ostream &out, Array &a) {
        for (int i = 0; i < a.num_elements; ++i) {
            out << a.array[i] << " ";
        }
        for (int i = a.num_elements; i < a.getCapacity(); ++i) {
            out << "_ ";
        }
        return out;
    }

    ~Array() {
        delete[] array;
    }

    const int getCapacity() {
        return capacity;
    }

    const int getNumElements() {
        return num_elements;
    }
};

int main() {
    Array a;
    a += (6);
    a += (4);
    a += (3);
    a += (2);
    a += (1);

    Array b;
    b = a;

    b -= (2);
    b -= (3);

    cout << "Niza a: " << a << endl;
    cout << "Brojot na elementi na nizata a e: " << a.getNumElements() << endl;
    cout << "Kapacitetot na nizata a e: " << a.getCapacity() << endl;

    cout << "Niza b: " << b << endl;
    cout << "Brojot na elementi na nizata b e: " << b.getNumElements() << endl;
    cout << "Kapacitetot na nizata b e: " << b.getCapacity() << endl;

    return 0;
}