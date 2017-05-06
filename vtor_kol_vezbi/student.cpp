//
// Created by krstevkoki on 5/6/17.
//
#include <iostream>
#include <string.h>

using namespace std;

class BadInputException {
private:
    char *errorMsg;
public:
    BadInputException(const char *errorMsg) {
        this->errorMsg = new char[strlen(errorMsg) + 1];
        strcpy(this->errorMsg, errorMsg);
    }

    BadInputException(const BadInputException &e) {
        this->errorMsg = new char[strlen(e.errorMsg) + 1];
        strcpy(this->errorMsg, errorMsg);
    }

    BadInputException &operator=(const BadInputException &e) {
        if (this != &e) {
            delete[] this->errorMsg;
            this->errorMsg = new char[strlen(e.errorMsg) + 1];
            strcpy(this->errorMsg, errorMsg);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const BadInputException &e) {
        return out << e.errorMsg;
    }

    ~BadInputException() { delete[] errorMsg; }
};

class StudentKurs {
protected:
    char name[30];
    int grade;
    bool daliUsno;
    static int MAX;
    const static int MINGRADE = 6;
public:
    StudentKurs(const char *name, const int grade) {
        strcpy(this->name, name);
        this->grade = grade;
        this->daliUsno = false;
    }

    //дополни ја класата
    friend ostream &operator<<(ostream &out, const StudentKurs &sk) {
        return out << sk.name << " --- " << sk.grade << endl;
    }

    static const void setMAX(const int m) {
        MAX = m;
    }

    virtual const int ocenka() const {
        return grade;
    }

    const bool getDaliUsno() const {
        return daliUsno;
    }

    const bool havePassed() const {
        return grade >= MINGRADE;
    }

    const char *getName() const {
        return name;
    }

    virtual ~StudentKurs() {}
};

int StudentKurs::MAX = 10;

//вметни го кодот за StudentKursUsno
class StudentKursUsno : public StudentKurs {
private:
    char *descriptiveGrade;
public:
    StudentKursUsno(const char *name, const int grade)
            : StudentKurs(name, grade) {
        this->descriptiveGrade = NULL;
        this->daliUsno = true;
    }

    StudentKursUsno(const StudentKurs &sk, const char *descriptiveGrade)
            : StudentKurs(sk.getName(), sk.ocenka()) {
        this->descriptiveGrade = new char[strlen(descriptiveGrade) + 1];
        strcpy(this->descriptiveGrade, descriptiveGrade);
    }

    StudentKursUsno &operator=(const StudentKursUsno &sku) {
        if (this != &sku) {
            strcpy(this->name, sku.name);
            this->grade = sku.grade;
            this->daliUsno = sku.daliUsno;
            delete[] this->descriptiveGrade;
            this->descriptiveGrade = new char[strlen(sku.descriptiveGrade) + 1];
            strcpy(this->descriptiveGrade, sku.descriptiveGrade);
        }
        return *this;
    }

    StudentKursUsno &operator+=(const char *descriptiveGrade) {
        delete[] this->descriptiveGrade;
        this->descriptiveGrade = new char[strlen(descriptiveGrade) + 1];
        strcpy(this->descriptiveGrade, descriptiveGrade);
        return *this;
    }

    const void setGrade(const int grade) {
        if (grade <= MAX)
            this->grade = grade;
    }

    const int ocenka() const {
        if (strcmp(descriptiveGrade, "odlicen") == 0)
            return grade + 2;
        else if (strcmp(descriptiveGrade, "dobro") == 0)
            return grade + 1;
        else if (strcmp(descriptiveGrade, "losho") == 0)
            return grade - 1;
        return grade;
    }

    ~StudentKursUsno() { delete[] descriptiveGrade; }
};

class KursFakultet {
private:
    char name[30];
    StudentKurs *students[20];
    int num_students;
public:
    KursFakultet(const char *name, StudentKurs **students, const int num_students) {
        this->num_students = num_students;
        strcpy(this->name, name);
        for (int i = 0; i < num_students; i++) {
            //ako studentot ima usno isprashuvanje
            if (students[i]->getDaliUsno())
                this->students[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(students[i]));
            else
                this->students[i] = new StudentKurs(*students[i]);
        }
    }

    //дополни ја класата
    const void postaviOpisnaOcenka(const char *name, const char *descriptiveGrade) {
        for (int i = 0; i < num_students; ++i) {
            if (strcmp(students[i]->getName(), name) == 0) {
                if (students[i]->getDaliUsno()) {
                    StudentKursUsno *tmp = dynamic_cast<StudentKursUsno *>(students[i]);
                    *tmp += descriptiveGrade;
                }
            }
        }
    }

    const void pecatiStudenti() const {
        for (int i = 0; i < num_students; ++i) {
            if (students[i]->getDaliUsno()) {
                StudentKursUsno *tmp = dynamic_cast<StudentKursUsno *>(students[i]);
                tmp->setGrade(tmp->ocenka());
            }
        }

        cout << "Kursot " << name << " go polozile:" << endl;
        for (int i = 0; i < num_students; ++i) {
            if (students[i]->havePassed())
                cout << *students[i];
        }
    }

    ~KursFakultet() {
        for (int i = 0; i < num_students; i++)
            delete students[i];
    }
};

int main() {
    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;

    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);

    for (int i = 0; i < n; i++)
        delete niza[i];
    delete[] niza;

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> ime >> opisna;
        try {
            for (int j = 0; j < strlen(opisna); ++j) {
                if (!isalpha(opisna[j]))
                    throw BadInputException("Greshna opisna ocenka\n");
            }
            programiranje.postaviOpisnaOcenka(ime, opisna);
        } catch (BadInputException &e) {
            int k = 0;
            for (int j = 0; j < strlen(opisna); ++j) {
                if (isalpha(opisna[j]))
                    opisna[k++] = opisna[j];
            }
            opisna[k] = '\0';

            cout << e;
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
    }

    StudentKurs::setMAX(9);
    programiranje.pecatiStudenti();

    return 0;
}