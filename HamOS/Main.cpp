#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

// Global variables
unordered_map<char, int> variables;
unordered_map<string, string> stringVariables;

// Function prototypes
void loadPrograms(vector<string>& programs);
void runProgram(const string& filename);
void displayStartupScreen(const vector<string>& programs, int currentSelection);
void createVar(char VarName, int Value);
void createStringVar(const string& VarName, const string& Value);
void printVar(char VarName);
void printStr(const string& str);
void printStrVar(const string& VarName);
void wait(int seconds);
void printMulti(const vector<string>& lines);
void executeLine(const string& line);

int main() {
    vector<string> programs;
    loadPrograms(programs);

    int currentSelection = 0;
    char key;

    while (true) {
        // Display startup screen
        displayStartupScreen(programs, currentSelection);

        // Get user input
        key = _getch();

        if (key == 72) { // Up arrow key
            currentSelection = (currentSelection - 1 + programs.size()) % programs.size();
        }
        else if (key == 80) { // Down arrow key
            currentSelection = (currentSelection + 1) % programs.size();
        }
        else if (key == 13) { // Enter key
            system("cls");
            runProgram(programs[currentSelection]);
            cout << "Program stopped. Reset?" << endl;
            _getch();
        }
    }

    return 0;
}

void loadPrograms(vector<string>& programs) {
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(L"programs\\*.Ham", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "No programs found." << endl;
        return;
    }

    do {
        wstring ws(findFileData.cFileName);
        string filename(ws.begin(), ws.end());
        programs.push_back(filename);
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void displayStartupScreen(const vector<string>& programs, int currentSelection) {
    system("cls");
    cout << "*****************************************************************" << endl;
    cout << "* Welcome to                                                    *" << endl;
    cout << "*                _    _                  ____   _____           *" << endl;
    cout << "*               | |  | |                / __ | / ____|          *" << endl;
    cout << "*               | |__| | __ _ _ __ ___ | |  | | (___            *" << endl;
    cout << "*               |  __  |/ _` | '_ ` _ || |  | ||___ |           *" << endl;
    cout << "*               | |  | | (_| | | | | | | |__| |____) |          *" << endl;
    cout << "*               |_|  |_||__,_|_| |_| |_||____/|_____/           *" << endl;
    cout << "*                                                               *" << endl;
    cout << "*                                                               *" << endl;
    cout << "*****************************************************************" << endl;
    cout << "*                                                               *" << endl;
    cout << "* V0.2                                        Developer Edition *" << endl;
    cout << "*****************************************************************" << endl;
    cout << endl;
    cout << "Available Programs:" << endl;

    for (int i = 0; i < programs.size(); ++i) {
        if (i == currentSelection) {
            cout << "> " << programs[i] << endl;
        }
        else {
            cout << "  " << programs[i] << endl;
        }
    }
}

void runProgram(const string& filename) {
    ifstream file("programs/" + filename);
    string line;
    vector<string> multiLine;

    while (getline(file, line)) {
        if (line.find("printMulti {") == 0) {
            while (getline(file, line) && line.find("}") == string::npos) {
                multiLine.push_back(line);
            }
            printMulti(multiLine);
            multiLine.clear();
        }
        else {
            executeLine(line);
        }
    }
}

void executeLine(const string& line) {
    if (line.find("==") != string::npos && line[1] == ' ') {
        char varName = line[0];
        int value = stoi(line.substr(line.find("==") + 3));
        createVar(varName, value);
    }
    else if (line.find("==") != string::npos && line[1] != ' ') {
        string varName = line.substr(0, line.find("==") - 1);
        string value = line.substr(line.find("==") + 3);
        createStringVar(varName, value);
    }
    else if (line.find("printVar") == 0) {
        char var = line[9];
        printVar(var);
    }
    else if (line.find("printStr") == 0) {
        string str = line.substr(10, line.size() - 11); // Extract string
        printStr(str);
    }
    else if (line.find("printStrVar") == 0) {
        string varName = line.substr(12, line.size() - 13); // Extract variable name
        printStrVar(varName);
    }
    else if (line.find("wait") == 0) {
        int seconds = stoi(line.substr(5, line.size() - 6)); // Extract seconds
        wait(seconds);
    }
}

void createVar(char VarName, int Value) {
    variables[VarName] = Value;
}

void createStringVar(const string& VarName, const string& Value) {
    stringVariables[VarName] = Value;
}

void printVar(char VarName) {
    if (variables.find(VarName) != variables.end()) {
        cout << variables[VarName] << endl;
    }
    else {
        cout << "Variable " << VarName << " not defined." << endl;
    }
}

void printStr(const string& str) {
    cout << str << endl;
}

void printStrVar(const string& VarName) {
    if (stringVariables.find(VarName) != stringVariables.end()) {
        cout << stringVariables[VarName] << endl;
    }
    else {
        cout << "String variable " << VarName << " not defined." << endl;
    }
}

void wait(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void printMulti(const vector<string>& lines) {
    for (const string& line : lines) {
        cout << line << endl;
    }
}
