#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class User
{
private:
    string nickname;
    string password;
    string divizie;
    int subdivizie;
public:
    User(string nick, string pass, string divizie, int subdivizie);
    void afisare();
    bool operator==(const User& other) const;
    string getNick() const;
    string getPass() const;
    string getRank() const;
    int getSubRank() const;
    User();
    bool empty() const;
    bool passwordMatch(const string&) const;
};

