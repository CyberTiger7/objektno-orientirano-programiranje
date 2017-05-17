//
// Created by krstevkoki on 5/17/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Exception {
private:
    char *errorMsg;
public:
    Exception(const char *errorMsg) {
        this->errorMsg = new char[strlen(errorMsg) + 1];
        strcpy(this->errorMsg, errorMsg);
    }

    Exception(const Exception &e) {
        this->errorMsg = new char[strlen(e.errorMsg) + 1];
        strcpy(this->errorMsg, e.errorMsg);
    }

    Exception &operator=(const Exception &e) {
        if (this != &e) {
            delete[] errorMsg;
            this->errorMsg = new char[strlen(e.errorMsg) + 1];
            strcpy(this->errorMsg, e.errorMsg);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Exception &e) {
        return out << e.errorMsg;
    }

    ~Exception() { delete[] errorMsg; }
};

class Trud {
private:
    char type; // C - konferenciski, J - spisanie
    int year;
public:
    Trud(const char type = 'C', const int year = 0) {
        this->type = toupper(type);
        this->year = year;
    }

    const char getType() const {
        return type;
    }

    const int getYear() const {
        return year;
    }

    friend istream &operator>>(istream &in, Trud &t) {
        in >> t.type >> t.year;
        return in;
    }
};

class Student {
private:
    char name[30];
    int index;
    int year;
    int grades[50];
    int passedExams;
public:
    Student() {
        this->year = 0;
        this->index = 0;
        this->passedExams = 0;
        strcpy(this->name, "");
        for (int i = 0; i < 50; ++i) {
            grades[i] = 0;
        }
    }

    Student(const char *name, const int index, const int year, const int *grades,
            const int passedExams) {
        this->index = index;
        this->year = year;
        this->passedExams = passedExams;
        strcpy(this->name, name);
        for (int i = 0; i < passedExams; ++i) {
            this->grades[i] = grades[i];
        }
    }

    friend ostream &operator<<(ostream &out, const Student &s) {
        out << s.index << " " << s.name << " " << s.year << " " << s.rang() << endl;
        return out;
    }

    virtual const float rang() const {
        float average = 0.0;
        for (int i = 0; i < passedExams; ++i) {
            average += grades[i];
        }
        return average / float(passedExams);
    }

    virtual const int studentType() const {
        return 1;
    }

    const void setIndex(const int index) {
        this->index = index;
    }

    const void setYear(const int year) {
        this->year = year;
    }

    const void setPassedExams(const int passedExams) {
        this->passedExams = passedExams;
    }

    const void setName(const char *name) {
        strcpy(this->name, name);
    }

    const void setGrades(const int *grades, int passedExams) {
        for (int i = 0; i < passedExams; ++i) {
            this->grades[i] = grades[i];
        }
    }

    const char *getName() const {
        return name;
    }

    const int getIndex() const {
        return index;
    }

    const int getYear() const {
        return year;
    }

    const int getPassedExams() const {
        return passedExams;
    }

    const int *getGrades() const {
        return grades;
    }

    virtual ~Student() {}
};

class PhDStudent : public Student {
private:
    Trud *scientificStudies;
    int num_studies;
    static int conferenceStudyPoints;
    static int journalistStudyPoints;
public:
    PhDStudent(const char *name, const int index, const int year, const int *grades,
               const int passedExams, Trud *scientificStudies, const int num_studies)
            : Student(name, index, year, grades, passedExams) {
        this->num_studies = num_studies;
        this->scientificStudies = new Trud[num_studies];
        for (int i = 0, j = 0; i < num_studies; ++i) {
            try {
                if (scientificStudies[i].getYear() < this->getYear())
                    throw Exception("Ne moze da se vnese dadeniot trud\n");
                this->scientificStudies[j++] = scientificStudies[i];
            } catch (Exception &e) {
                cout << e;
                --this->num_studies;
            }
        }
    }

