/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Syed Ahmad Shah
 * Date        : 9/28/2024
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    // Loop through all letters
    for(size_t i = 0; i < s.length(); i++){
        // If letters does not exist within the range of 'a' or 'z' then its either a number or a capital letter
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
    for(size_t i = 0; i < s.length(); i++){
        // If the & operator is valid, meaning bitvector and the new bit shift both have a 1, the letter has been seen before
        if(bit_vector & (1 << s[i])){
            return false;
        }

        // Update bitvector with the bit shift of the new letter
        bit_vector |= 1 << s[i];
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if (argc != 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if (!is_all_lowercase(argv[1])) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (all_unique_letters(argv[1])) {
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
