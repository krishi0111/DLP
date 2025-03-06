#include <iostream>
#include <string>

using namespace std;

string input;
int index = 0;

bool S();
bool L();
bool L_d();
bool match(char expected);

// Function to parse S → ( L ) | a
bool S() {
    if (match('a')) {
        return true; 
    }
    if (match('(')) { 
        if (L() && match(')')) {
            return true;
        }
    }
    return false; 
}

// Function to parse L → S L’
bool L() {
    if (!S()) return false; 
    return L_d(); // 
}

// Function to parse L' → , S L' | ε
bool L_d() {
    if (match(',')) { 
        if (!S()) return false;
        return L_d(); 
    }
    return true; // ε case
}

bool match(char expected) {
    if (index < input.length() && input[index] == expected) {
        index++; 
        return true;
    }
    return false;
}

bool validate(string str) {
    input = str;
    index = 0;
    return S() && index == input.length();
}

int main() {
    string testCases[] = {
        "a", "(a)", "(a,a)", "(a,(a,a),a)", "(a,a),(a,a)",
        "a)", "(a a,a", "a a,", "(a,a),a"
    };
    
    for (string testCase : testCases) {
        cout << "Input: " << testCase << " -> " 
             << (validate(testCase) ? "Valid string" : "Invalid string") 
             << endl;
    }

    return 0;
}
