//
// Created by krstevkoki on 5/17/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class OutOfBoundException {
private:
    char *errorMsg;
public:
    OutOfBoundException(const char *errorMsg) {
        this->errorMsg = new char[strlen(errorMsg) + 1];
        strcpy(this->errorMsg, errorMsg);
    }

    OutOfBoundException(const OutOfBoundException &e) {
        this->errorMsg = new char[strlen(e.errorMsg) + 1];
        strcpy(this->errorMsg, e.errorMsg);
    }

    OutOfBoundException &operator=(const OutOfBoundException &e) {
        if (this != &e) {
            delete[] this->errorMsg;
            this->errorMsg = new char[strlen(e.errorMsg) + 1];
            strcpy(this->errorMsg, e.errorMsg);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const OutOfBoundException &e) {
        return out << e.errorMsg;
    }

    ~OutOfBoundException() { delete[] errorMsg; }
};

class Karticka {
protected:
    char account[16];
    int PIN;
    bool morePINCodes;
public:
    Karticka(const char *account, const int PIN) {
        strcpy(this->account, account);
        this->PIN = PIN;
        this->morePINCodes = false;
    }
    // дополнете ја класата

    friend ostream &operator<<(ostream &out, const Karticka &k) {
        out << k.account << ": " << k.penetrationTest() << endl;
        return out;
    }

    virtual const int penetrationTest() const {
        int difficulty = 0;
        int tempPIN = PIN;
        while (tempPIN) {
            ++difficulty;
            tempPIN /= 10;
        }
        return difficulty;
    }

    const bool getDopolnitelenPin() const {
        return morePINCodes;
    }

    const char *getAccount() const {
        return account;
    }

    virtual ~Karticka() {}
};

//вметнете го кодот за SpecijalnaKarticka

class SpecijalnaKarticka : public Karticka {
private:
    int *additionalPINCodes;
    int num_PINCodes;
    const static int P = 4;
public:
    SpecijalnaKarticka(const char *account, const int PIN)
            : Karticka(account, PIN) {
        this->morePINCodes = true;
        this->num_PINCodes = 0;
        this->additionalPINCodes = NULL;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &sk)
            : Karticka(sk) {
        this->morePINCodes = true;
        this->num_PINCodes = sk.num_PINCodes;
        this->additionalPINCodes = new int[sk.num_PINCodes];
        for (int i = 0; i < sk.num_PINCodes; ++i) {
            this->additionalPINCodes[i] = sk.additionalPINCodes[i];
        }
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &sk) {
        if (this != &sk) {
            strcpy(this->account, sk.account);
            this->PIN = sk.PIN;
            this->morePINCodes = true;
            this->num_PINCodes = sk.num_PINCodes;
            delete[] this->additionalPINCodes;
            this->additionalPINCodes = new int[sk.num_PINCodes];
            for (int i = 0; i < sk.num_PINCodes; ++i) {
                this->additionalPINCodes[i] = sk.additionalPINCodes[i];
            }
        }
        return *this;
    }

    SpecijalnaKarticka &operator+=(const int PIN) {
        if (num_PINCodes + 1 > P)
            throw OutOfBoundException("Brojot na pin kodovi ne moze da "
                                              "go nadmine dozvolenoto\n");
        int *tmp = new int[num_PINCodes + 1];
        for (int i = 0; i < num_PINCodes; ++i) {
            tmp[i] = additionalPINCodes[i];
        }
        delete[] additionalPINCodes;
        additionalPINCodes = tmp;
        additionalPINCodes[num_PINCodes++] = PIN;
        return *this;
    }

    const int penetrationTest() const {
        return Karticka::penetrationTest() + num_PINCodes;
    }

    ~SpecijalnaKarticka() { delete[] additionalPINCodes; }
};

class Banka {
private:
    char name[30];
    Karticka *cards[20];
    int num_cards;
    static int LIMIT;
public:
    Banka(const char *name, Karticka **cards, const int num_cards) {
        strcpy(this->name, name);
        for (int i = 0; i < num_cards; i++) {
            //ako kartickata ima dopolnitelni PIN kodovi
            if (cards[i]->getDopolnitelenPin())
                this->cards[i] = new SpecijalnaKarticka(*dynamic_cast
                        <SpecijalnaKarticka *>(cards[i]));
            else
                this->cards[i] = new Karticka(*cards[i]);
        }
        this->num_cards = num_cards;
    }

    //да се дополни класата
    static const void setLIMIT(const int limit) {
        LIMIT = limit;
    }

    const void pecatiKarticki() const {
        cout << "Vo bankata " << name << " mozat da se probijat kartickite:" << endl;
        for (int i = 0; i < num_cards; ++i) {
            if (cards[i]->penetrationTest() <= LIMIT)
                cout << *cards[i];
        }
    }

    void dodadiDopolnitelenPin(const char *account, const int newPIN) {
        for (int i = 0; i < num_cards; ++i) {
            if (cards[i]->getDopolnitelenPin()) {
                if (strcmp(cards[i]->getAccount(), account) == 0) {
                    try {
                        SpecijalnaKarticka *sk = dynamic_cast<
                                SpecijalnaKarticka *>(cards[i]);
                        *sk += newPIN;
                    } catch (OutOfBoundException &e) {
                        cout << e;
                    }
                }
            }
        }
    }

    ~Banka() {
        for (int i = 0; i < num_cards; i++)
            delete cards[i];
    }
};

int Banka::LIMIT = 7;

int main() {
    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }
    Banka komercijalna("Komercijalna", niza, n);

    for (int i = 0; i < n; i++)
        delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;
        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }
    Banka::setLIMIT(5);
    komercijalna.pecatiKarticki();
    return 0;
}