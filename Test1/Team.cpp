#include "Team.h"
Team::Team(string nume) {
    this->nume = nume;
}
void Team::addUser(const User& u) {
    useri.push_back(u);
}
void Team::afisare() {
    cout << "Echipa: " << this->nume << '\n';
    cout << "_______________\n";
    for (User u : useri) {
        u.afisare();
        cout << "_______________\n";
    }
}
string Team::getName()const {
    return this->nume;
}
bool Team::empty()const {
    return nume.empty();
}
Team::Team() {};
list<User> Team::getUsers() const {
    return this->useri;
}
