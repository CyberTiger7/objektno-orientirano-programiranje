//
// Created by krstevkoki on 5/6/17.
//
#include <iostream>

using namespace std;

class Expression {
public:
    virtual const int solve() const = 0;

    virtual const void print() const = 0;

    virtual ~Expression() {}
};

class Number : public Expression {
private:
    int number;
public:
    Number(const int number) {
        this->number = number;
    }

    const int solve() const {
        return number;
    }

    const void print() const {
        cout << number;
    }

    ~Number() {}
};

class BinaryExpression : public Expression {
protected:
    Expression *e1;
    Expression *e2;
public:
    BinaryExpression(Expression *e1, Expression *e2) {
        this->e1 = e1;
        this->e2 = e2;
    }

    ~BinaryExpression() {}
};

class Multiplification : public BinaryExpression {
public:
    Multiplification(Expression *e1, Expression *e2)
            : BinaryExpression(e1, e2) {}

    const int solve() const {
        return e1->solve() * e2->solve();
    }

    const void print() const {
        e1->print();
        cout << "*";
        e2->print();
    }

    ~Multiplification() {}
};

class Addition : public BinaryExpression {
public:
    Addition(Expression *e1, Expression *e2)
            : BinaryExpression(e1, e2) {}

    const int solve() const {
        return e1->solve() + e2->solve();
    }

    const void print() const {
        e1->print();
        cout << "+";
        e2->print();
    }

    ~Addition() {}
};

class Division : public BinaryExpression {
public:
    Division(Expression *e1, Expression *e2)
            : BinaryExpression(e1, e2) {}

    const int solve() const {
        return e1->solve() / e2->solve();
    }

    const void print() const {
        e1->print();
        cout << "/";
        e2->print();
    }

    ~Division() {}
};

class Modulo : public BinaryExpression {
public:
    Modulo(Expression *e1, Expression *e2)
            : BinaryExpression(e1, e2) {}

    const int solve() const {
        return e1->solve() % e2->solve();
    }

    const void print() const {
        e1->print();
        cout << "%";
        e2->print();
    }

    ~Modulo() {}
};

class Substraction : public BinaryExpression {
public:
    Substraction(Expression *e1, Expression *e2)
            : BinaryExpression(e1, e2) {}

    const int solve() const {
        return e1->solve() - e2->solve();
    }

    const void print() const {
        e1->print();
        cout << "-";
        e2->print();
    }

    ~Substraction() {}
};

int main() {
    // 3 * 5 + 2
    BinaryExpression *e = new Addition(
            new Multiplification(
                    new Number(3),
                    new Number(5)
            ), new Number(2)
    );
    e->print();
    cout << "=" << e->solve() << endl;
    delete e;

    return 0;
}