#include "/src/Clases/User.h"
#include <iostream>
User::User(string nick, string pass, string di, int subdi): nickname(nick), password(pass), divizie(di), subdivizie(subdi) {}
void User::afisare() {
	cout << "Nickname: " << this->nickname << endl;
	cout << "Rank: " << this->divizie << ' ' << this->subdivizie <<endl;
}
bool User::operator==(const User& other) const{
    return nickname == other.nickname;
}
string User::getNick()const {
    return this->nickname;
}
bool User::empty()const{
    return nickname.empty();
}
User::User(){};
bool User::passwordMatch(const string& p)const{
    if(p == this->password)
        return true;
    else
        return false;
}
string User::getPass()const {
    return this->password;
}
string User::getRank()const {
    return this->divizie;
}
int User::getSubRank()const {
    return this->subdivizie;
}
