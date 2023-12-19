#pragma once
#include <list>
#include "User.h"
#include <iostream>
class Team
{
private:
    string nume;
    list<User> useri;
public:
    Team(string);
    void addUser(const User&);
    void afisare();
    string getName() const;
    bool empty() const;
    Team();
    list<User> getUsers() const;
};

