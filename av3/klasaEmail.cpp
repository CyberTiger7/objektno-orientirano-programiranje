//
// Created by krstevkoki on 2/23/17.
//
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Email {
private:
    enum {
        AddressLength = 100, SubjectLength = 200, BodyLength = 1000
    };
    char to[AddressLength];
    char from[AddressLength];
    char subject[SubjectLength];
    char body[BodyLength];
public:
    Email(char *t, char *f, char *s, char *b) {
        strcpy(to, t);
        strcpy(from, f);
        strcpy(subject, s);
        strcpy(body, b);
    }

    ~Email() {

    }

    // get functions
    const char *getTo() {
        return to;
    }

    const char *getFrom() {
        return from;
    }

    const char *getSubject() {
        return subject;
    }

    const char *getBody() {
        return body;
    }

    /* void print() {
        cout << "To: " << to << endl;
        cout << "From: " << from << endl;
        cout << "Subject: " << subject << endl;
        cout << "Body: " << body << endl;

    } */
};

int is_valid(char *String);

int read(char *to, char *from, char *subject, char *body);

int main() {
    char to[100];
    char from[100];
    char subject[200];
    char body[1000];

    if (read(to, from, subject, body) == 0) {
        return 0;
    }

    Email poraka(to, from, subject, body);

    cout << "To: " << poraka.getTo() << endl;
    cout << "From: " << poraka.getFrom() << endl;
    cout << "Subject: " << poraka.getSubject() << endl;
    cout << "Body: " << poraka.getBody() << endl;

    //poraka.print();
}

int is_valid(char String[]) {
    int counter = 0;
    for (int i = 0; i < strlen(String); ++i) {
        if (String[i] == '@') {
            counter++;
        }
    }
    return (1 == counter);
}

int read(char *to, char *from, char *subject, char *body) {
    cout << "To: ";
    cin >> to;
    if (is_valid(to)) {
        cout << "From: ";
        cin >> from;
        if (is_valid(from)) {
            cout << "Subject: ";
            cin >> subject;
            cout << "Body: ";
            cin >> body;
        } else {
            cout << "Nevalidna e-mail adresa";
            return 0;
        }
    } else {
        cout << "Nevalidna e-mail adresa";
        return 0;
    }
}

