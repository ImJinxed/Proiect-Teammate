#include <SFML/Graphics.hpp>
#include <iostream>
#include "User.h"
#include "Team.h"
#include <string.h>
bool userExists(const list<User>& lista, const string& username) {
    for (const User& u : lista) {
        if (u.getNick() == username) {
            return true;
        }
    }
    return false;
}
User findUserByNickname(const list<User>& lista, const string& nickname) {
    int OK = 0;
    for (const User& u : lista) {
        if (u.getNick() == nickname) {
            OK = 1;
            return u;
        }
    }
    if (OK == 0) {
        return User();
    }
}
class UserDisplay {
public:
    UserDisplay(const std::vector<User>& users, sf::Font& font)
        : users(users), font(font) {}

    void draw(sf::RenderWindow& window,int n) {
        for (size_t i = 0; i < users.size(); ++i) {
            sf::Text userText;
            userText.setFont(font);
            userText.setCharacterSize(20);
            userText.setFillColor(sf::Color::White);
            userText.setString(users[i].getNick());

            // Adjust the position based on the index
            userText.setPosition(55 + n*300, 129 + i * 38);

            window.draw(userText);
        }
    }
private:
    const std::vector<User>& users;
    sf::Font& font;
};
class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, const std::string& text)
        : text(text) {
        buttonShape.setPosition(position);
        buttonShape.setSize(size);
        buttonShape.setFillColor(sf::Color(0,0,0,0));

        if (!font.loadFromFile("Resources/kenvector_future.ttf")) {
            // Handle font loading error
            std::cerr << "Error loading font!" << std::endl;
        }

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(position.x + 10, position.y + 18);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    bool isClicked(sf::Vector2f mousePosition) {
        return buttonShape.getGlobalBounds().contains(mousePosition);
    }

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font font;
    std::string text;
};

class TextBox {
public:
    TextBox(sf::Vector2f position, sf::Vector2f size, const std::string& placeholder)
        : placeholder(placeholder),isActive(false) {
        textBoxShape.setPosition(position);
        textBoxShape.setSize(size);
        textBoxShape.setFillColor(sf::Color(0, 128, 255,80));
        textBoxShape.setOutlineThickness(1);
        textBoxShape.setOutlineColor(sf::Color(0,0,0,0));

        if (!font.loadFromFile("Resources/kenvector_future.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position.x + 5, position.y + 7);
        text.setString(placeholder);
    }
    void setActive(bool active) {
        isActive = active;
    }
    bool isActiveTextBox() const {
        return isActive;
    }
    void draw(sf::RenderWindow& window) {
        window.draw(textBoxShape);
        window.draw(text);
    }

    void handleInput(sf::Event event) {
        if (isActive) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !inputString.empty()) {
                    // Handle backspace
                    inputString.pop_back();
                }
                else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    // Handle printable characters
                    inputString += static_cast<char>(event.text.unicode);
                }
                updateText();
            }
        }
    }

    void updateText() {
        text.setString(inputString);
    }

    std::string getInput() const {
        return inputString;
    }
    bool isClicked(sf::Vector2f mousePosition) const {
        return textBoxShape.getGlobalBounds().contains(mousePosition);
    }

private:
    sf::RectangleShape textBoxShape;
    sf::Text text;
    sf::Font font;
    std::string placeholder;
    std::string inputString;
    bool isActive;
};

enum class Scene {
    AuthLogin,
    Login,
    Registration,
    MainMenu,
    BrowseScene,
    SearchScene,
    ReportScene,
    CreateScene,
    toFindUser,
    ReportResult
};

