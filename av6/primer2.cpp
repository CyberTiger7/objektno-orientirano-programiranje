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
    Array(const int capacity = 2) {
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
            this->num_elements = a.num_elements;
            this->capacity = a.capacity;
            delete[] this->array;
            this->array = new int[a.capacity];
            for (int i = 0; i < a.num_elements; ++i) {
                this->array[i] = a.array[i];
            }
        }
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
            capacity = capacity * 2;
        }
        array[num_elements++] = a;
        return *this;
    }

    Array &operator-=(int a) {
        int newNumElements = 0;
        for (int i = 0, j = 0; i < num_elements; ++i) {
            if (array[i] != a) {
                array[j++] = array[i];
                newNumElements++;
            }
        }
        num_elements = newNumElements;
        return *this;
    }

    friend ostream &operator<<(ostream &out, Array &a) {
        for (int i = 0; i < a.num_elements; ++i) {
            out << a.array[i] << " ";
        }

        for (int i = a.num_elements; i < a.capacity; ++i) {
            out << "_ ";
        }

        return out;
    }

    int &operator[](int index) {
        int exit = -1;
        if (index >= 0 && index <= num_elements) {
            return array[index];
        } else
            return exit;
    }

    bool operator==(Array &b) {
        if (this->num_elements != b.num_elements)
            return false;
        for (int i = 0; i < num_elements; ++i)
            if (this->array[i] != b.array[i])
                return false;
        return true;
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
    a += 6;
    a += 4;
    a += 3;
    a += 2;
    a += 1;
    a += 7;
    a += 2;
    a += 3;

    Array b;
    b = a;

    b -= 2;
    b -= 3;

    cout << "Niza a: " << a << endl;
    cout << "Brojot na elementi na nizata a e: " << a.getNumElements() << endl;
    cout << "Kapacitetot na nizata a e: " << a.getCapacity() << endl;

    a[0] = 9;
    cout << "Promeneta nizata a: " << a << endl;
    cout << "Brojot na elementi na nizata a e: " << a.getNumElements() << endl;
    cout << "Kapacitetot na nizata a e: " << a.getCapacity() << endl;

    cout << "Niza b: " << b << endl;
    cout << "Brojot na elementi na nizata b e: " << b.getNumElements() << endl;
    cout << "Kapacitetot na nizata b e: " << b.getCapacity() << endl;


    if (a == b)
        cout << "Isti se" << endl;
    else
        cout << "Ne se isti" << endl;
    return 0;
}