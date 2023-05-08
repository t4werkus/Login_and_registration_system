#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

bool strisdigit(string& line); //Проверка строки на число

void checkCorrectChoice(string& choice); // Проверка, что пользователь ввел правильно выбор действия

void enterlogin(string& login, string& password); // ввод логина и пароля

void registration(); // блок регистрации
void entrance(); // блок входа

void loginsToVector(vector <string>& loginsFromFileInVector); // создание вектора логина + пароль

int main(){
    cout << "Are you a new user?(inter the number)\n1) Yes\n2) No\n";
    string choice;
    cin >> choice;
    checkCorrectChoice(choice);
    if (choice == "1") {
        registration();
        string repeat;
        cout << "\nDo you want to Login?(Enter the number)\n1) Yes\n2) No\n";
        cin >> repeat;
        checkCorrectChoice(repeat);
        if (repeat == "1") {
            entrance();
        }
        else {
            return 0;
        }

    }
    else {
      entrance();
    }
    return 0;
}


bool strisdigit(string& line) {
    for (auto& i: line)
        if (!isdigit(i))
            return false;
    return true;
}

void checkCorrectChoice(string& choice) {
    while (true) {
        if (strisdigit(choice) and (choice == "1" or choice == "2")) {
            break;
        }
        else {
            cout << "Incorrect answer\nTry again: ";
            cin >> choice;
        }

    }
}

void enterlogin(string& login, string& password) {
    cout << "\nEnter login: ";
    cin >> login;
    cout << "Enter password: ";
    cin >> password;
}

void registration() {
    string login, password, checkPassword;
    cout << "Registration\n";
    vector <string> loginsFromFile;
    loginsToVector(loginsFromFile);
    bool check = true;
    while (check) {
        enterlogin(login, password);
        cout << "Enter password a second time: ";
        cin >> checkPassword;
        check = false;
        for (auto &i: loginsFromFile) { // проврека на существование логина
            if (includes(i.begin(), i.end(), login.begin(), login.end())) {
                cout << "This User already exists\n";
                check = true;
                break;
            }
        }
        while (checkPassword != password and !check) { // проверка на подтверждение пароля
            cout << "\npasswords are different\nTry again\n";
            enterlogin(login, password);
            cout << "Enter password a second time: ";
            cin >> checkPassword;
            check = false;
            for (auto &i: loginsFromFile) { // проверка на наличие в бд пользователя
                if (includes(i.begin(), i.end(), login.begin(), login.end())) {
                    cout << "\nThis User already exists\n\n";
                    check = true;
                    break;
                }
            }
        }
    }
    ofstream newLogin("users.txt", ios::app);

    newLogin << login + ":" + password + "\n";
    cout << "\nYou are registered!\nWelcome to the club buddy!\n";
    newLogin.close();
}
void entrance() {
    string login, password, loginFromFile;
    ifstream logins("users.txt");
    if (!logins.is_open()) {
        cout << "User file is not found!";
        return;
    }
    vector <string> loginsFromFile;
    loginsToVector(loginsFromFile);
    while (true) {
        enterlogin(login, password);
        login += ":" + password;
        for (auto& i: loginsFromFile) {
            if (i == login) {
                cout << "All correct!\n";
                return;
            }
        }
        logins.close();
        cout << "Login or password inccorect\n";
    }
}
void loginsToVector(vector <string>& loginsFromFileInVector) {
    ifstream newLoginForcheck("users.txt");
    string loginFromFile;
    while (getline(newLoginForcheck, loginFromFile)) {
        loginsFromFileInVector.push_back(loginFromFile);
    }
    newLoginForcheck.close();
}

