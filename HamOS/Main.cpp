#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include <conio.h>

using namespace std;

// Global variables
unordered_map<char, int> variables;

// Function prototypes
void loadPrograms(vector<string>& programs);
void runProgram(const string& filename);
void displayStartupScreen(const vector<string>& programs, int currentSelection);
void createVar(char VarName, int Value);
void printVar(char VarName);
void printStr(const string& str);
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
    cout << "*                                                               *" << endl;
    cout << "*****************************************************************" << endl;
    cout << "*                                                               *" << endl;
    cout << "* V0.1                                            Legacy Edition*" << endl;
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

    while (getline(file, line)) {
        executeLine(line);
    }
}

void executeLine(const string& line) {
    if (line.find("==") != string::npos) {
        char varName = line[0];
        int value = stoi(line.substr(line.find("==") + 3));
        createVar(varName, value);
    }
    else if (line.find("printVar") == 0) {
        char var = line[9];
        printVar(var);
    }
    else if (line.find("printStr") == 0) {
        string str = line.substr(10, line.size() - 11); // Extract string
        printStr(str);
    }
}

void createVar(char VarName, int Value) {
    variables[VarName] = Value;
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
