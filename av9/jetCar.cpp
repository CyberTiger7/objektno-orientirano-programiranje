//
// Created by krstevkoki on 4/26/17.
//
#include <iostream>

using namespace std;

class Vehicle {
protected:
    double acceleration;
public:
    Vehicle() {
        cout << "VEHICLE constructor" << endl;
    }

    virtual const void accelerate() const {
        cout << "VEHICLE accelerating" << endl;
    }

    const void setAcceleration(const double &acceleration) {
        this->acceleration = acceleration;
    }

    const double getAcceleration() {
        return acceleration;
    }

    virtual ~Vehicle() {
        cout << "VEHICLE destructor" << endl;
    };
};

class Car : virtual public Vehicle {
private:

public:
    Car() : Vehicle() {
        cout << "CAR constructor" << endl;
    }

    virtual const void accelerate() const {
        cout << "CAR accelerating" << endl;
    }

    virtual const void drive() const {
        cout << "CAR driving" << endl;
    }

    virtual ~Car() {
        cout << "CAR Destructor" << endl;
    }
};

class Jet : virtual public Vehicle {
private:

public:
    Jet() : Vehicle() {
        cout << "JET Constructor" << endl;
    }

    virtual const void fly() const {
        cout << "JET flying" << endl;
    }

    virtual ~Jet() {
        cout << "JET Destructor" << endl;
    }
};

class JetCar : public Car, public Jet {
private:

public:
    JetCar() : Car(), Jet() {
        cout << "JETCAR constructor" << endl;
    }

    const void drive() const {
        cout << "JETCAR driving" << endl;
    }

    const void fly() const {
        cout << "JETCAR flying" << endl;
    }

    const void accelerate() const {
        cout << "JETCAR accelerating" << endl;
    }

    ~JetCar() {
        cout << "JETCAR destructor" << endl;
    }
};

void analyzeCarPerformance(Car &testVehicle /* Car *testVehicle */ ) {
    testVehicle.drive();
    testVehicle.accelerate();
    /* функцијата drive() (accelerate()) може да се повика и со референца(или покажувач)
    кон основната и кон изведената класа. Oваа функција е дефинирана и во двете класи */
}

void analyzeJetPerformance(Jet &testVehicle /* Jet *testVehicle */ ) {
    testVehicle.fly();
    /* fly() е дефинирана и во основната и во изведената класа (Јет и JetCar) */
}

int main() {
    cout << endl << endl;
    Car myCar;
    Jet myJet;
    JetCar myJetCar;
    cout << endl << endl;
    cout << "========================\n"
            "CAR testing in progress\n"
            "========================" << endl;
    analyzeCarPerformance(myCar);
    analyzeCarPerformance(myJetCar);
    cout << "\n========================\n"
            "JET testing in progress\n"
            "========================" << endl;
    analyzeJetPerformance(myJet);
    analyzeJetPerformance(myJetCar);
    cout << endl << endl;
    return 0;
}