    PhDStudent(const PhDStudent &phd)
            : Student(phd) {
        this->num_studies = phd.num_studies;
        this->scientificStudies = new Trud[phd.num_studies];
        for (int i = 0; i < phd.num_studies; ++i) {
            this->scientificStudies[i] = phd.scientificStudies[i];
        }
    }

    PhDStudent &operator=(const PhDStudent &phd) {
        if (this != &phd) {
            this->setIndex(phd.getIndex());
            this->setYear(phd.getYear());
            this->setPassedExams(phd.getPassedExams());
            this->setName(phd.getName());
            this->setGrades(phd.getGrades(), phd.getPassedExams());
            this->num_studies = phd.num_studies;
            delete[] this->scientificStudies;
            this->scientificStudies = new Trud[phd.num_studies];
            for (int i = 0; i < phd.num_studies; ++i) {
                this->scientificStudies[i] = phd.scientificStudies[i];
            }
        }
        return *this;
    }

    PhDStudent &operator+=(const Trud &t) {
        if (t.getYear() < this->getYear())
            throw Exception("Ne moze da se vnese dadeniot trud\n");
        Trud *tmp = new Trud[num_studies + 1];
        for (int i = 0; i < num_studies; ++i) {
            tmp[i] = scientificStudies[i];
        }
        delete[] scientificStudies;
        scientificStudies = tmp;
        scientificStudies[num_studies++] = t;
        return *this;
    }

    const static void setConferenceStudyPoints(const int points) {
        conferenceStudyPoints = points;
    }

    const static void setJournalistStudyPoints(const int points) {
        journalistStudyPoints = points;
    }

    const float rang() const {
        int sum = 0;
        for (int i = 0; i < num_studies; ++i) {
            if (scientificStudies[i].getType() == 'C')
                sum += conferenceStudyPoints;
            else if (scientificStudies[i].getType() == 'J')
                sum += journalistStudyPoints;
        }
        return Student::rang() + sum;
    }

    const int studentType() const {
        return 2;
    }

    ~PhDStudent() { delete[] scientificStudies; }
};

int PhDStudent::conferenceStudyPoints = 1;
int PhDStudent::journalistStudyPoints = 3;

int main() {
    int testCase;
    cin >> testCase;
    int god, indeks, n, god_tr, m = 0, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Student **niza;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];
            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        for (int i = 0; i < m; ++i) {
            if (niza[i]->getIndex() == indeks) {
                if (niza[i]->studentType() == 2) {
                    try {
                        PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                        *phd += t;
                    } catch (Exception &e) {
                        cout << e;
                    }
                } else
                    cout << "Ne postoi PhD student so indeks " << indeks << endl;
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        for (int i = 0; i < m; ++i)
            delete niza[i];
        delete[] niza;
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];
            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for (int i = 0; i < m; ++i) {
            if (niza[i]->getIndex() == indeks) {
                if (niza[i]->studentType() == 2) {
                    try {
                        PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                        *phd += t;
                    } catch (Exception &e) {
                        cout << e;
                    }
                } else
                    cout << "Ne postoi PhD student so indeks " << indeks << endl;
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        for (int i = 0; i < m; ++i)
            delete niza[i];
        delete[] niza;
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];
            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        // vmetnete go kodot za dodavanje nov trud so
        // pomos na operatorot += i spravete se so isklucokot
        for (int i = 0; i < m; ++i) {
            if (niza[i]->getIndex() == indeks) {
                if (niza[i]->studentType() == 2) {
                    try {
                        PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                        *phd += t;
                    } catch (Exception &e) {
                        cout << e;
                    }
                } else
                    cout << "Ne postoi PhD student so indeks " << indeks << endl;
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        for (int i = 0; i < m; ++i)
            delete niza[i];
        delete[] niza;
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];
            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
        int conf, journal;
        cin >> conf;
        cin >> journal;
        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setConferenceStudyPoints(conf);
        PhDStudent::setJournalistStudyPoints(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        for (int i = 0; i < m; ++i)
            delete niza[i];
        delete[] niza;
    }
    return 0;
}