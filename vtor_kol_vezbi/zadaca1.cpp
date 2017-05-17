//
// Created by krstevkoki on 5/17/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char ISBN[20];
    char author[30];
    char title[50];
    float price;
public:
    Book(const char *ISBN = "", const char *title = "", const char *author = "",
         const float price = 0.0) {
        this->price = price;
        strcpy(this->ISBN, ISBN);
        strcpy(this->title, title);
        strcpy(this->author, author);
    }

    bool operator>(const Book &f) {
        return this->price > f.price;
    }

    friend ostream &operator<<(ostream &out, const Book &f) {
        out << f.ISBN << ": " << f.title << ", " << f.author << " " << f.bookPrice() << endl;
        return out;
    }

    virtual const float bookPrice() const = 0;

    virtual const int bookType() const = 0;

    const void setISBN(const char *ISBN) {
        strcpy(this->ISBN, ISBN);
    }

    virtual ~Book() {}
};

class OnlineBook : public Book {
private:
    char *url;
    int size;
public:
    OnlineBook(const char *ISBN, const char *title, const char *author,
               const float price, const char *url, const int size)
            : Book(ISBN, title, author, price) {
        this->size = size;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    OnlineBook(const Book &b, const char *url, const int size)
            : Book(b) {
        this->size = size;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    OnlineBook(const OnlineBook &ob)
            : Book(ob) {
        this->size = ob.size;
        this->url = new char[strlen(ob.url) + 1];
        strcpy(this->url, ob.url);
    }

    OnlineBook &operator=(const OnlineBook &ob) {
        if (this != &ob) {
            strcpy(this->ISBN, ob.ISBN);
            strcpy(this->title, ob.title);
            strcpy(this->author, ob.author);
            this->price = ob.price;
            this->size = ob.size;
            delete[] this->url;
            this->url = new char[strlen(ob.url) + 1];
            strcpy(this->url, url);
        }
        return *this;
    }

    const float bookPrice() const {
        if (size > 20)
            return price + (float(20) / 100) * price;
        return price;
    }

    const int bookType() const {
        return 1;
    }

    ~OnlineBook() { delete[] url; }
};

class PrintBook : public Book {
private:
    float weight;
    bool onSupply;
public:
    PrintBook(const char *ISBN, const char *title, const char *author,
              const float price, const float weight, const bool onSupply)
            : Book(ISBN, title, author, price) {
        this->weight = weight;
        this->onSupply = onSupply;
    }

    const float bookPrice() const {
        if (weight > 0.7)
            return price + (float(15) / 100) * price;
        return price;
    }

    const int bookType() const {
        return 2;
    }

    ~PrintBook() {}
};

const void mostExpensiveBook(Book **books, int n) {
    int num_books[2];
    num_books[0] = 0; // broj na OnlineBook knigi
    num_books[1] = 0; // broj na PrintBook knigi
    Book *max = books[0];
    for (int i = 0; i < n; ++i) {
        if (books[i]->bookType() == 1)
            ++num_books[0];
        else if (books[i]->bookType() == 2)
            ++num_books[1];
        if (!(*max > *books[i]))
            max = books[i];
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << num_books[0] << endl;
    cout << "Total number of print books: " << num_books[1] << endl;
    cout << "The most expensive book is: " << endl;
    cout << *max;
}

int main() {
    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n = 0;
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];
        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];
        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];
        for (int i = 0; i < n; i++) {
            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {
                cin >> url;
                cin >> size;
                books[i] = new OnlineBook(isbn, title, author, price, url, size);
            } else {
                cin >> weight;
                cin >> inStock;
                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }
        mostExpensiveBook(books, n);
    }
    for (int i = 0; i < n; i++)
        delete books[i];
    delete[] books;

    return 0;
}