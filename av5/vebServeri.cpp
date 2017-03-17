//
// Created by krstevkoki on 3/17/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class WebPage {
private:
    char url[100];
    char *content;
public:
    WebPage(char *url = "", char *content = "") {
        strcpy(this->url, url);
        this->content = new char[strlen(content) + 1];
        strcpy(this->content, content);
    }

    WebPage(const WebPage &wp) {
        strcpy(this->url, wp.url);
        this->content = new char[strlen(wp.content) + 1];
        strcpy(this->content, wp.content);
    }

    WebPage &operator=(WebPage &wp) {
        if (this != &wp) {
            strcpy(this->url, wp.url);
            delete[] content;
            this->content = new char[strlen(wp.content) + 1];
            strcpy(this->content, wp.content);
        }
        return *this;
    }

    ~WebPage() {
        delete[] content;
    }

    bool daliSeIsti(WebPage p) {
        if (strcmp(this->url, p.url) == 0)
            return true;
        else
            return false;
    }

    friend class WebServer;

};

class WebServer {
private:
    char name[30];
    int count;
    WebPage *wp;
public:
    WebServer(char *name = "", int count = 0, WebPage *wp = 0) {
        strcpy(this->name, name);
        this->count = count;
        this->wp = new WebPage[count];
        for (int i = 0; i < count; ++i) {
            this->wp[i] = wp[i];
        }
    }

    WebServer(const WebServer &ws) {
        strcpy(this->name, ws.name);
        this->count = ws.count;
        this->wp = new WebPage[ws.count];
        for (int i = 0; i < ws.count; ++i) {
            this->wp[i] = ws.wp[i];
        }
    }

    WebServer &operator=(WebServer &ws) {
        if (this != &ws) {
            strcpy(this->name, ws.name);
            this->count = ws.count;
            delete[] this->wp;
            this->wp = new WebPage[ws.count];
            for (int i = 0; i < ws.count; ++i) {
                wp[i] = ws.wp[i];
            }
        }
        return *this;
    }

    ~WebServer() {
        delete[] wp;
    }

    WebServer &addPage(WebPage p) {
        WebPage *temp = new WebPage[count + 1];
        for (int i = 0; i < count; ++i) {
            temp[i] = wp[i];
        }
        temp[count] = p;
        ++count;
        delete[] wp;
        wp = temp;
        return *this;
    }

    void listPages() {
        cout << "Golemina: " << count << endl;
        for (int i = 0; i < count; ++i) {
            cout << wp[i].url << "\t" << wp[i].content << endl;
        }
    }
};

int main() {
    WebPage wp1("http://www.google.com", "The search engine");
    WebPage wp2("http://www.finki.ukim.mk", "FINKI");
    WebPage wp3("http://www.time.mk", "Site vesti");

    WebServer ws(" Server ");

    ws.addPage(wp1);
    ws.addPage(wp2);
    ws.addPage(wp3);

    ws.listPages();
    return 0;
}