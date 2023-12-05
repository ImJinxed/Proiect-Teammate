#include <iostream>
#include <User.h>
#include <list>
#include <fstream>
#include <Team.h>
using namespace std;
list<User> readUsersFromFile(const std::string& filename) {
    list<User> userList;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            string nickname = line;
            string password;
            string Rank;
            int subRank;

            if (getline(file, password) &&
                getline(file, Rank) &&
                (file >> subRank)) {
                    file.ignore();
                    User newUser(nickname, password, Rank, subRank);
                    userList.push_back(newUser);
            }
        }

        file.close();
    }
    return userList;
}
void appendReportToFile(const string& nickname, const string& reason, const string& filename) {
    ofstream file;
    file.open(filename, std::ios::app);
    if (file.is_open()) {
        file << nickname << endl;
        file << reason << endl;
        file.close();
    }
}
list<Team> readTeamsFromFile(const string& filename) {
    ifstream file(filename);
    list<Team> teams;
    string line, Rank, Password;
    int  subRank;
    if (file.is_open()) {
        while (getline(file, line)) {
            string teamName = line;
            Team team(teamName);
            list<User> users;

            while (getline(file, line) && line != "---") {
                string userName = line;

                if (getline(file, Password) &&
                getline(file, Rank) &&
                (file >> subRank)) {
                    file.ignore();
                    User newUser(userName, Password, Rank, subRank);
                    team.addUser(newUser);
                }
            }
            teams.push_back(team);
        }

        file.close();
    }
    return teams;
}
void appendUserToFile(const User& user, const string& filename) {
    ofstream file;
    file.open(filename, std::ios::app);

    if (file.is_open()) {
        file << user.getNick() << endl;
        file << user.getPass() << endl;
        file << user.getRank() << endl;
        file << user.getSubRank() << endl;
        file.close();
    }
}
void appendTeamToFile(const Team& team, const string& filename){
    ofstream file;
    file.open(filename, std::ios::app);
    if(file.is_open()){
        file << team.getName()<<endl;
        list<User> us = team.getUsers();
        for(const User& u: us){
            file << u.getNick() << endl;
            file << u.getPass() << endl;
            file << u.getRank() << endl;
            file << u.getSubRank()<<endl;
        }
        file<< "---"<<endl;
        file.close();
    }
}
bool userExists(const list<User>& lista, const string& username) {
    for (const User& u : lista) {
        if (u.getNick() == username) {
            return true;
        }
    }
    return false;
}
User findUserByNickname(const list<User>& lista, const string& nickname) {
    int OK=0;
    for (const User& u : lista) {
        if (u.getNick() == nickname) {
            OK=1;
            return u;
        }
    }
    if(OK==0){
        return User();
    }
}
Team findTeamByName(const list<Team>& lista, const string& nickname) {
    int OK=0;
    for (const Team& u : lista) {
        if (u.getName() == nickname) {
            OK=1;
            return u;
        }
    }
    if(OK==0){
        return Team();
    }
}
int main()
{   string filename = "Users.txt";
    int choice,exec=0;
    list<User> lista;
    User EU = User("L9 KaiSa","razvy99113","Emerald",3);
    User EU2 = User("RocketWizzard","sefu","Diamond",2);
    //lista.push_back(EU);
    //lista.push_back(EU2);
    lista = readUsersFromFile(filename);
    string nick,parola,divi;
    User principal;
    int subdivi;

    do {
        cout << "Menu:\n";
        cout << "1. Autentificare\n";
        cout << "2. Conectare\n";
        cout << "3. Exit\n";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:{
                    cout << "Introduceti nickname, password, name si level:\n";
                    getline(cin,nick);
                    getline(cin,divi);
                    cin>>subdivi;
                    cin.ignore();
                    getline(cin,parola);
                    User a1 = User(nick, parola, divi, subdivi);
                    if (userExists(lista, nick)) {
                        cout << "Utilizatorul exista deja.\n";
                    } else {
                        lista.push_back(a1);
                        exec = 1;
                        break;
                    }
                break;
            }
            case 2:{
                cout << "Ai ales Conectare.\n";
                getline(cin,nick);
                getline(cin,parola);
                User foundUser = findUserByNickname(lista,nick);
                if(!foundUser.empty()&&foundUser.passwordMatch(parola)){
                    principal = foundUser;
                    exec = 1;
                }
                else if(!foundUser.passwordMatch(parola)){
                    cout<< "Conectare nereusita. Parola/Nickname gresit.\n";
                }
                break;
            }
            case 3:{
                exit(0);
                break;
            }
            default:
                cout << "Optiune invalida.\n";
        }

    } while (choice != 3 && exec != 1);
    int exec2 = 0;
    string n,m,name,reason,filename2="Teams.txt",filename3 = "ReportLog.txt";
    list<Team> teams = readTeamsFromFile(filename2);
    //Team t1 = Team("Ratonii");
    //t1.addUser(EU);
    //teams.push_back(t1);
    //Team t2 = Team("Soarecii");
    //t2.addUser(EU2);
    //teams.push_back(t2);
    int choice2,choice3,exec3=0;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Browse" << endl;
        cout << "2. Search" << endl;
        cout << "3. Create" << endl;
        cout << "4. Report" << endl;
        cout << "5. Exit" << endl;
        cout << "Select an option: ";
        cin >> choice2;
        cin.ignore();
        switch (choice2) {
            case 1:{
                for(Team t:teams){
                    t.afisare();
                }
                exec2=1;
                break;
            }
            case 2:{
                exec2=1;
                do{
                    cout<<"1. Search Player"<<endl;
                    cout<<"2. Search Team"<<endl;
                    cin>>choice3;
                    cin.ignore();
                    if(choice3 == 1){
                        getline(cin,n);
                        User searching = findUserByNickname(lista,n);
                        if(searching.empty())
                            cout<<"User not found!\n";
                        else
                            searching.afisare();
                        exec3=1;
                    }else if(choice3 == 2){
                        getline(cin,m);
                        Team searchingT = findTeamByName(teams,m);
                        if(searchingT.empty())
                            cout<<"Team not found!\n";
                        else
                            searchingT.afisare();
                        exec3 = 1;
                    }
                }while(choice3 != 2 && exec3 != 1);
                break;
            }
            case 3:{
                getline(cin,name);
                Team test = Team(name);
                test.addUser(principal);
                appendTeamToFile(test,filename2);
                exec2=1;
                break;
            }
            case 4:{
                cout<<"Report Player:";
                getline(cin,name);
                cout<<"Reason:";
                getline(cin,reason);
                if(findUserByNickname(lista,name).empty())
                    cout<<"User not found!\n";
                else{
                    appendReportToFile(name,reason,filename3);
                }
                exec2=1;
                break;
            }
            case 5:
                exit(0);
                break;
            default:
                cout << "Optiune invalida.\n" <<endl;
        }
    } while (choice2 != 5 && exec2 !=1);
    return 0;
}
