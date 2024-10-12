#include <iostream>
#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib> 
#ifdef _WIN32
#include <windows.h> 
#endif

using namespace std;

class User {
public:
    string frnd;
    int user_id; 

    void addFriend(string username) {
        string filename = username + "_friendList.txt";
        ofstream friendsFile;
        friendsFile.open(filename, ios_base::app);
        if (friendsFile.is_open()) {
            string friendName;
            cout << "Enter a friend's name (enter 'Stop' to finish): ";
            cin >> friendName;
            if (friendName == "Stop") return; 
            friendsFile << friendName << endl;
            friendsFile.close();
            string friendFilename = friendName + "_friendList.txt";
            ofstream friendFile;
            friendFile.open(friendFilename, ios_base::app);
            if (friendFile.is_open()) {
                friendFile << username << endl;
                friendFile.close();
            } else {
                cerr << "Error creating file: " << friendFilename << endl;
            }
            cout << "Friend List updated" << endl;
        } else {
            cerr << "Error creating file: " << filename << endl;
        }
    }

    void chat(string user1, string user2) {
        ifstream friends(user1 + "_friendList.txt");
        string friendName;
        bool foundFriend = false;
        while (friends >> friendName) {
            if (user2 == friendName) {
                foundFriend = true;
                break;
            }
        }
        friends.close();

        if (!foundFriend) {
            cerr << "Error: " << user2 << " is not in the friend list of " << user1 << endl;
            return;
        }
        ofstream chatFile(user1 + "_" + user2 + "_chat.txt", ios_base::app);
        if (!chatFile.is_open()) {
            cerr << "Error creating chat file" << endl;
            return;
        }

        string message;
        cout << "Start chatting between " << user1 << " and " << user2 << " (type 'exit' to end chat)" << endl;

        while (true) {
            cout << user1 << ": ";
            getline(cin, message);
            if (message == "exit") {
                break;
            }

            time_t t = time(nullptr);
            string timestamp = asctime(localtime(&t));
            timestamp = timestamp.substr(0, timestamp.size() - 1); 
            chatFile << "[" << timestamp << "] " << user1 << ": " << message << endl;

            cout << user2 << ": ";
            getline(cin, message);
            if (message == "exit") {
                break;
            }
            t = time(nullptr);
            timestamp = asctime(localtime(&t));
            timestamp = timestamp.substr(0, timestamp.size() - 1);
            chatFile << "[" << timestamp << "] " << user2 << ": " << message << endl;
        }
        chatFile.close();
    }

    void inbox(string username) {
        cout << "Enter the friend's name: ";
        cin >> frnd;
        string fileName = username + "_" + frnd + "_chat.txt";
        ifstream inputFile(fileName);

        if (!inputFile.is_open()) {
            cerr << "No chats found with " << frnd << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }
        inputFile.close();
    }

    void logout() {
        cout << "Logged out successfully" << endl;
    }
} u1;

class Options {
public:
    void choice(string username) {
        int ch, n = 1;
        string frnd;
        while (n == 1) {
            cout << "\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\t\t\tWelcome " << username << "\n";
            cout << "\t\t\t\t\t*                                        *\n";
            cout << "\t\t\t\t\t*\t\t1. Chat\t\t\t\t*\n";
            cout << "\t\t\t\t\t*\t\t2. Inbox\t\t\t*\n";
            cout << "\t\t\t\t\t*\t\t3. Add Friend\t\t\t*\n";
            cout << "\t\t\t\t\t*\t\t4. Logout\t\t\t*\n";
            cout << "\t\t\t\t\t*                                        *\n";
            cout << "\t\t\t\t\t****************\n";
            cout << "Enter your choice: ";
            cin >> ch;
            cin.ignore();
            switch (ch) {
                case 1:
                    cout << "Enter the friend's name to chat with: ";
                    cin >> frnd;
                    cin.ignore();
                    u1.chat(username, frnd);
                    break;
                case 2:
                    u1.inbox(username);
                    break;
                case 3:
                    u1.addFriend(username);
                    break;
                case 4:
                    u1.logout();
                    return; 
                default:
                    cout << "Invalid choice!" << endl;
            }
            cout << "Enter 0 to terminate/1 to continue: ";
            cin >> n;
        }
    }
} o;

void clearScreen() {
#ifdef _WIN32
    system("cls"); 
#else
    system("clear"); 
#endif
}

class Register {
public:
    string username, password;

    void sign_up() {
        ofstream m("Database.txt", ios::app);
        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        m << username << "\t" << password << endl;
        cout << "Successfully Registered" << endl;
        m.close();
    }

    void login() {
        string reguser, regpass;
        string line = "";
        cout << "USERNAME: ";
        cin >> username;
        cout << "PASSWORD: ";
        cin >> password;

        ifstream readFile("Database.txt");
        bool found = false;

        while (getline(readFile, line)) {
            stringstream iss(line);
            iss >> reguser >> regpass;

            if (username == reguser && password == regpass) {
                cout << "Login Success!!" << endl;
                found = true;
                clearScreen();
                o.choice(username);
                break;
            }
        }

        if (!found) {
            cerr << "Invalid login credentials!" << endl;
        }

        readFile.close();
    }
} r;

int main() {
    int ch;
    clearScreen(); 
    cout << "\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t** Welcome to 'AK' **\n";
    cout << "\t\t\t\t\t*                                        *\n";
    cout << "\t\t\t\t\t*\t\t1. Login\t\t\t *\n";
    cout << "\t\t\t\t\t*\t\t2. Sign Up\t\t\t *\n";
    cout << "\t\t\t\t\t*                                        *\n";
    cout << "\t\t\t\t\t****************\n";
    cout << "Enter your choice: ";
    cin >> ch;
    clearScreen(); 

    switch (ch) {
        case 1:
            r.login();
            break;
        case 2:
            r.sign_up();
            break;
        default:
            cerr << "Invalid choice!" << endl;
    }

    return 0;
}
