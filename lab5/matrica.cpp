//
// Created by krstevkoki on 3/20/17.
//
#include <iostream>

using namespace std;

class Matrica {
private:
    int rows;
    int cols;
    float M[10][10];
public:
    Matrica(int rows = 0, int cols = 0, float M[0][0] = 0) {
        this->rows = rows;
        this->cols = cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                this->M[i][j] = M[i][j];
            }
        }
    }

    Matrica(const Matrica &m) {
        this->rows = m.rows;
        this->cols = m.cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                this->M[i][j] = m.M[i][j];
            }
        }
    }

    Matrica operator*(Matrica &m) {
        Matrica temp;
        temp.rows = this->rows;
        temp.cols = m.cols;
        for (int i = 0; i < temp.rows; ++i) {
            for (int j = 0; j < temp.cols; ++j) {
                int sum = 0;
                for (int k = 0; k < m.cols; ++k) {
                    sum += (this->M[i][k] * m.M[k][j]);
                }
                temp.M[i][j] = sum;
            }
        }
        return temp;
    }

    Matrica operator-(Matrica &m) {
        Matrica temp;
        temp.rows = this->rows;
        temp.cols = m.cols;
        for (int i = 0; i < temp.rows; ++i) {
            for (int j = 0; j < temp.cols; ++j) {
                temp.M[i][j] = this->M[i][j] - m.M[i][j];
            }
        }
        return temp;
    }

    Matrica operator+(int num) {
        Matrica temp;
        temp.rows = this->rows;
        temp.cols = this->cols;
        for (int i = 0; i < temp.rows; ++i) {
            for (int j = 0; j < temp.cols; ++j) {
                temp.M[i][j] = this->M[i][j] + num;
            }
        }
        return temp;
    }

    friend ostream &operator<<(ostream &out, Matrica &m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                out << m.M[i][j] << " ";
            }
            out << endl;
        }
        out << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Matrica &m) {
        int rows, cols;
        in >> rows >> cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                in >> m.M[i][j];
            }
        }
        m.rows = rows;
        m.cols = cols;
        return in;
    }
};

int main() {
    Matrica A, B, C;
    cin >> A >> B >> C;
    Matrica D = B * C;
    Matrica R = A - D + 2;
    cout << R;
    return 0;
}
