/*******************************************************************************
 * Name        : unique.cpp
 * Author      : 
 * Date        : 
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      :
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    for(int i = 0; i < s.length(); i++){
        if(s[i] < 'a' or s[i] > 'z'){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    unsigned int bit_vector = 0;
    for(int i = 0; i < s.length(); i++){
        if(bit_vector & (1 << s[i])){
            return false;
        }
        bit_vector |= 1 << s[i];
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if (argc != 2) {  // Check if exactly one argument is provided
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if (!is_all_lowercase(argv[1])) {  // Validate if the input contains only lowercase letters
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (all_unique_letters(argv[1])) {  // Check for unique characters
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
