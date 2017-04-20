//
// Created by krstevkoki on 4/4/17.
//
#include <iostream>
#include <cstring>

using namespace std;

class TennisPlayer {
private:
    char name[100];
    char surname[100];
    bool playsInLeague;
public:
    TennisPlayer(const char *name = "", const char *surname = "", bool playsInLeague = false) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->playsInLeague = playsInLeague;
    }

    TennisPlayer(const TennisPlayer &tp) {
        strcpy(this->name, tp.name);
        strcpy(this->surname, tp.surname);
        this->playsInLeague = tp.playsInLeague;
    }

    TennisPlayer &operator=(const TennisPlayer &tp) {
        if (this != &tp) {
            strcpy(this->name, tp.name);
            strcpy(this->surname, tp.surname);
            this->playsInLeague = tp.playsInLeague;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const TennisPlayer &tp) {
        if (tp.playsInLeague)
            return out << tp.name << " " << tp.surname << ", igra vo liga";
        else
            return out << tp.name << " " << tp.surname << ", ne igra vo liga";
    }

    bool PlaysInLeague() {
        return playsInLeague;
    }

    void setPlaysInLeague(bool pl) {
        this->playsInLeague = pl;
    }
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;
public:
    RankedTennisPlayer(const char *name, const char *surname, bool playsInLeague = false, int rank = 0)
            : TennisPlayer(name, surname, playsInLeague) {
        this->rank = rank;
    }

    RankedTennisPlayer(const TennisPlayer &tp, int rank) : TennisPlayer(tp) {
        this->rank = rank;
    }

    RankedTennisPlayer(const RankedTennisPlayer &rtp) : TennisPlayer(rtp) {
    	this->rank = rtp.rank;
    }

    friend ostream &operator<<(ostream &out, const RankedTennisPlayer &rtp) {
        out << TennisPlayer(rtp) << " " << rtp.rank;
        return out;
    }
};

int main() {
    TennisPlayer rf("Roger", "Federer");
    TennisPlayer ng("Novak", "Djokovikj");
    cout << rf << endl;
    cout << ng << endl;
    //TennisPlayer t;
    RankedTennisPlayer rn("Rafael", "Nadal", true, 2750);
    cout << rn << endl;
    TennisPlayer tp = rn;
    cout << tp << endl;
    //RankedTennisPlayer copy(tp);
    RankedTennisPlayer copy(ng, 3320);
    cout << copy << endl;
    RankedTennisPlayer copy1 = rn;
    cout << copy1 << endl;
    return 0;
}
