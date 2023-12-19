#ifndef USER_H
#define USER_H
using namespace std;
#include <string>
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

#endif // USER_H
