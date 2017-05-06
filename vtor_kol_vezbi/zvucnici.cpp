//
// Created by krstevkoki on 5/6/17.
//
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

// vashiot kod ovde
class Speaker {
protected:
    float power;
    char model[50];
    bool amp;
    float price;
    static int DDV;
public:
    Speaker(const float power, const char *model, const bool amp, const float price) {
        this->power = power;
        this->amp = amp;
        this->price = price;
        strcpy(this->model, model);
    }

    friend ostream &operator<<(ostream &out, const Speaker &s) {
        if (s.amp)
            return out << s.model << " ima pojachalo " << s.presmetajCena();
        return out << s.model << " nema pojachalo " << s.presmetajCena();
    }

    bool operator>(Speaker &s) {
        return presmetajCena() > s.presmetajCena();
    }

    virtual const float presmetajCena() const = 0;

    static const void smeniDDV(const int ddv) {
        DDV = ddv;
    }

    static const void vkupnoDDV(Speaker **s, int n) {
        float totalPrice = 0.0;
        for (int i = 0; i < n; ++i) {
            totalPrice += s[i]->presmetajCena();
        }
        float totalDDV = abs((float(DDV) / 100) * totalPrice);
        cout << "Vkupna cena: " << totalPrice << endl;
        cout << "Vkupno DDV: " << totalDDV << endl;
    }

    virtual ~Speaker() {}
};

int Speaker::DDV = 18;

class TowerSpeaker : public Speaker {
private:
    bool full_semi;
public:
    TowerSpeaker(const float power, const char *model, const bool amp, const float price,
                 const bool full_semi)
            : Speaker(power, model, amp, price) {
        this->full_semi = full_semi;
    }

    const float presmetajCena() const {
        if (amp && full_semi)
            return price + (float(15) / 100) * price;
        if (amp)
            return price + (float(10) / 100) * price;
        if (full_semi)
            return price + (float(5) / 100) * price;
        return price;
    }

    ~TowerSpeaker() {}
};

class MonitorSpeaker : public Speaker {
private:
    bool function;
public:
    MonitorSpeaker(const float power, const char *model, const bool amp, const float price,
                   const bool function)
            : Speaker(power, model, amp, price) {
        this->function = function;
    }

    const float presmetajCena() const {
        if (amp && function)
            return price + (float(25) / 100) * price;
        if (amp)
            return price + (float(10) / 100) * price;
        if (function)
            return price + (float(15) / 100) * price;
        return price;
    }

    ~MonitorSpeaker() {}
};

const void lowestPrice(Speaker **s, int n) {
    Speaker *min = s[0];
    for (int i = 0; i < n; ++i) {
        if (*min > *s[i])
            min = s[i];
    }
    cout << *min;
}

// zabraneto e menuvanje na main funkcijata
int main() {
    int testCase;
    cin >> testCase;
    float power;
    char model[100];
    bool amp;
    float price;
    bool fullSemi;
    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> power;
        cin >> model;
        cin >> amp;
        cin >> price;
        cin >> fullSemi;
        TowerSpeaker ts(power, model, amp, price, fullSemi);
        cout << ts << endl;
        cin >> power;
        cin >> model;
        cin >> amp;
        cin >> price;
        cin >> fullSemi;
        MonitorSpeaker ms(power, model, amp, price, fullSemi);
        cout << ms << endl;
    } else if (testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        Speaker **speakers = new Speaker *[n];
        for (int i = 0; i < n; ++i) {
            cin >> power;
            cin >> model;
            cin >> amp;
            cin >> price;
            cin >> fullSemi;
            if (i % 2 == 1)
                speakers[i] = new TowerSpeaker(power, model, amp, price, fullSemi);
            else
                speakers[i] = new MonitorSpeaker(power, model, amp, price, fullSemi);
        }
        lowestPrice(speakers, n);
        for (int i = 0; i < n; ++i) {
            delete speakers[i];
        }
        delete[] speakers;
    } else if (testCase == 3) {
        cout << "===== TESTING DDV STATIC ======" << endl;
        int n;
        cin >> n;
        Speaker **speakers = new Speaker *[n];
        for (int i = 0; i < n; ++i) {
            cin >> power;
            cin >> model;
            cin >> amp;
            cin >> price;
            cin >> fullSemi;
            if (i % 2 == 1)
                speakers[i] = new TowerSpeaker(power, model, amp, price, fullSemi);
            else
                speakers[i] = new MonitorSpeaker(power, model, amp, price, fullSemi);
        }
        Speaker::vkupnoDDV(speakers, n);
        int ddv;
        cin >> ddv;
        Speaker::smeniDDV(ddv);
        Speaker::vkupnoDDV(speakers, n);
        for (int i = 0; i < n; ++i) {
            delete speakers[i];
        }
        delete[] speakers;
    }
    return 0;
}