int main() {
    User u1 = User("L9 KaiSa", "razvy99113", "Emerald", 3);
    User u2 = User("RocketWizzard", "botiuadi2", "Emerald", 2);
    User u3 = User("Vasile", "oaie", "Emerald", 1);
    User principal;
    std::vector<User> users1;
    users1.push_back(u1);
    users1.push_back(u2);
    users1.push_back(u3);
    std::vector<User> users2;
    users2.push_back(u3);
    users2.push_back(u1);
    users2.push_back(u2);
    std::list<User>userslist;
    userslist.push_back(u1);
    userslist.push_back(u2);
    userslist.push_back(u3);
    Team t1;
    t1.addUser(u1);
    t1.addUser(u2);
    vector<Team> teams;
    teams.push_back(t1);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TeamMate");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Resources/background1.png"))
        return -1;
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("Resources/button.png"))
        return -1;
    sf::Texture textBoxTexture;
    if (!textBoxTexture.loadFromFile("Resources/textBox.png"))
        return -1;
    Scene currentScene = Scene::AuthLogin;

    Button authButton(sf::Vector2f(100, 100), sf::Vector2f(150, 50), "Authenticate");
    sf::Sprite buttonAuth(buttonTexture);
    buttonAuth.setPosition(100, 100);
    Button loginButton(sf::Vector2f(100, 200), sf::Vector2f(150, 50), "Login");
    sf::Sprite buttonLogin(buttonTexture);
    buttonLogin.setPosition(100, 200);
    TextBox usernameBox(sf::Vector2f(100, 100), sf::Vector2f(250, 40), "Enter username");
    TextBox passwordBox(sf::Vector2f(100, 200), sf::Vector2f(250, 40), "Enter password");

    TextBox usernameRegistrationBox(sf::Vector2f(100, 100), sf::Vector2f(250, 40), "Enter username");
    TextBox emailRegistrationBox(sf::Vector2f(100, 200), sf::Vector2f(350, 40), "Enter email");
    TextBox passwordRegistrationBox(sf::Vector2f(100, 300), sf::Vector2f(250, 40), "Enter password");
    TextBox searchUserBox(sf::Vector2f(100, 200), sf::Vector2f(250, 40), "Enter User");
    TextBox reportPlayerBox(sf::Vector2f(100, 200), sf::Vector2f(250, 40), "Report");

    Button reportPlayerButton(sf::Vector2f(100, 450), sf::Vector2f(200, 30), "Report");
    sf::Sprite reportPlayerButtonsp(buttonTexture);
    reportPlayerButtonsp.setPosition(100, 450);

    Button searchUserButton(sf::Vector2f(100, 350), sf::Vector2f(200, 30), "Search");
    sf::Sprite searchUserButtonsp(buttonTexture);
    searchUserButtonsp.setPosition(100, 350);

    Button confAuth(sf::Vector2f(100, 400), sf::Vector2f(200, 30), "Authentificate");
    sf::Sprite confAuthsp(buttonTexture);
    confAuthsp.setPosition(100, 400);

    Button confLog(sf::Vector2f(100, 400), sf::Vector2f(200, 30), "Login");
    sf::Sprite confLogsp(buttonTexture);
    confLogsp.setPosition(100, 400);

    Button browseButton(sf::Vector2f(100, 100), sf::Vector2f(200, 30), "Browse Teams");
    sf::Sprite browseButtonsp(buttonTexture);
    browseButtonsp.setPosition(100, 100);

    Button searchButton(sf::Vector2f(100, 200), sf::Vector2f(200, 30), "Search");
    sf::Sprite searchButtonsp(buttonTexture);
    searchButtonsp.setPosition(100, 200);

    Button createTeamButton(sf::Vector2f(500, 100), sf::Vector2f(200, 30), "Create Team");
    sf::Sprite createTeamButtonsp(buttonTexture);
    createTeamButtonsp.setPosition(500, 100);

    Button reportButton(sf::Vector2f(500, 200), sf::Vector2f(200, 30), "Report");
    sf::Sprite reportButtonsp(buttonTexture);
    reportButtonsp.setPosition(500, 200);
    sf::Text browseTitle;
    sf::Font fontFormat;
    if (!fontFormat.loadFromFile("Resources/fontFormat.ttf")) {
        return -1;
    }
    browseTitle.setFont(fontFormat);
    browseTitle.setString("Browse Teams");
    browseTitle.setCharacterSize(30);
    browseTitle.setPosition(50, 50);
    sf::Text mainMenuTitle;
    mainMenuTitle.setFont(fontFormat);
    mainMenuTitle.setString("Main Menu");
    mainMenuTitle.setCharacterSize(30);
    mainMenuTitle.setPosition(50, 50);
    sf::Text searchTitle;
    searchTitle.setFont(fontFormat);
    searchTitle.setString("Search Menu");
    searchTitle.setCharacterSize(30);
    searchTitle.setPosition(50, 50);
    sf::Text reportTitle;
    reportTitle.setFont(fontFormat);
    reportTitle.setString("Report Menu");
    reportTitle.setCharacterSize(30);
    reportTitle.setPosition(50, 50);
    sf::Text createTeamTitle;
    createTeamTitle.setFont(fontFormat);
    createTeamTitle.setString("Create Team Menu");
    createTeamTitle.setCharacterSize(30);
    createTeamTitle.setPosition(50, 50);
    UserDisplay UD(users1, fontFormat);
    UserDisplay UD1(users2, fontFormat);
    sf::Texture teamBoxTexture;
    if (!teamBoxTexture.loadFromFile("Resources/TeamBox.png")) {
        return -1;
    }
    sf::Sprite teamBoxsp(teamBoxTexture);
    teamBoxsp.setPosition(50, 100);
    sf::Sprite teamBoxsp2(teamBoxTexture);
    teamBoxsp2.setPosition(350, 100);
    sf::Sprite teamBoxsp3(teamBoxTexture);
    teamBoxsp3.setPosition(650, 100);
    std::vector<User> usersToFind;
    sf::Text toFindTheUser;
    toFindTheUser.setFont(fontFormat);
    toFindTheUser.setPosition(100, 100);
    std::vector<User> newTeam;
    bool userFound = false;
    User toFindUser;
    
    sf::Text toReportPlayer;
    toReportPlayer.setFont(fontFormat);
    toReportPlayer.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            switch (currentScene) {
                case Scene::AuthLogin:
                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                            if (authButton.isClicked(mousePosition)) {
                                std::cout << "Authenticate button clicked!" << std::endl;
                                currentScene = Scene::Registration;
                            } else if (loginButton.isClicked(mousePosition)) {
                                std::cout << "Login button clicked!" << std::endl;
                                currentScene = Scene::Login;
                            }
                        }
                    }
                    break;

                case Scene::Login:
                    usernameBox.handleInput(event);
                    passwordBox.handleInput(event);

                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                            if (usernameBox.isClicked(mousePosition)) {
                                usernameBox.setActive(true);
                                passwordBox.setActive(false);
                            }
                            else if (passwordBox.isClicked(mousePosition)) {
                                usernameBox.setActive(false);
                                passwordBox.setActive(true);
                            }
                            else {
                                usernameBox.setActive(false);
                                passwordBox.setActive(false);
                            }
                            if (confLog.isClicked(mousePosition)) {
                                std::string n = usernameBox.getInput();
                                std::string pass = passwordBox.getInput();
                                User foundUser = findUserByNickname(userslist, n);
                                if (!foundUser.empty() && foundUser.passwordMatch(pass)) {
                                    principal = foundUser;
                                    newTeam.push_back(principal);
                                    currentScene = Scene::MainMenu;
                                }
                                else if (!foundUser.passwordMatch(pass)) {
                                    cout << "Wrong account!" << std::endl;
                                }
                            }
                        }
                    }
                    break;
                case Scene::MainMenu:
                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                            if (browseButton.isClicked(mousePosition))
                                currentScene = Scene::BrowseScene;
                            if (searchButton.isClicked(mousePosition))
                                currentScene = Scene::SearchScene;
                            if (reportButton.isClicked(mousePosition))
                                currentScene = Scene::ReportScene;
                            if (createTeamButton.isClicked(mousePosition))
                                currentScene = Scene::CreateScene;
                        }
                    }

                case Scene::Registration:
                    usernameRegistrationBox.handleInput(event);
                    emailRegistrationBox.handleInput(event);
                    passwordRegistrationBox.handleInput(event);

                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                            if (usernameRegistrationBox.isClicked(mousePosition)) {
                                usernameRegistrationBox.setActive(true);
                                emailRegistrationBox.setActive(false);
                                passwordRegistrationBox.setActive(false);
                            }
                            else if (emailRegistrationBox.isClicked(mousePosition)) {
                                usernameRegistrationBox.setActive(false);
                                emailRegistrationBox.setActive(true);
                                passwordRegistrationBox.setActive(false);                             
                            }
                            else if (passwordRegistrationBox.isClicked(mousePosition)) {
                                usernameRegistrationBox.setActive(false);
                                emailRegistrationBox.setActive(false);
                                passwordRegistrationBox.setActive(true);
                            }
                            else {
                                usernameRegistrationBox.setActive(false);
                                emailRegistrationBox.setActive(false);
                                passwordRegistrationBox.setActive(false);
                            }
                            if (confAuth.isClicked(mousePosition)) {
                                std::string nick = usernameRegistrationBox.getInput();
                                std::string pas = passwordRegistrationBox.getInput();
                                if (userExists(userslist, nick))
                                    std::cout << "The user already exists!" << std::endl;
                                else {
                                    User a1(nick, pas, "Emerald", 4);
                                    userslist.push_back(a1);
                                    principal = a1;
                                    newTeam.push_back(principal);
                                    currentScene = Scene::MainMenu;
                                }
                                
                            }
                            
                        }
                    }
                    break;
                case Scene::SearchScene:
                    searchUserBox.handleInput(event);
                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                            if (searchUserBox.isClicked(mousePosition)) {
                                searchUserBox.setActive(true);
                            }
                            if (searchUserButton.isClicked(mousePosition)) {
                                std::string tofind = searchUserBox.getInput();
                                toFindUser = findUserByNickname(userslist, tofind);
                                if (!toFindUser.empty()) {
                                    userFound = true;
                                }
                                else
                                    userFound = false;
                                currentScene = Scene::toFindUser;
                            }
                        }
                    }
                    break;
                case Scene::ReportScene:
                    reportPlayerBox.handleInput(event);
                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                            if (reportPlayerBox.isClicked(mousePosition)) {
                                reportPlayerBox.setActive(true);
                            }
                            if (reportPlayerButton.isClicked(mousePosition)) {
                                std::string toreport1 = reportPlayerBox.getInput();
                                User toreport = findUserByNickname(userslist, toreport1);
                                if (!toreport.empty()) {
                                    toReportPlayer.setString("Player: " + toreport.getNick() + " has been reported succesfully!");
                                }
                                else
                                    toReportPlayer.setString("No player found to report!");
                                currentScene = Scene::ReportResult;
                            }
                        }
                    }
                default:
                    break;
            }
        }
        UserDisplay UD2(newTeam, fontFormat);
        if (userFound)
            toFindTheUser.setString(toFindUser.getNick() + " - " + toFindUser.getRank() + ' ' + to_string(toFindUser.getSubRank()));
        else
            toFindTheUser.setString("User Not Found!");
        window.clear();
        window.draw(backgroundSprite);
        switch (currentScene) {
            case Scene::AuthLogin:
                window.draw(buttonAuth);
                window.draw(buttonLogin);
                authButton.draw(window);
                loginButton.draw(window);
                break;

            case Scene::Login:
                usernameBox.draw(window);
                passwordBox.draw(window);
                window.draw(confLogsp);
                confLog.draw(window);
                break;

            case Scene::Registration:
                usernameRegistrationBox.draw(window);
                emailRegistrationBox.draw(window);
                passwordRegistrationBox.draw(window);
                window.draw(confAuthsp);
                confAuth.draw(window);
                break;

            case Scene::MainMenu:
                window.draw(mainMenuTitle);
                window.draw(browseButtonsp);
                browseButton.draw(window);
                window.draw(searchButtonsp);
                searchButton.draw(window);
                window.draw(createTeamButtonsp);
                createTeamButton.draw(window);
                window.draw(reportButtonsp);
                reportButton.draw(window);
                break;
            case Scene::BrowseScene:
                window.draw(browseTitle);
                window.draw(teamBoxsp);
                window.draw(teamBoxsp2);
                UD.draw(window,0);
                UD1.draw(window, 1);
                break;

            case Scene::SearchScene:
                window.draw(searchTitle);
                window.draw(searchUserButtonsp);
                searchUserButton.draw(window);
                searchUserBox.draw(window);
                break;
            case Scene::ReportScene:
                window.draw(reportTitle);
                window.draw(reportPlayerButtonsp);
                reportPlayerButton.draw(window);
                reportPlayerBox.draw(window);
                break;
            case Scene::ReportResult:
                window.draw(toReportPlayer);
                break;
            case Scene::CreateScene:
                window.draw(createTeamTitle);
                window.draw(teamBoxsp);
                window.draw(teamBoxsp2);
                window.draw(teamBoxsp3);
                UD.draw(window, 0);
                UD1.draw(window, 1);
                UD2.draw(window, 2);
                break;
            case Scene::toFindUser:
                window.draw(toFindTheUser);
                break;
            default:
                break;
        }

        window.display();
    }

    return 0;
}
