/*******************************************************************************
* Name : waterjugpuzzle.cpp
* Author : Syed Ahmad Shah
* Date : 10/19/2024
* Description :
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
*******************************************************************************/

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <sstream>

using namespace std;

// Struct to represent the state of the water jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions)
        : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() const {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

string gallon(int amount) {
    if (amount == 1) {
        return "gallon";
    } else {
        return "gallons";
    }
}


void bfs(int capA, int capB, int capC, int goalA, int goalB, int goalC) {
    queue<State*> q;
    unordered_set<string> visited;
    vector<State*> all_states;

    State* initial_state = new State(0, 0, capC, "Initial state.");
    q.push(initial_state);
    visited.insert(initial_state->to_string());
    all_states.push_back(initial_state);

    while (!q.empty()) {
        State *current = q.front();
        q.pop();

        if (current->a == goalA && current->b == goalB && current->c == goalC) {
            vector<string> solution;
            State *temp = current;
            while (temp != nullptr) {
                solution.push_back(temp->directions + " " + temp->to_string());
                temp = temp->parent;
            }
            for (auto it = solution.rbegin(); it != solution.rend(); ++it) {
                cout << *it << endl;
            }

            for (State* state : all_states) {
                delete state;
            }
            return;
        }

        vector<State*> next_states;
        int pour;

        if (current->c > 0 && current->a < capA) {
            pour = min(current->c, capA - current->a);
            State* newState = new State(current->a + pour, current->b, current->c - pour, "Pour " + to_string(pour) + " " + gallon(pour) + " from C to A.");
            newState->parent = current;
            next_states.push_back(newState);
        }

        if (current->b > 0 && current->a < capA) {
            pour = min(current->b, capA - current->a);
            State* newState = new State(current->a + pour, current->b - pour, current->c, "Pour " + to_string(pour) + " " + gallon(pour) + " from B to A.");
            newState->parent = current;
            next_states.push_back(newState);
        }

        if (current->c > 0 && current->b < capB) {
            pour = min(current->c, capB - current->b);
            State* newState = new State(current->a, current->b + pour, current->c - pour, "Pour " + to_string(pour) + " " + gallon(pour) + " from C to B.");
            newState->parent = current;
            next_states.push_back(newState);
        }

        for (int i = 0; i < 2; ++i) {
            if (current->a > 0 && current->b < capB) {
                pour = min(current->a, capB - current->b);
                State* newState = new State(current->a - pour, current->b + pour, current->c, "Pour " + to_string(pour) + " " + gallon(pour) + " from A to B.");
                newState->parent = current;
                next_states.push_back(newState);
            }

            if (current->b > 0 && current->c < capC) {
                pour = min(current->b, capC - current->c);
                State* newState = new State(current->a, current->b - pour, current->c + pour, "Pour " + to_string(pour) + " " + gallon(pour) + " from B to C.");
                newState->parent = current;
                next_states.push_back(newState);
            }

            if (current->a > 0 && current->c < capC) {
                pour = min(current->a, capC - current->c);
                State* newState = new State(current->a - pour, current->b, current->c + pour, "Pour " + to_string(pour) + " " + gallon(pour) + " from A to C.");
                newState->parent = current;
                next_states.push_back(newState);
            }
        }

        for (State* next : next_states) {
            if (visited.find(next->to_string()) == visited.end()) {
                q.push(next);
                visited.insert(next->to_string());
                all_states.push_back(next);
            } else {
                delete next;
            }
        }
    }

    cout << "No solution." << endl;

    for (State* state : all_states) {
        delete state;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }


    int capA = stoi(argv[1]);
    int capB = stoi(argv[2]);
    int capC = stoi(argv[3]);
    int goalA = stoi(argv[4]);
    int goalB = stoi(argv[5]);
    int goalC = stoi(argv[6]);

    if (capA < 0) {
        cout << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    if (capB < 0) {
        cout << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }
    if (capC <= 0) {
        cout << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }
    if (goalA < 0) {
        cout << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }
    if (goalB < 0) {
        cout << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }
    if (goalC < 0) {
        cout << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }
    if (goalA > capA) {
        cout << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if (goalB > capB) {
        cout << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if (goalC > capC) {
        cout << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    if (goalA + goalB + goalC != capC) {
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    bfs(capA, capB, capC, goalA, goalB, goalC);


    return 0;
}
