#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSets;
map<char, set<char>> followSets;
map<char, map<char, string>> parsingTable;

// Compute First sets
void computeFirst(char nonTerminal) {
    if (!firstSets[nonTerminal].empty()) return;

    for (const string &production : grammar[nonTerminal]) {
        bool hasEpsilon = true;

        for (char symbol : production) {
            if (islower(symbol) || symbol == '(' || symbol == ')') {
                firstSets[nonTerminal].insert(symbol);
                hasEpsilon = false;
                break;
            } else if (isupper(symbol)) {
                computeFirst(symbol);
                for (char c : firstSets[symbol]) {
                    if (c != 'ε') firstSets[nonTerminal].insert(c);
                }
                if (firstSets[symbol].count('ε') == 0) {
                    hasEpsilon = false;
                    break;
                }
            }
        }
        if (hasEpsilon) firstSets[nonTerminal].insert('ε');
    }
}

// Compute Follow sets
void computeFollow(char nonTerminal) {
    if (!followSets[nonTerminal].empty()) return;

    if (nonTerminal == 'S') followSets[nonTerminal].insert('$');

    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        char lhs = it->first;
        for (const string &production : it->second) {
            for (size_t i = 0; i < production.size(); i++) {
                if (production[i] == nonTerminal) {
                    bool hasEpsilon = false;

                    for (size_t j = i + 1; j < production.size(); j++) {
                        if (isupper(production[j])) {
                            for (char c : firstSets[production[j]]) {
                                if (c != 'ε') followSets[nonTerminal].insert(c);
                            }
                            if (firstSets[production[j]].count('ε') == 0) break;
                            hasEpsilon = true;
                        } else {
                            followSets[nonTerminal].insert(production[j]);
                            hasEpsilon = false;
                            break;
                        }
                    }

                    if (hasEpsilon || i + 1 == production.size()) {
                        computeFollow(lhs);
                        followSets[nonTerminal].insert(followSets[lhs].begin(), followSets[lhs].end());
                    }
                }
            }
        }
    }
}

// Construct Parsing Table
bool constructParsingTable() {
    bool isLL1 = true;

    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        char nonTerminal = it->first;
        for (const string &production : it->second) {
            set<char> firstSet;

            if (islower(production[0]) || production[0] == '(' || production[0] == ')') {
                firstSet.insert(production[0]);
            } else {
                firstSet = firstSets[production[0]];
            }

            for (char terminal : firstSet) {
                if (terminal != 'ε') {
                    if (!parsingTable[nonTerminal][terminal].empty()) {
                        isLL1 = false;
                    }
                    parsingTable[nonTerminal][terminal] = production;
                }
            }

            if (firstSet.count('ε')) {
                for (char terminal : followSets[nonTerminal]) {
                    if (!parsingTable[nonTerminal][terminal].empty()) {
                        isLL1 = false;
                    }
                    parsingTable[nonTerminal][terminal] = production;
                }
            }
        }
    }

    return isLL1;
}

// Print Parsing Table in Tabular Form (without | symbols)
void printParsingTable() {
    set<char> terminals = {'a', 'b', '(', ')', 'c', '$'};

    cout << "\nPredictive Parsing Table:\n";
    cout << "------------------------------------------------------\n";
    cout << setw(10) << " ";
    for (char t : terminals) cout << setw(8) << t;
    cout << "\n------------------------------------------------------\n";

    for (auto it = parsingTable.begin(); it != parsingTable.end(); ++it) {
        char nonTerminal = it->first;
        cout << setw(10) << nonTerminal;
        for (char t : terminals) {
            cout << setw(8) << (parsingTable[nonTerminal][t] == "" ? "-" : parsingTable[nonTerminal][t]);
        }
        cout << "\n------------------------------------------------------\n";
    }
}

int main() {
    // Define the grammar
    grammar['S'] = {"ABC", "D"};
    grammar['A'] = {"a", "ε"};
    grammar['B'] = {"b", "ε"};
    grammar['C'] = {"(S)", "c"};
    grammar['D'] = {"AC"};

    // Compute First and Follow sets
    for (auto it = grammar.begin(); it != grammar.end(); ++it) computeFirst(it->first);
    for (auto it = grammar.begin(); it != grammar.end(); ++it) computeFollow(it->first);

    // Construct Parsing Table
    bool isLL1 = constructParsingTable();

    // Print Parsing Table
    printParsingTable();

    cout << "\nGrammar is " << (isLL1 ? "LL(1)" : "NOT LL(1)") << "\n";

    return 0;
}
