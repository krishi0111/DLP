#include <iostream>
#include <string>
using namespace std;

class FiniteAutomaton {
public:
    string transitions[10][2];
    string initial_state;
    string final_states[10];
    int num_final_states;

    FiniteAutomaton(string initial_state, string final_states[], int num_final_states) {
        this->initial_state = initial_state;
        this->num_final_states = num_final_states;
        for (int i = 0; i < num_final_states; ++i) {
            this->final_states[i] = final_states[i];
        }
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 2; ++j) {
                transitions[i][j] = "";
            }
        }
    }

    void add_transition(int from_state, char symbol, int to_state) {
        int symbol_index = (symbol == 'a') ? 0 : 1;
        transitions[from_state - 1][symbol_index] = to_string(to_state);
    }

    bool is_valid_string(string input_string) {
        int current_state = stoi(initial_state);

        for (char symbol : input_string) {
            int symbol_index = (symbol == 'a') ? 0 : 1;

            if (transitions[current_state - 1][symbol_index] == "") {
                return false;
            }

            current_state = stoi(transitions[current_state - 1][symbol_index]);
        }

        for (int i = 0; i < num_final_states; ++i) {
            if (to_string(current_state) == final_states[i]) {
                return true;
            }
        }

        return false;
    }
};

bool test_cases(string input, int test_number) {
    if (test_number == 1) {
        for (size_t i = 0; i < input.length(); ++i) {
            if (input[i] == '0' && (i + 2 >= input.length() || input[i + 1] != '1' || input[i + 2] != '1')) {
                return false;
            }
        }
        return true;
    } else if (test_number == 2) {
        return input[0] == input[input.length() - 1];
    } else if (test_number == 3) {
        return isalpha(input[0]);
    }
    return false;
}

int main() {
    int num_states, num_symbols, num_final_states;
    cout << "Enter number of states: ";
    cin >> num_states;

    cout << "Enter number of symbols (assumed as a and b): ";
    cin >> num_symbols;

    string initial_state;
    cout << "Enter initial state: ";
    cin >> initial_state;

    cout << "Enter number of final states: ";
    cin >> num_final_states;

    string final_states[10];
    cout << "Enter final state(s): ";
    for (int i = 0; i < num_final_states; ++i) {
        cin >> final_states[i];
    }

    FiniteAutomaton fa(initial_state, final_states, num_final_states);

    cout << "Enter transitions (format: from_state symbol to_state, e.g., 1 a 2):\n";
    int from_state, to_state;
    char symbol;
    while (true) {
        cin >> from_state;
        if (from_state == -1) break;
        cin >> symbol >> to_state;
        fa.add_transition(from_state, symbol, to_state);
    }

    string input_string;
    cout << "Enter input string for automaton: ";
    cin >> input_string;

    if (fa.is_valid_string(input_string)) {
        cout << "Valid string for the automaton.\n";
    } else {
        cout << "Invalid string for the automaton.\n";
    }

    cout << "\nAdditional Test Cases:\n";
    cout << "Test 1: String over 0 and 1 where every 0 is immediately followed by 11.\n";
    cout << "Enter string: ";
    cin >> input_string;
    if (test_cases(input_string, 1)) {
        cout << "Valid string for Test 1.\n";
    } else {
        cout << "Invalid string for Test 1.\n";
    }

    cout << "Test 2: String over a, b, c that starts and ends with the same letter.\n";
    cout << "Enter string: ";
    cin >> input_string;
    if (test_cases(input_string, 2)) {
        cout << "Valid string for Test 2.\n";
    } else {
        cout << "Invalid string for Test 2.\n";
    }

    cout << "Test 3: String over lower-case alphabet and digits that starts with an alphabet.\n";
    cout << "Enter string: ";
    cin >> input_string;
    if (test_cases(input_string, 3)) {
        cout << "Valid string for Test 3.\n";
    } else {
        cout << "Invalid string for Test 3.\n";
    }

    return 0;
}
